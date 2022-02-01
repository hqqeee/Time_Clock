/*
 * This file contains definitions of Display Codes.
 * Connections:
 * Board Pins | Display Pins
 * PB0 		  | A
 * PB1 		  | B
 * PB2 		  | C
 * PB3 		  | D
 * PB4 		  | E
 * PB5 		  | F
 * PB6 		  | G
 * PB7        | Anode DIG-1
 * PB8        | Anode DIG-2
 * PB9        | Anode DIG-3
 * PB10       | Anode DIG-4
 * PB11       | Anode DIG-5
 * PB12       | Anode DIG-6
 *
 *	  PB0
 * PB5   PB1
 * PB5   PB1
 *    PB6
 * PB4   PB2
 * PB4   PB2
 *    PB3
 */

#ifndef __DISPLAY_CODES_H
#define __DISPLAY_CODES_H

#define DISP_0 0x3FU
#define DISP_1 0x06U
#define DISP_2 0x5BU
#define DISP_3 0x4FU
#define DISP_4 0x66U
#define DISP_5 0x6DU
#define DISP_6 0x7DU
#define DISP_7 0x07U
#define DISP_8 0x7FU
#define DISP_9 0x6FU
#define DISP_H 0x76U
#define DISP_A 0x77U
#define DISP_E 0x79U
#define DISP_L 0x38U
#define DISP_P 0x73U
#define DIG1_MSK 0xFF00U
#define DIG2_MSK 0xFE80U
#define DIG3_MSK 0xFD80U
#define DIG4_MSK 0xFB80U
#define DIG5_MSK 0xF780U
#define DIG6_MSK 0xEF80U

#endif /* __DISPLAY_CODES_H */
