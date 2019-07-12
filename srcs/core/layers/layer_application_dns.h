#ifndef		LAYER_APPLICATION_DNS_H_
# define	LAYER_APPLICATION_DNS_H_

#include <stdint.h>
#include <sys/types.h>
#include "layer_list_node.h"
#include "../../generic-list/generic_list.h"

/*
 * Doc here for header :
 * http://www.tcpipguide.com/free/t_DNSMessageHeaderandQuestionSectionFormat.htm
 *
 * and :
 * http://www.tcpipguide.com/free/t_DNSMessageResourceRecordFieldFormats.htm
 *
 * and :
 * http://www.networksorcery.com/enp/protocol/dns.htm
 */

typedef struct s_dns_question {
  uint16_t type;
  uint16_t class;
} t_dns_question;

typedef struct s_dns_answer   {
  uint16_t type;
  uint16_t class;
  uint32_t ttl;
  uint16_t rdata_length;
  uint16_t rdata;
} t_dns_answer;

typedef	struct s_dns_header {
  uint16_t	id;
  uint8_t	rd : 1;
  uint8_t	tc : 1;
  uint8_t	aa : 1;
  uint8_t	opcode : 4;
  uint8_t	qr : 1;
  uint8_t	rcode : 4;
  uint8_t	cd : 1;
  uint8_t	ad : 1;
  uint8_t	z : 1;
  uint8_t	ra : 1;
  uint16_t	qd_count;
  uint16_t	an_count;
  uint16_t	ns_count;
  uint16_t	ar_count;
}		t_dns_header;

typedef struct s_layer_application_dns {
  layer_node	header;
  t_dns_header	dns_header;
  uint8_t	*data;
  t_list	questions;
  t_list	answers;
  t_list	authorities;
  t_list	additional;
} layer_application_dns;

void parse_layer_application_dns(t_list data, u_char *buffer);
void dump_layer_application_dns(layer_application_dns *la_dns);
void free_layer_application_dns(layer_application_dns *la_dns);

#endif /* !LAYER_APPLICATION_DNS_H_ */
