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

#include "init_socket.h"

int init_socket(void)
{

    int in_port  = 2000;
	int out_port = 2001; 

    server_sock = socket(PF_INET, SOCK_DGRAM, 0);
    client_sock = socket(PF_INET, SOCK_DGRAM, 0);

    if (server_sock < 0) {
        perror("socket");
        abort();
    }
    addr_server.sin_family      = AF_INET;
    addr_server.sin_port        = htons(in_port);
    addr_server.sin_addr.s_addr = INADDR_ANY;

    addr_client.sin_family      = AF_INET;
    addr_client.sin_port        = htons(out_port);
	inet_aton("127.0.0.1", &addr_client.sin_addr);

    if (bind(server_sock, (struct sockaddr *) &addr_server, sizeof(addr_server)) < 0) {
        perror("bind");
        abort();
    }
    return 0;
}

void kill_socket(void)
{
    close(server_sock);
}
