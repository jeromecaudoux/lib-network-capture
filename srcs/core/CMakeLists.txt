CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(network-security-1)

SET(HEADER
  xexit.c
  network_capture.h
  pcap.h
  packet.h
  forge.h
  layers/layer_data_link_ethernet.h
  layers/layer_network_ipv4.h
  layers/layer_transport_tcp.h
  layers/layer_transport_udp.h
  layers/layer_application_http.h
  layers/layer_application_dns.h
  )

SET(SOURCES
  xexit.c
  network_capture.c
  pcap.c
  packet.c
  forge.c
  layers/layer_data_link_ethernet.c
  layers/layer_network_ipv4.c
  layers/layer_transport_tcp.c
  layers/layer_transport_udp.c
  layers/layer_application_http.c
  layers/layer_application_dns.c
  )

SET(NS1_CORE_LIBRARY_NAME ns1-core)
ADD_LIBRARY(${NS1_CORE_LIBRARY_NAME} ${SOURCES} ${HEADERS})

TARGET_LINK_LIBRARIES(${NS1_BINARY_NAME} generic-list)

IF (UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -Werror")
endif (UNIX)
