/*

|‾‾‾‾‾‾‾‾‾‾‾‾‾‾|‾‾‾‾˙˙˙˙‾‾‾‾|‾‾‾‾‾‾‾‾‾‾‾‾|
| packet_start |            | packet_end |
|______________|____̣̣ ̣ ̣ ̣ ____|____________|

*/

#ifndef COMMAND_CODES

// Here reside the command codes for
// the ramanPi project

#define packet_start        0xF0
#define packet_ok			0xF1
#define packet_series		0xF2
#define packet_end          0xF3
#define packet_final		0xF4 // for a series of packets

#define packet_int			0xF6 // flags to indicate what kind
#define packet_float		0xF7 // of data is being sent in the
#define packet_double		0xF8 // packet

#define packet_error		0xFF

#define cmd_laser           0xA0
#define laser_on       	    0xA1
#define laser_off           0xA2
#define shutter_open        0xA3
#define shutter_close       0xA4
#define laser_temp          0xA5

#define cmd_cuvette         0xB0
#define tray_open           0xB1
#define tray_close          0xB2
#define tray_heat           0xB3
#define tray_cool           0xB4
#define tray_temp           0xB5

#define cmd_filter          0xC0
#define filter_open         0xC1
#define filter_forward      0xC2
#define filter_backward     0xC3

#define cmd_ccd_pelt        0xD0
#define ccd_heat            0xD1
#define ccd_cool            0xD2

#endif