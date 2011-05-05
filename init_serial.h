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

#ifndef _INIT_SERIAL_H
#define _INIT_SERIAL_H

#include "cssl.h"
#include <unistd.h>
#include <stdio.h>

#define BAUDRATE 9600

#ifdef USB_SERIAL
#define PORT "/dev/ttyUSB0"
#else
#define PORT "/dev/ttyS0"
#endif

cssl_t *serial_port;

#endif                          /* _INIT_SERIAL_H */
