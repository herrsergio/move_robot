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

#include "read_serial.h"
#include <string.h>

extern int rotating;
extern int translating;
extern int stopped;

void read_serial_port(int id, uint8_t * buf, int buflen)
{

    if (rotating) {             // Kill Herr Sergio.
        translating = 0;
        rotate_diff = 0;
        if (buf[0] != '\r') {
            sscanf((char *) buf, "RVE %4x", &value);
            printf("En read_serial: value rot = %4x\n", value);
            if (value > 0x0000) {
                rotate_diff = 1;
                zeros_rot_count = 0;
            } else if (value == 0x0000) {
                rotate_diff = 0;
                zeros_rot_count++;
                printf("En read_serial: zeros_rot_count = %d\n",
                       zeros_rot_count);
            }
        }
    }

    if (translating) {          // Kill Herr Sergio.
        rotating = 0;
        translate_diff = 0;
        if (buf[0] != '\r') {
            sscanf((char *) buf, "TVE %4x", &value);
            printf("En read_serial: value trans = %4x\n", value);
            if (value > 0x0000) {
                translate_diff = 1;
                zeros_trans_count = 0;
            } else if (value == 0x0000) {
                translate_diff = 0;
                zeros_trans_count++;
                printf("En read_serial: zeros_trans_count = %d\n",
                       zeros_trans_count);
            }
        }
    }

    if (stopped) {
        zeros_trans_count = 0;
        zeros_rot_count = 0;
        translate_diff = 0;
        rotate_diff = 0;
    }



    memset(buf, 0, 8);

}
