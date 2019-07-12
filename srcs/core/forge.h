#ifndef FORGE_H_
# define FORGE_H_

# include <netinet/ip.h>

struct pseudo_header
{
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t reserved;
    u_int8_t protocol;
    u_int16_t udp_length;
};

void forge(const char* source_ip,
	   int port_src,
	   const char* dest_ip,
	   int port_dst,
	   const char *hostname,
	   int ttl);

int get_dns_forged_packet(const char* source_ip,
			  int port_src,
			  int port_dst,
			  const char *hostname,
			  int ttl,
			  char **packet,
			  struct sockaddr_in *sin);

#endif
