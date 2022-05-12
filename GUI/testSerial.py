from  serial import Serial
import time

serialPort = "/dev/ttyACM1"
baudRate = 9600
ser = Serial(serialPort, baudRate, timeout=0, writeTimeout=0)


while True:
    c = ser.read()
    time.sleep(0.2)