CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(generic-list)

SET(HEADER
  generic_list.h
  )

SET(SOURCES
  list_acces_node.c
  list_access_get.c
  list_control.c
  list_infos.c
  list_modif_add.c
  list_modif_del_clear.c
  )

SET(GENERIC_LIST_LIBRARY_NAME generic-list)
ADD_LIBRARY(${GENERIC_LIST_LIBRARY_NAME} STATIC ${SOURCES} ${HEADERS})

IF (UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -Wall -Wextra -Werror")
endif (UNIX)
