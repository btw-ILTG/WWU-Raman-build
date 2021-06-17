#Felicia's version of control board 
# Now modified by Stefan Hess starting 6/17/2021

import time
import serial

packet_start = chr(0xF0)
packet_flag = chr(0xF2)
packet_end = chr(0xF3)

cmd_laser = chr(0xA0)
laser_on = chr(0xA1)
laser_off = chr(0xA2)
shutter_open = chr(0xA3)
shutter_close = chr(0xA4)
laser_temp = chr(0xA5)

cmd_cuvette = chr(0xB0)
tray_open = chr(0xB1)
tray_close = chr(0xB2)
tray_heat = chr(0xB3)
tray_cool = chr(0xB4)
tray_temp = chr(0xB5)

cmd_filter = chr(0xC0)
filter_open = chr(0xC1)
filter_forward = chr(0xC2)
filter_back = chr(0xC3)

cmd_ccd_pelt = chr(0xD0)
ccd_heat = chr(0xD1)
ccd_cool = chr(0xD2)

def laserOn():
    print 'req laser on.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(laser_on)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())

def laserOff():
    print 'req laser off.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(laser_off)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())

def shutterOpen():
    print 'req shutter open.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(shutter_open)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())
    
def shutterClose():
    print 'req shutter close.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(shutter_close)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())
    
def laserTemp():
    print 'req laser temp.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_laser)
    serial.write(laser_temp)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())
    
def trayOpen():
    print 'req tray open.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_open)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())

def trayClose():
    print 'req tray close.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_close)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())
    
def trayHeat():
    print 'req tray heat.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_heat)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())
    
def trayCool():
    print 'req tray cool.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_cool)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())
    
def trayTemp():
    print 'req tray temp.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_cuvette)
    serial.write(tray_temp)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())

def filterForward():
    print 'req filter forward.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_filter)
    serial.write(filter_forward)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())
    
def filterBack():
    print 'req filter back.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_filter)
    serial.write(filter_back)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())

def ccdHeat():
    print 'req ccd heat.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_ccd_pelt)
    serial.write(ccd_heat)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())
    
def ccdCool():
    print 'req ccd cool.\n'
    serial.write(packet_start)
    serial.write(packet_flag)
    serial.write(cmd_ccd_pelt)
    serial.write(ccd_cool)
    serial.write(packet_flag)
    serial.write(packet_start)
    print(serial.readline())
    

serial = serial.Serial("/dev/serial0", baudrate=921600, timeout=3.0)

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

while(1):
    laserOn()
    time.sleep(5)
    laserOff()

