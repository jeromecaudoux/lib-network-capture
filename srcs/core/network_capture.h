#ifndef		NETWORK_CAPTURE_H_
# define	NETWORK_CAPTURE_H_

#include "layers/layer_list_node.h"
#include "../generic-list/generic_list.h"

#define MAX_BUFFER_SIZE 65535

typedef void		(*t_packet_handler)(t_list data, void *param);

void start_capture(t_packet_handler handler, void *param);
void start_capture_to_file(t_packet_handler handler, void *param, const char *path);
void start_capture_from_file(t_packet_handler handler, void *param, const char *path);

#endif /* !NETWORK_CAPTURE_H_ */
