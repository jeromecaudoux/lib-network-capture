#include <pcap.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "xexit.h"
#include "pcap.h"

FILE* pcap_init_file(const char *path)
{
  struct pcap_file_header	file_header;
  FILE *fd;

  file_header.magic = 0xa1b2c3d4;
  file_header.version_major = 2;
  file_header.version_minor = 4;
  file_header.thiszone = 0;
  file_header.sigfigs = 0;
  file_header.snaplen = 65535;
  file_header.linktype = DLT_EN10MB;

  if (!(fd = fopen(path, "w")))
  {
    perror("unable to open file");
    xexit();
  }

  if ((fwrite((char*)&file_header, sizeof(struct pcap_file_header), 1, fd)) != 1)
  {
    perror("unable to write file");
    xexit();
  }

  fflush(fd);

  return fd;
}

int pcap_read_header(FILE *fd, struct pcap_file_header *header)
{
  if (fread(header, sizeof(struct pcap_file_header), 1, fd) != 1)
    {
      perror("unable to read file");
      return 0;
    }
  return 1;
}

int pcap_read_packet(FILE *fd, struct pcap_sf_pkthdr *header, u_char *buffer)
{
  int output;

  if ((output = fread(header, sizeof(struct pcap_sf_pkthdr), 1, fd)) != 1)
    return output;
  if ((output = fread(buffer, header->caplen, 1, fd)) != 1)
    return output;
  return 1;
}

void pcap_write_packet(FILE *fd,
		       bpf_int32 sec,
		       bpf_int32 usec,
		       bpf_u_int32 caplen,
		       bpf_u_int32 len,
		       u_char* data)
{
  struct pcap_sf_pkthdr packet_header;

  packet_header.ts.tv_sec = sec;
  packet_header.ts.tv_usec = usec;
  packet_header.caplen = caplen;
  packet_header.len = len;

  if ((fwrite((char*)&packet_header, sizeof(struct pcap_sf_pkthdr), 1, fd)) != 1) {
    perror("unable to write file");
    xexit();
  }
  if ((fwrite((char*)data, caplen, 1, fd)) != 1) {
    perror("unable to write file");
    xexit();
  }
  fflush(fd);
}

void pcap_close_file(FILE *fd)
{
  fclose(fd);
}
