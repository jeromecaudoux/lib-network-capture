#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "layer_data_link_ethernet.h"
#include "layer_application_dns.h"
#include "layer_network_ipv4.h"
#include "../network_capture.h"
#include "../xexit.h"
#include <string.h>

void free_layer_application_dns(layer_application_dns *la_dns)
{
  (void) la_dns;
}

void dump_layer_application_dns(layer_application_dns *la_dns)
{
  printf("Protocol DNS\n");
  printf("dns ID => %d\n", la_dns->dns_header.id);
  printf("dns qd count => %d\n", htons(la_dns->dns_header.qd_count));
  printf("dns an count => %d\n", htons(la_dns->dns_header.an_count));
  printf("dns ns count => %d\n", htons(la_dns->dns_header.ns_count));
  printf("dns ar count => %d\n", htons(la_dns->dns_header.ar_count));
  printf("First question hostname => %s\n", la_dns->data);
}

void parse_layer_application_dns(t_list data, u_char *buffer)
{
  layer_application_dns *la_dns;
  size_t len;

  if ((la_dns = malloc(sizeof(layer_application_dns))) == NULL)
    xexit();
  bzero(la_dns, sizeof(layer_application_dns));
  la_dns->header.type = NODE_TYPE_DNS;
  memcpy(&(la_dns->dns_header), buffer, sizeof(t_dns_header));
  if (la_dns->dns_header.qd_count > 0)
    {
      len = strlen((char *) buffer + sizeof(t_dns_header));
      if ((la_dns->data = malloc(len + 1)) == NULL)
	xexit();
      memcpy(la_dns->data, (u_char *) buffer + sizeof(t_dns_header), len + 1);
    }
  if (list_add_elem_at_back(&data, la_dns) == glFALSE)
    xexit();
}
