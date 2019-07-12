#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "layer_data_link_ethernet.h"
#include "layer_application_http.h"
#include "layer_network_ipv4.h"
#include "../packet.h"
#include "../xexit.h"

static t_bool find_node(void *value, void *param)
{
  if ((unsigned long) ((layer_node *) value)->type == (unsigned long) param)
    return glTRUE;
  return glFALSE;
}

void free_layer_application_http(layer_application_http *la_http)
{
  free(la_http->buffer);
}

void dump_layer_application_http(layer_application_http *la_http)
{
  printf("Protocol HTTP :\n%.*s\n", la_http->size, la_http->buffer);
}

void parse_layer_application_http(t_list data, u_char *buffer)
{
  layer_application_http *la_http;
  layer_network_ipv4 *ln_ipv4;
  parse_params *params;
  unsigned int headers_size;
  unsigned int http_size;

  ln_ipv4 = (layer_network_ipv4 *) list_get_elem_like(data, find_node, (void *)NODE_TYPE_IPV4);
  params = (parse_params *) list_get_elem_like(data, find_node, (void *)NODE_TYPE_PARSE_PARAMS);
  headers_size = (u_char *)buffer - (u_char *)(params->buffer) - ETH_HLEN;
  http_size = htons(ln_ipv4->iphdr.tot_len) - headers_size;

  if ((la_http = malloc(sizeof(layer_application_http))) == NULL)
    xexit();
  la_http->header.type = NODE_TYPE_HTTP;
  la_http->size = http_size;
  if ((la_http->buffer = malloc(http_size + 1)) == NULL)
    xexit();
  memcpy(la_http->buffer, buffer, http_size);
  la_http->buffer[http_size] = 0;
  if (list_add_elem_at_back(&data, la_http) == glFALSE)
    xexit();
}
