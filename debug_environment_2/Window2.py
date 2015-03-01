import matplotlib
matplotlib.use('TkAgg')
from numpy import arange, sin, pi
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
# implement the default mpl key bindings
from matplotlib.backend_bases import key_press_handler
import Tkinter as Tk


class Window:

    def __init__(self):
        self.root = Tk.Tk()
        quit_button = Tk.Button(self.root, text="Quit", command=self.quit)
        quit_button.pack(side=Tk.BOTTOM)
        
    def runMainLoop(self):
        Tk.mainloop()
        
    def add_figure(self, f):
        c = FigureCanvasTkAgg(f, master=self.root)
        c.get_tk_widget().pack() # canvas.draw will update
        
    def quit(self):
        self.root.quit()     # stops mainloop
        self.root.destroy()
        
    def _schedule(self, *args):
        delay, func, fargs = args
        func(*fargs) # call function with parameters expanded
        self.root.after(delay, self._schedule, delay, func, fargs)
        
    def schedule(self, func, delay, *args):
        self.root.after(delay, self._schedule, delay, func, args )