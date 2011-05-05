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

#include "move_robot.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Taken from beeSoft.ini
#define base_encPerCm 212

#define convertMMToEncoders(arg)\
((arg * base_encPerCm) / 10)


int rotating = 0;
int translating = 0;
int stopped = 0;


int secs_to_micro(float seconds)
{
    return (int) (seconds * 1000000);
}

void mysleep(float seconds)
{
    int time_usecs;

    time_usecs = secs_to_micro(seconds);

    select(0, 0, 0, 0, &(struct timeval) {
           .tv_usec = time_usecs});
}



int rotate(double angle)
{
    int r = 0;
    char buffer[1024];
    unsigned int angle_hex = 0;

    /* Set Rotate Velocity */
    /* Default is 0080 */
    //sprintf(buffer, "RV 0100\r");
    //0100 = 256
    float angular_speed = (128 * 2 * M_PI) / 1024;
    double time = fabs(angle) / angular_speed;

    //printf("tiemporot = %d\n", (int) round(time));
    /* Positive Angle */

    translating = 0;


    if (angle > 0) {

        angle_hex = (unsigned int) ((angle * 1024) / (2 * M_PI));


        sprintf(buffer, "R< %4x\r", angle_hex);
        cssl_putstring(serial_port, buffer);
        memset(buffer, 0, sizeof(buffer));

        rotating = 1;

        printf("En move_robot: zeros_rot_count 2+ = %d\n",
               zeros_rot_count);
        //sleep((int)round(time));
        mysleep(round(time));

        printf("deje de rotar\n");

        zeros_rot_count = 0;
        r = 1;
    }

    rotating = 0;
    r = 0;

    if (angle < 0) {
        angle = 0 - angle;
        angle_hex = (unsigned int) ((angle * 1024) / (2 * M_PI));

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "R> %4x\r", angle_hex);
        cssl_putstring(serial_port, buffer);

        rotating = 1;

        //sleep((int)round(time));
        mysleep(round(time));

        printf("deje de rotar\n");

        zeros_rot_count = 0;
        r = 1;

    }

    rotating = 0;
    return r;
}

int translate(double distance)
{
    int t = 0;
    char buffer[1024];
    unsigned int distance_hex = 0;

    //10 cm = 800 unidades en hexadecimal para el robot
    //10 cm = 2120 d
    // de acuerdo a la funcion convertMMToEncoders
    // 6144 es por la velocidad establecida en init_serial.c
    // 1800x = 6144d
    double time = (fabs(distance) * 2120) / 6144;

    printf("distance = %f\n", distance);

    printf("timetrans = %f\n", time);


    rotating = 0;
    printf("voy con la traslacion\n");
    if (distance > 0) {

        distance_hex = (unsigned int) (distance * 2120);

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "T> %4x\r", distance_hex);
        cssl_putstring(serial_port, buffer);


        printf("distance = %f\n", distance);
        printf("distance_hex = %x\n", distance_hex);
        printf("buffer = %s\n", buffer);

        printf("timetrans = %d\n", (int) round(time));
        //sleep((int)round(time));
        mysleep(round(time));

        translating = 1;

        printf("En move_robot: zeros_trans_count 2+ = %d\n",
               zeros_trans_count);


        printf("deje de trasladarme\n");

        zeros_trans_count = 0;
        t = 1;

    }

    translating = 0;
    t = 0;

    if (distance < 0) {
        distance = 0 - distance;

        //distance_hex = (unsigned int)((distance * 1024) / 0.5) ;
        distance_hex = (unsigned int) (distance * 2120);

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "T< %4x\r", distance_hex);
        cssl_putstring(serial_port, buffer);

        printf("-distance = %f\n", distance);
        printf("-distance_hex = %x\n", distance_hex);
        printf("-buffer = %s\n", buffer);


        //sleep((int)round(time));
        mysleep(round(time));

        translating = 1;

        printf("deje de trasladarme\n");

        zeros_trans_count = 0;
        t = 1;
    }

    translating = 0;
    return t;
}


void move_robot(char *name, double distance, double angle, double speed)
{

	char buffer[1024];

    rotate(angle);
    translate(distance);

	sprintf(buffer, "mv %lf %lf", distance, angle);
	sendto(client_sock, buffer, strlen(buffer)+1, 0, (struct sockaddr*)&addr_client, 100);
    memset(buffer, 0, 1024);

}
