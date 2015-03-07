from Tkinter import *

class GridCanvas:

    def __init__(self, master, width):
        height = (9.0/8.0)*width
        
        self.numRow = 10
        self.numCol = 9
        self.lineWidth = 1
        
        self.canvas = Canvas(master, width=width, height=height)
        
        rowPadding = ( height-(self.lineWidth*self.numRow) ) / (self.numRow-1)
        colPadding = ( width-(self.lineWidth*self.numCol) ) /(self.numCol-1)
        
        # needs offset of 2 from the top-left hand corner in order to show on the screen - determined experimentally
        for i in range(0, self.numRow):
            self.canvas.create_line(0, 2+ rowPadding*i + self.lineWidth*i, width, 2+ rowPadding*i + self.lineWidth*i)
        for i in range(0, self.numCol):
            self.canvas.create_line(2+ colPadding*i + self.lineWidth*i, 0, 2+ colPadding*i + self.lineWidth*i, height)
        
        self.canvas.pack()
        
if __name__ == "__main__":
    master = Tk()
    GridCanvas(master, 609)
    mainloop()
        