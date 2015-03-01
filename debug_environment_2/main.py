from Window import Window
import matplotlib.pyplot as plt
from numpy import *
import time
from SerialWrapper import *

port = "COM16"
serial = SerialWrapper(port)
commands = ['data'] # the 'commands' that will be sent via the arduino. e.g. "$data,1,2\n". 'Command' was probably a bad name for it
global_data = {}
row_displays = {}
figures = {} # maps 'command' to axes

def parseData(byteArray):
    dataString = ''.join(byteArray)
    commands = dataString.split('\n')
    map = {}
    for i in range(0, len(commands)): 
        parts = commands[i].split('$')
        for j in range(0, len(parts)):
            subparts = parts[j].split(',')
            if(subparts[0] == ''): continue
            if subparts[0] in map.keys():
                map[subparts[0]].append(subparts[1:len(subparts)])
            else:
                map[subparts[0]] = [subparts[1:len(subparts)]]
    return map

def loop():
    global global_data
    global view
    data = parseData(serial.readCommand())
    if(not len(data.keys()) == 0):
        for command in data.keys(): # data[command] = [[time, data], [time, data]]
            for data_piece in data[command]:
                try:
                    global_data[command]['time'].append(data_piece[0])
                    global_data[command]['value'].append(data_piece[1])
                except Exception as e:
                    print(data)
                    print(command)
                    print(e)
            #print(global_data[command])
            row_displays[command].setValue(data[command][0][1]) # set it to the first one 'cuz fuck it
            
    # check if a figure is open
    for command in commands:
        if command in figures.keys():
            print("Figure open: " + command)
            ax = figures[command]
            ax.plot(global_data[command]['time'], global_data[command]['value'])
            plt.draw()
        
    
def buttonCallBack(name):
    fig = plt.figure()
    figures[name] = fig.add_subplot(1,1,1) # two rows, one column, first plot
    plt.show()
    
view = Window(buttonCallBack)
for command in commands:
    global_data[command] = {
                            'time': [],
                            'value': []
                            }
    row_displays[command] = view.addSensorDisplay(command, 0)
view.schedule(loop, 100)
plt.show()
view.begin()

serial.close()


