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
    

serial = serial.Serial("/dev/ttyAMA0", baudrate=921600, write_timeout=3.0, stopbits=1)
#serial = serial.Serial("/dev/ttyAMA0", baudrate=9600, write_timeout=3.0, stopbits=1)

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
	if data[0] == packet_start[0]:
		if data[1] == packet_int[0]:
			data_int = data[2:-1]
			print(data_int)
			packet_data = int.from_bytes(data_int, "little", signed=True)
			print(packet_data)

		elif data[1] == packet_float[0]:
			data_float = data[2:-1]
			print(data_float)
			packet_data = struct.unpack('f', data_float)
			print(packet_data)

		elif data[1] == packet_double[0]:
			data_double = data[2:-1]
			print(data_double)
			packet_data = struct.unpack('d', data_double)
			print(packet_data)

		elif data[1] == packet_series[0]:
			if data[2] == packet_int[0]:
				print("int series")
				series_flag = 1
				while series_flag == 1:
					series_data = serial.read(6)
					print(series_data)
					if series_data[0] == packet_series[0]:
						if len(series_data) == 3 and series_data[1] == packet_final[0] and series_data[2] == packet_end[0]:
							series_flag = 0
							print("Final packet")
							break
						else:
							data_int = series_data[1:-1]
							print(data_int)
							packet_data = int.from_bytes(data_int, "little", signed=True)
							print(packet_data)

			elif data[2] == packet_float[0]:
				print("float series")
				series_flag = 1
				while series_flag == 1:
					series_data = serial.read(6)
					print(series_data)
					if series_data[0] == packet_series[0]:
						if len(series_data) == 3 and series_data[1] == packet_final[0] and series_data[2] == packet_end[0]:
							series_flag = 0
							print("Final packet")
							break
						else:
							data_float = series_data[1:-1]
							print(data_float)
							packet_data = struct.unpack('f', data_float)
							print(packet_data)

			elif data[2] == packet_double[0]:
				print("double series")
				series_flag = 1
				serial.timeout = 0.002
				while series_flag == 1:
					series_data = serial.read(10)
					print(len(series_data))
					print(series_data)
					if series_data[0] == packet_series[0]:
						if len(series_data) == 3 and series_data[1] == packet_final[0] and series_data[2] == packet_end[0]:
							series_flag = 0
							print("Final packet")
							serial.timeout = None
							break
						else:
							data_double = series_data[1:-1]
							print(data_double)
							packet_data = struct.unpack('d', data_double)
							print(packet_data)
						
					else:
						print("No packet_series")
			
	else:
		print("No packet_start")

serial.timeout = 1
while True:
	#packet = packet_start + cmd_laser + laser_on + packet_end
	#integer_val = 42
	#bin_int = integer_val.to_bytes(4, 'little')
	#bin_float = struct.pack('f', 42)
	#bin_double = struct.pack('d', 42)
	#bin_double1 = struct.pack('d', 84)
	#bin_double2 = struct.pack('d', 168)

	#packet = packet_start + packet_series + packet_double + packet_end
	#serial.timeout = None
	#print(serial.read_until(b'\xf3'))
	#serial.write(packet)
	#serial.timeout = 3
	#time.sleep(3)

	#for i in range(0,50):
	#	bin_double = struct.pack('d', i)
	#	packet = packet_series + bin_double + packet_end
	#	#print(packet)
	#	serial.write(packet)

	#packet = packet_series + packet_final + packet_end
	#serial.write(packet)

	#print(packet)
	#serial.write(packet)
	#packet = packet_series + bin_double1 + packet_end
	#print(packet)
	#serial.write(packet)
	#packet = packet_series + bin_double2 + packet_end
	#print(packet)
	#serial.write(packet)
	#packet = packet_series + packet_final + packet_end
	#print(packet)
	#serial.write(packet)

	#print(serial.read_until(b'\xf3'))

	#data_read = serial.read_until(b'\xf3')	
	##data_read = serial.read()
	#print(data_read)
	#if (len(data_read) > 0):
	#	packet_processor(data_read)

	#data_read = serial.read_until(b'\xf3')	
	#print(data_read)
	#if (len(data_read) > 0):
	#	packet_processor(data_read)
	##input("Press Enter to continue...")

	#while True:
	#	bytes_to_read = serial.in_waiting
	#	print(bytes_to_read)
	#	if(bytes_to_read > 0):
	#		res = serial.read(bytes_to_read)
	#		print(res)
	#		#serial.reset_input_buffer()
	#	time.sleep(0.2)

	print("Looped")
