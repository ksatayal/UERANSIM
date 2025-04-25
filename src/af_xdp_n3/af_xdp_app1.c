#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <xdp/xsk.h>
//#include <xdp/umem.h>
#include <xdp/libxdp.h>
#include <linux/if_link.h>
#include <linux/if_xdp.h>
#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <arpa/inet.h>
#include <net/if.h>

#define NUM_FRAMES 4096
#define FRAME_SIZE 2048
#define RX_RING_SIZE 2048
#define TX_RING_SIZE 2048
#define BATCH_SIZE 32

struct _xsk_umem_info {
    struct xsk_ring_prod fq;
    struct xsk_ring_cons cq;
    struct xsk_umem *umem;
    void *buffer;
};

struct _xsk_socket_info {
    struct xsk_ring_cons rx;
    struct xsk_ring_prod tx;
    struct xsk_umem_info *umem;
    struct xsk_socket *xsk;

    uint64_t umem_frame_addr[NUM_FRAMES];
    uint32_t umem_frame_free;

    uint32_t outstanding_tx;

    //struct stats_record stats;

    //struct stats_record prev_stats;
};



static struct _xsk_umem_info *configure_xsk_umem(void *buffer, uint64_t size)
{
    struct _xsk_umem_info *umem;
    int ret;

    struct xsk_umem_config umem_cfg = {
        .fill_size = RX_RING_SIZE,
        .comp_size = TX_RING_SIZE,
        .frame_size = FRAME_SIZE,
        .frame_headroom = 0,
    };

    umem = calloc(1, sizeof(*umem));
    if (!umem)
        return NULL;

    ret = xsk_umem__create(&umem->umem, buffer, size, &umem->fq, &umem->cq, &umem_cfg);
    if (ret) {
        //errno = -ret;
        return NULL;
    }

    umem->buffer = buffer;
    return umem;
}

int main() {

    struct _xsk_umem_info *umem_info;
    
    struct xsk_umem *umem = NULL;
    struct xsk_socket *xsk = NULL;
    void *umem_area = NULL;
    size_t umem_size = NUM_FRAMES * FRAME_SIZE;
    void *packet_buffer;
    uint64_t packet_buffer_size = NUM_FRAMES * FRAME_SIZE;
    struct _xsk_socket_info *xsk_info;


    // Allocate UMEM
    /*umem_area = malloc(umem_size);
    if (!umem_area) {
        fprintf(stderr, "Failed to allocate UMEM area\n");
        return -1;
    }*/


    if (posix_memalign(&packet_buffer,
               getpagesize(), /* PAGE_SIZE aligned */
               packet_buffer_size)) {
        fprintf(stderr, "ERROR: Can't allocate buffer memory \"%s\"\n",
            strerror(errno));
        exit(EXIT_FAILURE);
    }
    /* Initialize shared packet_buffer for umem usage */
    umem_info = configure_xsk_umem(packet_buffer, packet_buffer_size);
    if (umem_info == NULL) {
        fprintf(stderr, "ERROR: Can't create umem \"%s\"\n",
            strerror(errno));
        exit(EXIT_FAILURE);
    }


    struct xsk_ring_prod fill_ring;
    struct xsk_ring_cons comp_ring;

    struct xsk_umem_config umem_cfg = {
        .fill_size = RX_RING_SIZE,
        .comp_size = TX_RING_SIZE,
        .frame_size = FRAME_SIZE,
        .frame_headroom = 0,
    };

    /*if (xsk_umem__create(&umem, umem_area, umem_size, &umem_cfg)) {
        fprintf(stderr, "Failed to create UMEM\n");
        free(umem_area);
        return -1;
    }
    int ret = xsk_umem__create(&umem, umem_area, umem_size, &fill_ring, &comp_ring, &umem_cfg);
    if (ret) {
        fprintf(stderr, "Failed to create UMEM. ret=%d\n",ret);
        free(umem_area);
        return -1;
    }*/
/*
int xsk_umem__create(struct xsk_umem **umem,
             void *umem_area, __u64 size,
             struct xsk_ring_prod *fill,
             struct xsk_ring_cons *comp,
             const struct xsk_umem_config *config);
*/


    // Create AF_XDP socket
    const char *ifname = "ens224";
    int ifindex = if_nametoindex(ifname);
    if (!ifindex) {
        fprintf(stderr, "Failed to get interface index\n");
        xsk_umem__delete(umem);
        free(umem_area);
        return -1;
    }

    struct xsk_socket_config xsk_cfg = {
        .rx_size = RX_RING_SIZE,
        .tx_size = TX_RING_SIZE,
        .libxdp_flags = 0,
        .xdp_flags = XDP_FLAGS_UPDATE_IF_NOEXIST | XDP_FLAGS_SKB_MODE, // Add SKB mode
    };

    xsk_info = calloc(1, sizeof(*xsk_info));
    if (!xsk_info)
        return NULL;


    xsk_info->umem = umem;
    int ret = xsk_socket__create(&xsk_info->xsk, 
                ifname,ifindex ,
                umem_info->umem, &xsk_info->rx,&xsk_info->tx, 
                &xsk_cfg);

    if(ret) {
        fprintf(stderr, "Failed to create AF_XDP socket %d\n",ret);
        xsk_umem__delete(umem);
        free(umem_area);
        return -1;
    }
/*

int xsk_socket__create(struct xsk_socket **xsk,
               const char *ifname, __u32 queue_id,
               struct xsk_umem *umem,
               struct xsk_ring_cons *rx,
               struct xsk_ring_prod *tx,
               const struct xsk_socket_config *config);
*/


    // Set up ring buffers
    //struct xsk_ring_prod fill_ring;
    //struct xsk_ring_cons comp_ring;
    //struct xsk_ring_cons rx_ring;
    //struct xsk_ring_prod tx_ring;
    //xsk_socket__get_rings(xsk, &fill_ring, &comp_ring, &rx_ring, &tx_ring);

    struct xsk_ring_cons *rx_ring = &xsk_info->rx; //xsk_socket__rx_ring(xsk);
    struct xsk_ring_prod *tx_ring = &xsk_info->tx; //xsk_socket__tx_ring(xsk);

    // Fill the Fill ring
    unsigned int idx = 0;
    xsk_ring_prod__reserve(tx_ring, NUM_FRAMES, &idx);
    for (int i = 0; i < NUM_FRAMES; i++) {
        *xsk_ring_prod__fill_addr(&tx_ring, idx + i) = i;
    }
    xsk_ring_prod__submit(tx_ring, NUM_FRAMES);
    
    // Main loop
    while (1) {
        unsigned int rcvd = xsk_ring_cons__peek(rx_ring, BATCH_SIZE, &idx);
        if (rcvd > 0) {
            for (int i = 0; i < rcvd; i++) {
                struct xdp_desc *desc = xsk_ring_cons__rx_desc(rx_ring, idx + i);
                void *packet = xsk_umem__get_data(umem_area, desc->addr);
                printf("Received packet of length %u\n", desc->len);
            }
            xsk_ring_cons__release(rx_ring, rcvd);
        }

        // Refill the Fill ring
        xsk_ring_prod__reserve(tx_ring, rcvd, &idx);
        for (int i = 0; i < rcvd; i++) {
            *xsk_ring_prod__fill_addr(tx_ring, idx + i) = i;
        }
        xsk_ring_prod__submit(tx_ring, rcvd);
    }

    // Clean up
    xsk_socket__delete(xsk);
    xsk_umem__delete(umem);
    free(umem_area);
    return 0;
}

