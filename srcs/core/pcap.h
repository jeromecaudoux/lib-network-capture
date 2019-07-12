#ifndef PCAP_H_
# define PCAP_H_

# include <stdint.h>
# include <pcap.h>

struct pcap_timeval {
    bpf_int32	tv_sec;
    bpf_int32	tv_usec;
};

struct pcap_sf_pkthdr {
    struct pcap_timeval ts;
    bpf_u_int32		caplen;
    bpf_u_int32		len;
};

FILE* pcap_init_file(const char *path);
void pcap_write_packet(FILE *fd,
		       bpf_int32 sec,
		       bpf_int32 usec,
		       bpf_u_int32 caplen,
		       bpf_u_int32 len,
		       u_char* data);
int pcap_read_header(FILE *fd, struct pcap_file_header *header);
int pcap_read_packet(FILE *fd, struct pcap_sf_pkthdr *header, u_char *buffer);
void pcap_close_file(FILE *fd);

#endif
