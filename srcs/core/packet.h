#ifndef		PARSE_PACKET_H_
# define	PARSE_PACKET_H_

#include "../generic-list/generic_list.h"
#include "layers/layer_list_node.h"

typedef struct s_parse_params {
  layer_node	header;
  u_char	*buffer; /* tmp buffer while parsing*/
  unsigned long timestamp;
  ssize_t	packet_size;
  int		parse_error_layer; /* -1 if no error or the layer level */
} parse_params;

t_list   parse_packet(ssize_t packet_size, u_char *buffer);
void     clear_packet_data_node(void *addr);
t_list   parse_packet(ssize_t packet_size, u_char *buffer);
void	 dump_packet_data_node(void *addr);
t_list create_and_fill_params(ssize_t packet_size, u_char *buffer);

#endif /* !PARSE_PACKET_H_ */
