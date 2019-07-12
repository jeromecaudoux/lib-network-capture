#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "layer_data_link_ethernet.h"
#include "layer_network_ipv4.h"
#include "../xexit.h"
#include <arpa/inet.h>

static const char *get_protocol_name(uint16_t protocol)
{
  protocol = htons(protocol);
  if (protocol == ETH_P_IP)
    return "IPV4";
  else if (protocol == ETH_P_IPV6)
    return "IPV6";
  return "Not supported";
}

static void parse_next_layer(uint16_t protocol, t_list data, u_char *buffer)
{
  protocol = htons(protocol);
  if (protocol == ETH_P_IP)
    {
      parse_layer_network_ipv4(data, buffer);
      return;
    }
  //  printf("Ignoring packet type %04X\n", protocol);
}

void dump_layer_ethernet(layer_ethernet *ethernet)
{
  printf("From %02x:%02x:%02x:%02x:%02x:%02x To %02x:%02x:%02x:%02x:%02x:%02x Protocol 0x%04X %s\n",
	 ethernet->ethhdr.h_source[0],
	 ethernet->ethhdr.h_source[1],
	 ethernet->ethhdr.h_source[2],
	 ethernet->ethhdr.h_source[3],
	 ethernet->ethhdr.h_source[4],
	 ethernet->ethhdr.h_source[5],
	 ethernet->ethhdr.h_dest[0],
	 ethernet->ethhdr.h_dest[1],
	 ethernet->ethhdr.h_dest[2],
	 ethernet->ethhdr.h_dest[3],
	 ethernet->ethhdr.h_dest[4],
	 ethernet->ethhdr.h_dest[5],
	 ethernet->ethhdr.h_proto,
	 get_protocol_name(ethernet->ethhdr.h_proto));
}

t_list parse_layer_ethernet(t_list data, u_char *buffer)
{
  layer_ethernet *ethernet;

  if ((ethernet = malloc(sizeof(layer_ethernet))) == NULL)
    xexit();
  ethernet->header.type = NODE_TYPE_ETHERNET;
  memcpy(&(ethernet->ethhdr), buffer, ETH_HLEN);
  if (list_add_elem_at_front(&data, ethernet) == glFALSE)
    xexit();
  parse_next_layer(ethernet->ethhdr.h_proto, data, (u_char *)buffer + ETH_HLEN);
  return data;
}
