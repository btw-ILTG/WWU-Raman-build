#Felicia's version of control board 
# Now modified by Stefan Hess starting 6/17/2021

import time
import serial
import numpy as np
import struct

packet_start = b'\xf0'
packet_ok = b'\xf1'
packet_series = b'\xf2'
packet_end = b'\xf3'
packet_final = b'\xf4'

packet_int = b'\xf6'
packet_float = b'\xf7'
packet_double = b'\xf8'

packet_error = b'\xff'

cmd_laser = b'\xa0'
laser_on = b'\xa1'
laser_off = b'\xa2'
shutter_open = b'\xa3'
shutter_close = b'\xa4'
laser_temp = b'\xa5'

cmd_cuvette = b'\xb0'
tray_open = b'\xb1'
tray_close = b'\xb2'
tray_heat = b'\xb3'
tray_cool = b'\xb4'
tray_temp = b'\xb5'

cmd_filter = b'\xc0'
filter_open = b'\xc1'
filter_forward = b'\xc2'
filter_back = b'\xc3'

cmd_ccd_pelt = b'\xd0'
ccd_heat = b'\xd1'
ccd_cool = b'\xd2'

def laserOn():
    print('req laser on.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(laser_on)
    serial.write(packet_end)
    print(serial.readline())

def laserOff():
    print('req laser off.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(laser_off)
    serial.write(packet_end)
    print(serial.readline())

def shutterOpen():
    print('req shutter open.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(shutter_open)
    serial.write(packet_end)
    print(serial.readline())
    
def shutterClose():
    print('req shutter close.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(shutter_close)
    serial.write(packet_end)
    print(serial.readline()) 

def laserTemp():
    print('req laser temp.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(laser_temp)
    serial.write(packet_end)
    print(serial.readline())
    
def trayOpen():
    print('req tray open.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_open)
    serial.write(packet_end)
    print(serial.readline())

def trayClose():
    print('req tray close.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_close)
    serial.write(packet_end)
    print(serial.readline())
    
def trayHeat():
    print('req tray heat.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_heat)
    serial.write(packet_end)
    print(serial.readline())
    
def trayCool():
    print('req tray cool.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_cool)
    serial.write(packet_end)
    print(serial.readline())
    
def trayTemp():
    print('req tray temp.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_temp)
    serial.write(packet_end)
    print(serial.readline())

def filterForward():
    print('req filter forward.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_filter)
    serial.write(filter_forward)
    serial.write(packet_end)
    print(serial.readline())
    
def filterBack():
    print('req filter back.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_filter)
    serial.write(filter_back)
    serial.write(packet_end)
    print(serial.readline())

def ccdHeat():
    print('req ccd heat.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_ccd_pelt)
    serial.write(ccd_heat)
    serial.write(packet_end)
    print(serial.readline())
    
def ccdCool():
    print('req ccd cool.\n')
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_ccd_pelt)
    serial.write(ccd_cool)
    serial.write(packet_end)
    print(serial.readline())
    

serial = serial.Serial("/dev/ttyAMA0", baudrate=9600, write_timeout=3.0, stopbits=1)

#call functions below-

#trayOpen()
#
#time.sleep(5)
#
#trayClose()
#
#time.sleep(5)
#
#ccdCool()

#while(1):

#msg = "HeLlo"
#msg_byte = msg.encode('utf-8')
#bytes_written = serial.write(msg_byte)
#print("Bytes written: ", bytes_written)

#while True:
#msg = "This is a very long message to see how much of the buffer stays so I can figure out if I need to have a certain read interval to not loose the data that I need"

#for i in range(1, 500):
	#msg = msg + " " + str(i)

#msg_byte = msg.encode('utf-8')
#bytes_written = serial.write(msg_byte)
#print("Bytes written: ", bytes_written)
#msg_test = "Hi"
#packet = packet_start + packet_flag + cmd_laser + packet_end
#serial.write(packet)
#data = data[:-1]	
#size = 300
#struct_string = ''
#for i in range(0,size):
#		struct_string = struct_string + 'd'	

#print(struct.unpack(struct_string, data))

def packet_processor(data):
	if data[0].to_bytes(1, "little") == packet_start:
		if data[1].to_bytes(1, "little") == packet_int:
			data_int = data[2:-1]
			print(data_int)
			packet_data = int.from_bytes(data_int, "little", signed=True)
			print(packet_data)

		elif data[1].to_bytes(1, "little") == packet_float:
			data_float = data[2:-1]
			print(data_float)
			packet_data = struct.unpack('f', data_float)
			print(packet_data)

		elif data[1].to_bytes(1, "little") == packet_double:
			data_double = data[2:-1]
			print(data_double)
			packet_data = struct.unpack('d', data_double)
			print(packet_data)
	else:
		print("No packet_start")

while True:
	data_read = serial.read_until(b'\xf3')	
	#data_read = serial.read()
	print(data_read)
	packet_processor(data_read)
	print("Looped")
