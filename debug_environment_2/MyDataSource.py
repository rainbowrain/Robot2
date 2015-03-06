class MyDataSource:
    
    def __init__(self):
        self.x = 0
        self.y = 0
    
    def read(self, n=1):
        self.x += 1
        self.y += 1
        return "$test," + str(self.x) + "," + str(self.y) + "\n"
        
    def available(self):
        return 1
    
    def close(self):
        return