from Window import Window
from numpy import *
import time
from MyDataSource import MyDataSource

port = "COM16"
#serial = Serial(port, 9600, timeout=1)
serial = MyDataSource()
descriptors = ['test'] # the descriptors to be monitored for
global_data = {} # global data tracker used by all other components

view = Window(global_data) # give the view a reference to the data

dataBuffer = ""
def readMsg(ds): # reads ONE sentence and stores the rest in a buffer
    global dataBuffer
    dataBuffer += ds.read(ds.available()) # ds must implement ds.read()->string and ds.available()->int
    deliminatorIndex = dataBuffer.find('\n')
    if(deliminatorIndex < 0):
        print("EOF not found")
        return []
    sentence = dataBuffer[0:dataBuffer.index('\n')]
    dataBuffer = dataBuffer[dataBuffer.index('\n')+1 : len(dataBuffer)] # incompleted sentences
    if(sentence[0] != "$"):
        print("In-complete message. Did not find '$'")
        return []
    parts = sentence.split(',')
    parts[0] = parts[0][1:len(parts[0])]
    return parts
    
def updateRows():
    for descriptor in descriptors:
        if len(global_data[descriptor]['value']) == 0:
            view.setSensorValue(descriptor, 0)
        else:
            view.setSensorValue(descriptor, global_data[descriptor]['value'][-1])

def readData():
    global global_data
    message = readMsg(serial)
    if(len(message)==0):
        print("Message was empty")
        return
    descriptor = message[0]
    time = message[1]
    value = message[2]
    if(descriptor not in global_data.keys()):
        print("Unrecognized value: " + descriptor)
        return
    
    global_data[descriptor]['time'].append(time)
    global_data[descriptor]['value'].append(value)
    
    
def loop():
    readData()
    view.update()
    
for descriptor in descriptors:
    global_data[descriptor] = {
                            'time': [],
                            'value': []
                            }
    view.addSensorDisplay(descriptor, 0)
    
view.schedule(loop, 100)

view.begin()

serial.close()


