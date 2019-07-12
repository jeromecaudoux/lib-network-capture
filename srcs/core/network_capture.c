#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <errno.h>
#include "network_capture.h"
#include "xexit.h"
#include "pcap.h"
#include "packet.h"

void	start_capture_to_file(t_packet_handler handler, void *param, const char *path)
{
  u_char	buffer[MAX_BUFFER_SIZE];
  int		socket_fd;
  FILE		*fd;
  ssize_t	nb_bytes;
  t_list	packet_data;
  struct timeval ts;

  if ((socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
  {
    perror(NULL);
    return;
  }

  fd = pcap_init_file(path);
  while ((nb_bytes = recvfrom(socket_fd, buffer, MAX_BUFFER_SIZE, 0, NULL, NULL)) != 0)
  {
    if ((gettimeofday(&ts, 0)))
    {
      perror("Unable to gettimeofday");
      xexit();
    }
    pcap_write_packet(fd, ts.tv_sec, ts.tv_usec, nb_bytes, nb_bytes, buffer);

    packet_data = parse_packet(nb_bytes, buffer);
    handler(packet_data, param);
    list_clear(&packet_data, clear_packet_data_node);
  }
  pcap_close_file(fd);
  close(socket_fd);
  return;
}

void	start_capture_from_file(t_packet_handler handler, void *param, const char *path)
{
  u_char	buffer[MAX_BUFFER_SIZE];
  t_list	packet_data;
  FILE		*fd;
  struct pcap_file_header gheader;
  struct pcap_sf_pkthdr pheader;

  if (!(fd = fopen(path, "r")))
    {
      perror("unable to open file");
      return;
    }

  if (pcap_read_header(fd, &gheader) == 0)
    return ;
  if (gheader.linktype != DLT_EN10MB)
    {
      fprintf(stderr, "File doesn't provide Ethernet headers - not supported\n");
      return;
    }
  while (pcap_read_packet(fd, &pheader, buffer) != 0)
    {
      packet_data = parse_packet(pheader.caplen, buffer);
      handler(packet_data, param);
      list_clear(&packet_data, clear_packet_data_node);
    }
  fclose(fd);
  return;
}

void	start_capture(t_packet_handler handler, void *param)
{
  u_char	buffer[MAX_BUFFER_SIZE];
  int		socket_fd;
  ssize_t	nb_bytes;
  t_list	packet_data;

  if ((socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
    {
      perror(NULL);
      return;
    }

  while ((nb_bytes = recvfrom(socket_fd, buffer, MAX_BUFFER_SIZE, 0, NULL, NULL)) != 0)
    {
      packet_data = parse_packet(nb_bytes, buffer);
      handler(packet_data, param);
      list_clear(&packet_data, clear_packet_data_node);
    }
  close(socket_fd);
  return;
}
