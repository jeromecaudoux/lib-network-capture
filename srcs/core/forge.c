#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/udp.h>
#include<netinet/ip.h>
#include <arpa/inet.h>

#include "forge.h"
#include "xexit.h"
#include "layers/layer_application_dns.h"

static void convert_to_dns_name_format(char* data, const char* hostname)
{
  int lock=0 , i;
  char buffer[4096];

  snprintf(buffer, 4096, "%s.", hostname);
  for(i=0 ; i<(int)strlen((char*)buffer) ; i++)
  {
    if(buffer[i]=='.')
    {
      *data = i - lock;
      ++data;
      for( ; lock < i ; lock++)
      {
        *data = buffer[lock];
        ++data;
      }
      lock++;
    }
  }
}

static unsigned short checksum(unsigned short *ptr, unsigned int count) {
  unsigned long sum = 0;

  while (count > 1) {
    sum += * ptr++;
    count -= 2;
  }
  //if any bytes left, pad the bytes and add
  if (count > 0) {
    sum += ((*ptr)&htons(0xFF00));
  }
  //Fold sum to 16 bits: add carrier to result
  while (sum>>16) {
    sum = (sum & 0xffff) + (sum >> 16);
  }
  //one's complement
  sum = ~sum;
  return ((unsigned short)sum);
}

void  forge(const char* source_ip, int port_src, const char* dest_ip, int port_dst, const char *hostname, int ttl)
{
  char *packet;
  int len, s;
  struct sockaddr_in sin;

  if ((s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1) {
    perror("Failed to create raw socket");
    xexit();
  }

  sin.sin_family = AF_INET;
  sin.sin_port = htons(port_dst);
  sin.sin_addr.s_addr = inet_addr (dest_ip);

  len = get_dns_forged_packet(source_ip, port_src, port_dst, hostname, ttl, &packet, &sin);
  if (len > 0 && sendto (s, packet, len,  0, (struct sockaddr *) &sin, sizeof (sin)) < 0)
  {
    perror("sendto failed");
  }
}

int get_dns_forged_packet(const char* source_ip, int port_src, int port_dst, const char *hostname, int ttl, char **packet, struct sockaddr_in *sin)
{
  char datagram[4096];
  char *pseudogram, *dnsqname;
  struct iphdr* iph;
  struct udphdr* udph;
  struct pseudo_header psh;
  t_dns_header* dnsh;
  t_dns_question* dnsq;
  int psize, dnssize;

  memset (datagram, 0, 4096);
  iph = (struct iphdr*) datagram;
  udph = (struct udphdr*) ((char*)iph + sizeof(struct iphdr));
  dnsh = (t_dns_header*) ((char*)udph + sizeof(struct udphdr));
  dnsqname = (char*)dnsh + sizeof(t_dns_header);


  // DNS
  dnsh->id = 1;
  dnsh->qr = 0;
  dnsh->opcode = 0;
  dnsh->aa = 0;
  dnsh->tc = 0;
  dnsh->rd = 1;
  dnsh->ra = 0;
  dnsh->z = 0;
  dnsh->ad = 0;
  dnsh->cd = 0;
  dnsh->rcode = 0;
  dnsh->qd_count = htons(1);
  dnsh->an_count = 0;
  dnsh->ns_count = 0;
  dnsh->ar_count = 0;
  convert_to_dns_name_format(dnsqname, hostname);

  dnsq = (t_dns_question*) (dnsqname + strlen(dnsqname) + 1);
  dnsq->type = htons(1); //ipv4
  dnsq->class = htons(1);

  dnssize = sizeof(t_dns_header) + strlen(dnsqname) + 1 + sizeof(t_dns_question);

  //Fill in the IP Header
  iph->ihl = 5;
  iph->version = 4;
  iph->tos = 0;
  iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + dnssize;
  iph->id = htonl (54321); //Id of this packet
  iph->frag_off = 0;
  iph->ttl = ttl;
  iph->protocol = IPPROTO_UDP;
  iph->check = 0;      //Set to 0 before calculating checksum
  iph->saddr = inet_addr ( source_ip );
  iph->daddr = sin->sin_addr.s_addr;
  iph->check = checksum ((unsigned short *) datagram, iph->tot_len);

  //UDP header
  udph->source = htons (port_src);
  udph->dest = htons (port_dst);
  udph->len = htons(sizeof(struct udphdr) + dnssize);
  udph->check = 0; //leave checksum 0 now, filled later by pseudo header

  //UDP checksum using the pseudo header
  psh.source_address = inet_addr( source_ip );
  psh.dest_address = sin->sin_addr.s_addr;
  psh.reserved = 0;
  psh.protocol = IPPROTO_UDP;
  psh.udp_length = htons(sizeof(struct udphdr) + dnssize);

  psize = sizeof(struct pseudo_header) + sizeof(struct udphdr) + dnssize;
  pseudogram = malloc(psize);

  memcpy(pseudogram , (char*) &psh , sizeof (struct pseudo_header));
  memcpy(pseudogram + sizeof(struct pseudo_header) , udph , sizeof(struct udphdr) + dnssize);

  udph->check = checksum( (unsigned short*) pseudogram, psize);
  
  *packet = 0;
  if (dnssize > 512) {
    printf("UDP DNS payload too large");
    return -1;
  }
  if (!(*packet = malloc(iph->tot_len))) {
    perror("malloc failed");
    xexit();
  }
  memcpy(*packet, datagram, iph->tot_len);
  return iph->tot_len;
}

