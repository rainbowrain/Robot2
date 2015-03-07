from serial import *

class MyDataSource:
    
    def __init__(self):

        self.ser = Serial("COM16", 9600, timeout=0) # Where should these configurations such as COM port go?
    
    def read(self, n=1):
        str = self.ser.readline()
        return str
        
    def available(self):
        self.ser.inWaiting()
    
    def close(self):
        return