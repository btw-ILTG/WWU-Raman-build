#Testing daisy chaining serial connections to the Nucleo boards --Stefan Hess

import time
import serial

packet_start = chr(0xF0)
packet_flag = chr(0xF2)
packet_end = chr(0xF3)

control_board = chr(0xA0)
interface_board = chr(0xA1)
imaging_board = chr(0xA2)
    

serial = serial.Serial("/dev/ttyAMA0", baudrate=9600, write_timeout=3.0, stopbits=1)

while(1):
	serial.write(packet_start+packet_flag+control_board+packet_end)
	time.sleep(2)
	serial.write(packet_start+packet_flag+control_board+packet_end)
	time.sleep(2)

	serial.write(packet_start+packet_flag+interface_board+packet_end)
	time.sleep(2)
	serial.write(packet_start+packet_flag+interface_board+packet_end)
	time.sleep(2)

	serial.write(packet_start+packet_flag+imaging_board+packet_end)
	time.sleep(2)
	serial.write(packet_start+packet_flag+imaging_board+packet_end)
	time.sleep(2)
