#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tcp.h"
#include "udp.h"
#include "../application/dns.h"
#include "../../xexit.h"

static const struct application supported_applications[] = {
  {53, "DNS", parse_layer_application_dns},
  {0, NULL, NULL}
};

static int match_port(layer_transport_udp *lt_udp, int port)
{
  return htons(lt_udp->udphdr.source) == port || htons(lt_udp->udphdr.dest) == port;
}

static void parse_next_layer(layer_transport_udp *lt_udp, t_list data, u_char *buffer)
{
  struct application application;
  int i;

  i = 0;
  application = supported_applications[i];
  while (application.func_parse != NULL)
    {
      if (match_port(lt_udp, application.port))
	{
	  (application.func_parse)(data, buffer);
	  return ;
	}
      application = supported_applications[++i];
    }
}

const char *get_udp_application_name(layer_transport_udp *lt_udp)
{
  struct application application;
  int i;

  i = 0;
  application = supported_applications[i];
  while (application.func_parse != NULL)
    {
      if (match_port(lt_udp, application.port))
	return application.name;
      application = supported_applications[++i];
    }
  return "--";
}

void dump_layer_transport_udp(layer_transport_udp *lt_udp)
{
  printf("Src Port => %d\n", htons(lt_udp->udphdr.source));
  printf("Dst Port => %d\n", htons(lt_udp->udphdr.dest));
  printf("Datagram size => %d\n", htons(lt_udp->udphdr.len));
  printf("Checksum => 0x%02x\n", htons(lt_udp->udphdr.check));
}

void parse_layer_transport_udp(t_list data, u_char *buffer)
{
  layer_transport_udp *lt_udp;

  if ((lt_udp = malloc(sizeof(layer_transport_udp))) == NULL)
    xexit();
  memset(lt_udp, 0, sizeof(layer_transport_udp));
  lt_udp->header.type = NODE_TYPE_UDP;
  memcpy(&(lt_udp->udphdr), buffer, sizeof(struct udphdr));
  if (list_add_elem_at_back(&data, lt_udp) == glFALSE)
    xexit();
  parse_next_layer(lt_udp, data, (u_char *)buffer + sizeof(struct udphdr));
}
