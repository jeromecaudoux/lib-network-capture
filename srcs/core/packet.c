#include <time.h>
#include <stdlib.h>
#include "layers/layer_data_link_ethernet.h"
#include "layers/layer_network_ipv4.h"
#include "layers/layer_transport_tcp.h"
#include "layers/layer_transport_udp.h"
#include "layers/layer_application_http.h"
#include "layers/layer_application_dns.h"
#include "packet.h"
#include "xexit.h"

t_list create_and_fill_params(ssize_t packet_size, u_char *buffer)
{
  t_list	data;
  parse_params *params;

  data = NULL;
  if ((params = malloc(sizeof(parse_params))) == NULL)
    xexit();
  params->header.type = NODE_TYPE_PARSE_PARAMS;
  params->buffer = buffer;
  params->timestamp = time(NULL);
  params->packet_size = packet_size;
  params->parse_error_layer = -1;

  if (list_add_elem_at_front(&data, params) == glFALSE)
    xexit();
  return data;
}

t_list	parse_packet(ssize_t packet_size, u_char *buffer)
{
  t_list	data;

  data = create_and_fill_params(packet_size, buffer);
  return parse_layer_ethernet(data, buffer);
}

void dump_packet_data_node(void *addr)
{
  layer_node *node;

  node = (layer_node *)addr;
  if (node->type == NODE_TYPE_ETHERNET)
    dump_layer_ethernet((layer_ethernet *) node);
  if (node->type == NODE_TYPE_IPV4)
    dump_layer_network_ipv4((layer_network_ipv4 *) node);
  if (node->type == NODE_TYPE_TCP)
    dump_layer_transport_tcp((layer_transport_tcp *) node);
  if (node->type == NODE_TYPE_UDP)
    dump_layer_transport_udp((layer_transport_udp *) node);
  if (node->type == NODE_TYPE_HTTP)
    dump_layer_application_http((layer_application_http *) node);
  if (node->type == NODE_TYPE_DNS)
    dump_layer_application_dns((layer_application_dns *) node);
}

void	clear_packet_data_node(void *addr)
{
  layer_node *node;

  node = (layer_node *)addr;
  if (node->type == NODE_TYPE_HTTP)
    free_layer_application_http((layer_application_http *) addr);
  free(addr);
}
