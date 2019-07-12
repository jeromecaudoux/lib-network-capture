#ifndef		LAYER_DATA_LINK_H_
# define	LAYER_DATA_LINK_H_

#include <netinet/ether.h>
#include <sys/types.h>
#include "../layer_list_node.h"
#include "../../../generic-list/generic_list.h"

/*
 * Documentation :
 * http://lxr.free-electrons.com/source/include/uapi/linux/if_ether.h#L46
 */

typedef struct s_layer_ethernet {
  layer_node	header;
  struct ethhdr	ethhdr;
} layer_ethernet;

t_list parse_layer_ethernet(t_list data, u_char *buffer);
void dump_layer_ethernet(layer_ethernet *ethernet);

#endif /* !LAYER_DATA_LINK_H_ */
