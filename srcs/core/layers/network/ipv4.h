#ifndef		LAYER_NETWORK_IPV4_H_
# define	LAYER_NETWORK_IPV4_H_

#include <netinet/ip.h>
#include <sys/types.h>
#include "../layer_list_node.h"
#include "../../../generic-list/generic_list.h"

/*
 * Documentation :
 * http://lxr.free-electrons.com/source/include/uapi/linux/ip.h
 */

typedef struct s_layer_network_ipv4 {
  layer_node	header;
  struct iphdr	iphdr;
} layer_network_ipv4;

const char *get_transport_layer_name(struct iphdr *iphdr);
void parse_layer_network_ipv4(t_list data, u_char *buffer);
void dump_layer_network_ipv4(layer_network_ipv4 *ethernet);

#endif /* !LAYER_NETWORK_IPV4_H_ */
