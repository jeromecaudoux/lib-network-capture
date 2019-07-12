#ifndef		LAYER_DATA_NODE_H_
# define	LAYER_DATA_NODE_H_

#include <sys/types.h>

#define NODE_TYPE_PARSE_PARAMS 0
#define NODE_TYPE_ETHERNET 1
#define NODE_TYPE_IPV4 2
#define NODE_TYPE_TCP 3
#define NODE_TYPE_UDP 4
#define NODE_TYPE_HTTP 5
#define NODE_TYPE_DNS 6

typedef struct s_layer_node {
  ushort type;
} layer_node;


#endif /* !LAYER_DATA_NODE_H_ */
