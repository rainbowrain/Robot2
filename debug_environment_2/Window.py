import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from numpy import arange, sin, pi
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
# implement the default mpl key bindings
from matplotlib.backend_bases import key_press_handler
from Tkinter import *
import matplotlib.animation as animation


class Window:

    def __init__(self, data):
        """ Creates a window with an internal frame representing a table with three
        columns: name, value, and open graph.
        
        Key Arguments:
        
        callback - function that takes a string. This function is called when an 'open graph' button is pressed
        and it is passed the name of the sensor to be opened.
        
        """
        self.root = Tk()
        
        titleFont = ("Arial", 16, "bold")
    
                
        # sensor table
        self.sensorTable = Frame(master=self.root)
        self.sensorNameColumn = LabelFrame(self.sensorTable, text="Name", font=titleFont)
        self.sensorNameColumn.grid(row = 0, column = 0)
        self.sensorValueColumn = LabelFrame(self.sensorTable, text="Value", font=titleFont)
        self.sensorValueColumn.grid(row = 0, column = 1)
        self.sensorButtonColumn = LabelFrame(self.sensorTable, text="Button", font=titleFont)
        self.sensorButtonColumn.grid(row = 0, column = 2)
        self.sensorRows = {} # do we really need to keep track of this?
        self.sensorTable.pack()
        
        self.figures = {}
        self.axes = {}
        self.lines = {}
        
        self.data = data
        
        self.sensorDisplayButtonCallback = self.openGraph
            
        quit_button = Button(self.root, text="Quit", command=self.quit)
        quit_button.pack(side=BOTTOM)
        
        plt.ion()
    
    def addSensorDisplay(self, name, value=0):
        """ Creates a new sensor row in the sensor table, packs it, and returns a SensorRowDisplay object that can be used to set the value
        """
        self.sensorRows[name] = SensorRowDisplay(self.sensorNameColumn,
                                                self.sensorValueColumn,
                                                self.sensorButtonColumn,
                                                name,
                                                float(value),
                                                self.sensorDisplayButtonCallback)
        self.sensorRows[name].pack()
        return self.sensorRows[name]

    def openGraph(self, name):
        self.figures[name] = plt.figure()
        self.axes[name] = self.figures[name].add_subplot(1,1,1) # two rows, one column, first plot
        self.lines[name] = self.axes[name].plot(self.data[name]['time'], self.data[name]['value'], "r-", animated=True)[0]
        animation.FuncAnimation(self.figures[name] , self.animate, None, 
                                      interval=0, blit=True)
        plt.show()
        print("Graph opened")
        return 
    
    def update(self):
        self.updateTableRows()
        
    def updateTableRows(self):
        for descriptor in self.sensorRows.keys():
            if len(self.data[descriptor])==0:
                self.sensorRows[descriptor].setValue(-1)
            else:
                self.sensorRows[descriptor].setValue(self.data[descriptor]['value'][-1])
        
    
    def animate(self, i):
        for descriptor in self.lines.keys():
            line = self.lines[descriptor]
            line.set_ydata(self.data[descriptor]['value'])
        print("animation called")
        return list(self.lines.values())
    
    #def updateGraphs(self):
    #    for descriptor in self.axes.keys():
    #        # relies on the fact that only the end data point may not be on the graph
    #        self.axes[descriptor].scatter(self.data[descriptor]['time'][-1], self.data[descriptor]['value'][-1])
    #    #plt.pause(0.01)

        
    def begin(self):
        mainloop()
        
    def quit(self):
        self.root.quit()     # stops mainloop
        self.root.destroy()
        
    def _schedule(self, *args):
        delay, func, fargs = args
        func(*fargs) # call function with parameters expanded
        self.root.after(delay, self._schedule, delay, func, fargs)
        
    def schedule(self, func, delay, *args):
        self.root.after(delay, self._schedule, delay, func, args )
        
        
class SensorRowDisplay:
    
    def __init__(self, nameLabelMaster, valueLabelMaster, buttonMaster, name, value, callback):
        self.valueVar = StringVar()
        self.nameLabel = Label(master=nameLabelMaster, text=name)
        self.valueLabel = Label(master=valueLabelMaster, textvariable=self.valueVar)
        self.valueVar.set(value)
        self.button = Button(master=buttonMaster, text='display', command= lambda: callback(name) )
        
    
    def pack(self):
        self.nameLabel.pack()
        self.valueLabel.pack()
        self.button.pack()
        
    def setValue(self, value):
        self.valueVar.set(value)
        
if __name__=="__main__":
    
    def openGraph(str):
        print(str)
    
    w = Window(openGraph)
    frontRightIRView = w.addSensorDisplay('Front Right IR', 20)
    frontRightIRView.setValue(50)
    frontRightIRView = w.addSensorDisplay('Front Left IR', 20)
    w.begin()
    