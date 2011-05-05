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

#include "read_socket.h"
#include "move_robot.h"

int finished = 0;

void *read_socket(void *id)
{

    double angle = 0, distance = 0;
#ifdef DEBUG
    printf("en read_socket thread\n");
#endif

    do {
        bzero(buffer_socket, BUFSIZE);
        addr_size = BUFSIZE;
        bytes_read =
            recvfrom(server_sock, buffer_socket, BUFSIZE, 0,
                     (struct sockaddr *) &addr_server, &addr_size);

        if (bytes_read > 0) {
            sscanf(buffer_socket, "mv %lf %lf", &distance, &angle);
            printf("distancia : %lf angulo: %lf\n", distance, angle);
            move_robot("tx8", distance, angle, 0.0);
			distance = 0;
			angle = 0;
			/*
            if (sendto
                (server_sock, buffer_socket, bytes_read, 0,
                 (struct sockaddr *) &addr_server, addr_size) < 0)
                perror("reply");
			*/
        } else
            perror("recvfrom");
    } while (bytes_read > 0);
    pthread_exit(NULL);
}
