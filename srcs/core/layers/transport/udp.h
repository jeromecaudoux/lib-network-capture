#ifndef		LAYER_TRANSPORT_UDP_H_
# define	LAYER_TRANSPORT_UDP_H_

#include <netinet/udp.h>
#include <sys/types.h>
#include "../layer_list_node.h"
#include "../../../generic-list/generic_list.h"

/*
 * Documentation :
 * http://lxr.free-electrons.com/source/include/uapi/linux/udp.h
 */

typedef struct s_layer_transport_udp {
  layer_node	header;
  struct udphdr	udphdr;
} layer_transport_udp;

const char *get_udp_application_name(layer_transport_udp *lt_udp);
void parse_layer_transport_udp(t_list data, u_char *buffer);
void dump_layer_transport_udp(layer_transport_udp *ethernet);

#endif /* !LAYER_TRANSPORT_UDP_H_ */
