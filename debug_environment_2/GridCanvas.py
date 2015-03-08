from Tkinter import *
import cmath

PI = 3.14159265

class GridCanvas:

    def __init__(self, master, width):
        
        self.computeGridParameters(width)
        self.robotWidth = self.colPadding / 2
        
        self.canvas = Canvas(master, width=self.width, height=self.height, bg="white")
        
        self.drawGrid()
        
        self.canvas.pack()

    def drawRobot(self, x, y, angle): # where x and y are the center of the robot
        r = self.robotWidth/2
        c1 = complex(x-r, y-r)
        c2 = complex(x+r, y-r)
        c3 = complex(x+r, y+r)
        c4 = complex(x-r, y+r)
        center = complex(x, y)
        t = cmath.exp(angle * 1j) # transformation
        
        c1 = t * (c1 - center) + center
        c2 = t * (c2 - center) + center
        c3 = t * (c3 - center) + center
        c4 = t * (c4 - center) + center
        
        self.canvas.create_polygon(c1.real, c1.imag,
                                    c2.real, c2.imag,
                                    c3.real, c3.imag,
                                    c4.real, c4.imag,
                                    fill="blue")
        
    def computeGridParameters(self, width):
        self.width = width
        self.height = (9.0/8.0)*width

        self.offset = 1
        self.numRow = 10
        self.numCol = 9
        self.lineWidth = 2
        
        self.offset = self.offset + self.lineWidth # determined experimentally
        
        self.rowPadding = int( ( ( self.height-(self.lineWidth*self.numRow) ) / (self.numRow-1) ) + 0.5 )
        self.colPadding = int( ( ( self.width-(self.lineWidth*self.numCol) ) /(self.numCol-1) ) + 0.5 )
        
        #re-compute width and height based on integer values of rowPadding and colPadding
        
        self.height = ( self.rowPadding * (self.numRow-1) ) + ( self.lineWidth * self.numRow)
        self.width = self.colPadding * (self.numCol-1) + self.lineWidth * self.numCol
        
    
        
    def drawGrid(self):
        # needs offset of 2 from the top-left hand corner in order to show on the screen - determined experimentally
        for i in range(0, self.numRow):
            self.canvas.create_line(self.offset+ 0, self.offset+ self.rowPadding*i + self.lineWidth*i, self.offset+ self.width, self.offset+ self.rowPadding*i + self.lineWidth*i, width=self.lineWidth)
        for i in range(0, self.numCol):
            self.canvas.create_line(self.offset+ self.colPadding*i + self.lineWidth*i, self.offset+ 0, self.offset+ self.colPadding*i + self.lineWidth*i, self.offset+ self.height, width=self.lineWidth)
        
        # draw center red line
        centreX = ( self.colPadding * (self.numCol-1) / 2 ) + ( self.lineWidth * (self.numCol-1) / 2 )
        self.canvas.create_line(self.offset+ centreX, self.offset+ 0 , self.offset+ centreX, self.offset+ self.height , width=self.lineWidth, fill="red")

    


if __name__ == "__main__":
    master = Tk()
    GridCanvas(master, 400)
    mainloop()
        