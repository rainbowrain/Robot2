from serial import *

class SerialWrapper:
    
    
    def __init__(self, port):
        self.ser = Serial(port, 9600, timeout=1)
        self.numBytesInBuffer = 0
        self.buffer = [0 for i in range(0, 256)]
                
    def readCommand(self):
        """ Returns a byte of full sentences where sentences are deliminated by '\n'. Does not parse to make sure
        the commands are in valid format
        """
        
        """ Pseudo-code: read as much as will fit in the buffer, locate the first '\n' from the end of the 
        number of bytes in the buffer which corresponds to a complete instruction, copy them to a buffer that is
        to be returned, and push the remaining bytes corresponding to an incomplete instruction to the front of the 
        buffer
        """
        if(not self.ser.isOpen()):
            print("Cannot read data - Serial port not open")
            sys.exit(1)
        
        numBytesToRead = self.ser.inWaiting()
        roomAvailable = len(self.buffer) - self.numBytesInBuffer

        if numBytesToRead > roomAvailable:
            numBytesToRead = roomAvailable 
        
        for i in range(0, numBytesToRead):
            self.buffer[self.numBytesInBuffer+i] = self.ser.read(1)
        
        self.numBytesInBuffer = self.numBytesInBuffer + numBytesToRead
        
        j = self.numBytesInBuffer - 1 # index of the last read byte in the buffer
        while j>=0:
            if(self.buffer[j]=='\n'): break
            j = j-1
            
        if j<0:
            #print("Could not find a complete instruction.")
            return []
        
        toReturn = [self.buffer[i] for i in range(0, j+1)] # include the '\n'
        
        numExtraBytes = self.numBytesInBuffer - (j+1) # note: unchecked for OBOB
    
        for i in range(0, numExtraBytes):
            self.buffer[i] = self.buffer[j+1+i]
        
        self.numBytesInBuffer = numExtraBytes
        
        self.sanitize(toReturn) # remove any preceding garbage
        
        return toReturn
    
    def close(self):
        self.ser.close()
    
    def sanitize(self, byteArray):
        i = 0
        for i in range(0, len(byteArray)):
            if byteArray[i]=='$':
                break
        byteArray = byteArray[i:len(byteArray)]