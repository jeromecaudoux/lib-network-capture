#ifndef		LAYER_APPLICATION_HTTP_H_
# define	LAYER_APPLICATION_HTTP_H_

#include <stdint.h>
#include <sys/types.h>
#include "layer_list_node.h"
#include "../../generic-list/generic_list.h"

typedef struct s_layer_application_http {
  layer_node	header;
  unsigned int	size;
  uint8_t	*buffer;
} layer_application_http;

void parse_layer_application_http(t_list data, u_char *buffer);
void dump_layer_application_http(layer_application_http *la_http);
void free_layer_application_http(layer_application_http *la_http);

#endif /* !LAYER_APPLICATION_HTTP_H_ */
