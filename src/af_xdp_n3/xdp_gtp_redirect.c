// xdp_gtp_redirect.c
#include <linux/bpf.h>
#include <linux/ptrace.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>  // For ETH_P_IP and struct ethhdr
#include <linux/ip.h>        // For struct iphdr
#include <linux/udp.h>       // For struct udphdr
#include <linux/in.h>      // For IPPROTO_UDP

// Map for AF_XDP sockets
struct {
    __uint(type, BPF_MAP_TYPE_XSKMAP);
    __uint(key_size, sizeof(int));
    __uint(value_size, sizeof(int));
    __uint(max_entries, 64);
} xsks_map SEC(".maps");

static inline unsigned short htons(unsigned short hostshort) {
	    return (hostshort << 8) | (hostshort >> 8);
}

SEC("xdp")
int xdp_gtp_redirect(struct xdp_md *ctx) {
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;

    // Parse Ethernet header
    struct ethhdr *eth = data;
    if ((void *)(eth + 1) > data_end)
        return XDP_PASS;

    // Check for IPv4
    if (eth->h_proto != htons(ETH_P_IP))
        return XDP_PASS;

    // Parse IP header
    struct iphdr *ip = data + sizeof(*eth);
    if ((void *)(ip + 1) > data_end)
        return XDP_PASS;

    // Check for UDP
    if (ip->protocol != IPPROTO_UDP)
        return XDP_PASS;

    // Parse UDP header
    struct udphdr *udp = (void *)ip + sizeof(*ip);
    if ((void *)(udp + 1) > data_end)
        return XDP_PASS;

    // Check for GTP-U port (2152)
    if (udp->dest != htons(2152))
        return XDP_PASS;

    // Redirect to AF_XDP socket
    return bpf_redirect_map(&xsks_map, ctx->rx_queue_index, XDP_PASS);
}

char _license[] SEC("license") = "GPL";
