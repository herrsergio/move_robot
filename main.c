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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>


#define USB_SERIAL
#define DEBUG

#include "init_serial.h"
#include "init_socket.h"
#include "move_robot.h"
#include "read_serial.h"
#include "read_socket.h"

extern int finished;
extern char data_port;

int main(int argc, char *argv[])
{

    pthread_t lesen_thread[2];

    //init_serial_port();
    init_socket();

    pthread_create(&lesen_thread[1], NULL, read_socket, NULL);

    //square 1
    /*
       move_robot("tx8", 5.0, 0.0, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 0.0, M_PI_2, 0.0);
     */

    //square 2
    /*
       move_robot("tx8", 5.0, 0.0, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 0.0, M_PI_2, 0.0);

       //square 2
       move_robot("tx8", 5.0, 0.0, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 0.0, M_PI_2, 0.0);

       //square 2
       move_robot("tx8", 5.0, 0.0, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 5.0, M_PI_2, 0.0);
       move_robot("tx8", 0.0, M_PI_2, 0.0);
     */

    pthread_exit(NULL);
    kill_socket();
    //cssl_close(serial_port);
    //cssl_stop();

    return 0;
}
