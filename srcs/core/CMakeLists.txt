CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(network-security-1)

SET(HEADER
  xexit.c
  network_capture.h
  pcap.h
  packet.h
  forge.h
  layers/link/ethernet.h
  layers/network/ipv4.h
  layers/transport/tcp.h
  layers/transport/udp.h
  layers/application/http.h
  layers/application/dns.h
  )

SET(SOURCES
  xexit.c
  network_capture.c
  pcap.c
  packet.c
  forge.c
  layers/link/ethernet.c
  layers/network/ipv4.c
  layers/transport/tcp.c
  layers/transport/udp.c
  layers/application/http.c
  layers/application/dns.c
  )

SET(NS1_CORE_LIBRARY_NAME ns1-core)
ADD_LIBRARY(${NS1_CORE_LIBRARY_NAME} ${SOURCES} ${HEADERS})

TARGET_LINK_LIBRARIES(${NS1_BINARY_NAME} generic-list)

IF (UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -Werror")
endif (UNIX)
