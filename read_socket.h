/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _READ_SOCKET_H
#define _READ_SOCKET_H

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include "cssl.h"

#define BUFSIZE	1024

extern struct sockaddr_in addr_server, addr_client;
extern cssl_t *serial_port;
extern int server_sock, client_sock, bytes_read, fd;
extern unsigned int addr_size;


extern char buffer_socket[BUFSIZE];

void *read_socket(void *id);

#endif                          /* _READ_SOCKET_H */
