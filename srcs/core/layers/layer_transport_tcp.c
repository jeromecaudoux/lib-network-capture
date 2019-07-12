#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "layer_transport_tcp.h"
#include "layer_application_http.h"
#include "layer_application_dns.h"
#include "../xexit.h"

static const struct application supported_applications[] = {
  {80, "HTTP", parse_layer_application_http},
  {53, "DNS", parse_layer_application_dns},
  {0, NULL, NULL}
};

static int match_port(layer_transport_tcp *lt_tcp, int port)
{
  return htons(lt_tcp->tcphdr.source) == port || htons(lt_tcp->tcphdr.dest) == port;
}

static void parse_next_layer(layer_transport_tcp *lt_tcp, t_list data, u_char *buffer)
{
  struct application application;
  int i;

  if (lt_tcp->tcphdr.fin)
    return ;
  i = 0;
  application = supported_applications[i];
  while (application.func_parse != NULL)
    {
      if (match_port(lt_tcp, application.port))
	{
	  (application.func_parse)(data, buffer);
	  return ;
	}
	application = supported_applications[++i];
    }
}

const char *get_tcp_application_name(layer_transport_tcp *lt_tcp)
{
  struct application application;
  int i;

  if (lt_tcp->tcphdr.fin)
    return "--";
  i = 0;
  application = supported_applications[i];
  while (application.func_parse != NULL)
    {
      if (match_port(lt_tcp, application.port))
	return application.name;
      application = supported_applications[++i];
    }
  return "--";
}

void dump_layer_transport_tcp(layer_transport_tcp *lt_tcp)
{
  printf("Src Port => %d\n", htons(lt_tcp->tcphdr.source));
  printf("Dst Port => %d\n", htons(lt_tcp->tcphdr.dest));
  printf("Sequence number => %d\n", htons(lt_tcp->tcphdr.seq));
  printf("Sequence ack => %d\n", htons(lt_tcp->tcphdr.ack_seq));
  printf("Window => %d\n", htons(lt_tcp->tcphdr.window));
  printf("Checksum => 0x%02x\n", htons(lt_tcp->tcphdr.check));
  printf("Urg ptr => %d\n", htons(lt_tcp->tcphdr.urg_ptr));
  printf("Data offset => %d\n", lt_tcp->tcphdr.doff);
}

void parse_layer_transport_tcp(t_list data, u_char *buffer)
{
  layer_transport_tcp *lt_tcp;

  if ((lt_tcp = malloc(sizeof(layer_transport_tcp))) == NULL)
    xexit();
  lt_tcp->header.type = NODE_TYPE_TCP;
  memcpy(&(lt_tcp->tcphdr), buffer, sizeof(struct tcphdr));
  if (list_add_elem_at_back(&data, lt_tcp) == glFALSE)
    xexit();
  parse_next_layer(lt_tcp, data, (u_char *)buffer + (lt_tcp->tcphdr.doff * 4));
}
