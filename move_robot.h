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

#ifndef _MOVE_ROBOT_H
#define _MOVE_ROBOT_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "cssl.h"
#include <math.h>

extern cssl_t *serial_port;
extern unsigned int value;
extern int rotate_diff;
extern int zeros_rot_count;
extern int translate_diff;
extern int zeros_trans_count;
extern int client_sock;
extern struct sockaddr_in addr_client;


#define M_PI	3.14159265358979323846  /* pi */
#define M_PI_2	1.57079632679489661923  /* pi/2 */

void move_robot(char *name, double distance, double angle, double speed);
int translate(double distance);
int rotate(double angle);
int secs_to_micro(float seconds);
void mysleep(float seconds);


#endif                          /* _MOVE_ROBOT_H */
