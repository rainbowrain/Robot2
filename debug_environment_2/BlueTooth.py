from bluetooth import *
import sys

class BTClient:
    
    def __init__(self, deviceName):
        """ Connects to nearby device with user friendly name 'name'
        """
        nearby_devices = discover_devices(duration=2, lookup_names=True, lookup_class=False)
        
        for (addr, name) in nearby_devices:
            if name==deviceName:
                 print(" Device found: %s - %s" % (addr, name))
                 self.socket=BluetoothSocket( RFCOMM )
                 self.socket.connect((addr, 1)) # need to specify port
                 self.socket.send("hello world")
                 print("data sent")



if (__name__ == "__main__"):
    BTClient("HC-05")

