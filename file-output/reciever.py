import serial

PORT = 'COM4'

file = open('data.txt', 'a')

arduino = serial.Serial(port=PORT, baudrate=115200, timeout=.1)

def read_serial():
    data = arduino.readline()
    return data

while True:
	file.write(read_serial())