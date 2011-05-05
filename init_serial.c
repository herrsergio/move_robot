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

#include "init_serial.h"
#include "read_serial.h"
#include <string.h>
#include <stdlib.h>

void init_serial_port(void)
{
    char buffer[1024];

    cssl_start();

    /* cssl_open(path, callback_function, id, baud, bits, parity, stopbits); */

    //serial_port = cssl_open("/dev/ttyUSB0", read_serial_port, 0, 9600, 8, 0, 1);
    serial_port = cssl_open("/dev/ttyUSB0", NULL, 0, 9600, 8, 0, 1);

    if (!serial_port) {
        printf("%s\n", cssl_geterrormsg());
        exit(1);
    }

    /* Set Half Duplex Mode */
    sprintf(buffer, "HD\r");
    cssl_putstring(serial_port, buffer);
    memset(buffer, 0, 1024);

    /* Set Translate Velocity */
    /* Default is 0800 */
    sprintf(buffer, "TV 1800\r");
    cssl_putstring(serial_port, buffer);
    memset(buffer, 0, 1024);

    /* Set Translate Acceleration */
    /* Default is 4000 */
    sprintf(buffer, "TA 8000\r");
    cssl_putstring(serial_port, buffer);
    memset(buffer, 0, 1024);

    /* Set Rotate Acceleration */
    /* Default is 0400 */
    sprintf(buffer, "RA 0800\r");
    cssl_putstring(serial_port, buffer);
    memset(buffer, 0, 1024);

    /* Set Rotate Velocity */
    /* Default is 0080 */
    sprintf(buffer, "RV 0100\r");
    cssl_putstring(serial_port, buffer);
    memset(buffer, 0, 1024);

    cssl_settimeout(serial_port, 10000);
    cssl_drain(serial_port);

}
