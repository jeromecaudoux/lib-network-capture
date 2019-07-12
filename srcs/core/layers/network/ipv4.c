#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ipv4.h"
#include "../transport/tcp.h"
#include "../transport/udp.h"
#include "../../xexit.h"

static void parse_next_layer(uint8_t protocol, t_list data, u_char *buffer)
{
  if (protocol == 6)
    parse_layer_transport_tcp(data, buffer);
  else if (protocol == 17)
    parse_layer_transport_udp(data, buffer);
  /* else */
  /*   printf("Ignoring packet type %04X\n", protocol); */
}

const char *get_transport_layer_name(struct iphdr *iphdr)
{
  if (iphdr->protocol == 6)
    return "TCP";
  if (iphdr->protocol == 17)
    return "UDP";
  if (iphdr->protocol == 1)
    return "ICMP";
  return "Unknown";
}

void dump_layer_network_ipv4(layer_network_ipv4 *ln_ipv4)
{
  printf("From %s ", inet_ntoa(*((struct in_addr*) &(ln_ipv4->iphdr.saddr))));
  printf("to %s\n", inet_ntoa(*((struct in_addr*) &(ln_ipv4->iphdr.daddr))));
  printf("IP version => %d\n", ln_ipv4->iphdr.version);
  printf("IHL (Internet Header Length) => %d\n", ln_ipv4->iphdr.ihl);
  printf("Tos (Type of Service) => 0x%02x\n", htons(ln_ipv4->iphdr.tos));
  printf("Datagram Total length => %d\n", htons(ln_ipv4->iphdr.tot_len));
  printf("Frag id => 0x%02x\n", htons(ln_ipv4->iphdr.id));
  printf("Frag offset => 0x%02x\n", htons(ln_ipv4->iphdr.frag_off));
  printf("TTL => %d\n", ln_ipv4->iphdr.ttl);
  printf("Transport Layer => %d %s\n",
	 ln_ipv4->iphdr.protocol,
	 get_transport_layer_name(&(ln_ipv4->iphdr)));
  printf("Checksum => 0x%02x\n", ln_ipv4->iphdr.check);
}

void parse_layer_network_ipv4(t_list data, u_char *buffer)
{
  layer_network_ipv4 *ln_ipv4;

  if ((ln_ipv4 = malloc(sizeof(layer_network_ipv4))) == NULL)
    xexit();
  ln_ipv4->header.type = NODE_TYPE_IPV4;
  memcpy(&(ln_ipv4->iphdr), buffer, sizeof(struct iphdr));
  if (list_add_elem_at_back(&data, ln_ipv4) == glFALSE)
    xexit();
  parse_next_layer(ln_ipv4->iphdr.protocol, data, (u_char *)buffer + sizeof(struct iphdr));
}
