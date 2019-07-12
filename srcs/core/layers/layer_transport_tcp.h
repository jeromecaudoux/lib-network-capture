#ifndef		LAYER_TRANSPORT_TCP_H_
# define	LAYER_TRANSPORT_TCP_H_

#include <netinet/tcp.h>
#include <sys/types.h>
#include "layer_list_node.h"
#include "../../generic-list/generic_list.h"

struct application {
  ushort port;
  const char *name;
  void (*func_parse)(t_list data, u_char *buffer);
};

/*
 * Documentation :
 * http://lxr.free-electrons.com/source/include/uapi/linux/tcp.h
 */

typedef struct s_layer_transport_tcp {
  layer_node	header;
  struct tcphdr	tcphdr;
} layer_transport_tcp;

const char *get_tcp_application_name(layer_transport_tcp *lt_tcp);
void parse_layer_transport_tcp(t_list data, u_char *buffer);
void dump_layer_transport_tcp(layer_transport_tcp *ethernet);

#endif /* !LAYER_TRANSPORT_TCP_H_ */
