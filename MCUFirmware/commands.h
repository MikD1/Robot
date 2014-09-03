/*
* commands.h
*
* Created: 27.08.2014 18:47:15
* Author: Mikhail Doshevsky <m.doshevsky@gmail.com>
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#define READ_COMMAND 0x11
#define WRITE_COMMAND 0x12

#define LED_COMMAND 0x20
// arguments:
// bits 7:1 - address
// bit 1 - value

#define SENSOR_COMMAND 0x21
// arguments:
// bits 7:0 - address

#define DRIVE_COMMAND 0x22
// arguments:
// bits 7:2 - motors speed
// bit 1 - M1 direction
// bit 0 - M2 direction

#endif /* COMMANDS_H_ */
