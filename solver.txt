import sys, time, copy

def rowno(i):
    return i // 9

def colno(i):
    return i % 9

def boxno(i):
    return (i // 9 // 3 )*3 + (i // 3) % 3

def getFileName():
    if sys.platform == "win32":
        filename = input("Filename? ")
    else:
        filename = sys.argv[-1]
    return filename
    
class Cell:
    def __init__(self, value):
        self.value = value
        if value == '0':
            self.candidates = ['1','2','3','4','5','6','7','8','9']
        else:
            self.candidates = [value]
        
    def __str__(self):
        return str(self.value)

    def delCandidate(self, value):
        # deletes value from candidate list
        if value in self.candidates:
            self.candidates.remove(value)      
  
    def setValue(self, val):
        self.value = str(val)
        self.candidates = [str(val)]
    
class Board:
    def __init__(self, puzzle):
        self.puzzle = []
        for i in range(0, len(puzzle)):
            cell = Cell(puzzle[i])
            self.puzzle.append(cell)
        for i in range(0, len(self.puzzle)):
            if self.puzzle[i].value != '0':
                self.solveOne(i, self.puzzle[i].value)
            
    def __str__(self):
        temp = ''
        for i in range(0, len(self.puzzle)):
            temp +=(self.puzzle[i].value)            
        return temp
        
    def findMin(self):
        length = 10
        sq = 81
        for i in range(0, len(self.puzzle)):
            if self.puzzle[i].value == '0' and len(self.puzzle[i].candidates) < length:
                length = len(self.puzzle[i].candidates)
                sq = i        
        return sq
    
    def solveOne(self, sq, val):
        self.puzzle[sq].setValue(val)
        row = rowno(sq)
        col = colno(sq)
        box = boxno(sq)
        for i in range(0, len(self.puzzle)):
            if i == sq:
                continue
            elif row == rowno(i) or col == colno(i) or box == boxno(i):
                self.puzzle[i].delCandidate(val)
            
def solve(bd):
    before = time.clock()
    wklist = [bd]
    solnlist = []
    count = 0
    while wklist and len(solnlist) < 2:
        board = wklist.pop()
        if board.findMin() == 81: # no unsolved squares
            solnlist.append(board)
            continue
        sq = board.findMin()        
        for v in board.puzzle[sq].candidates:
            tmp = copy.deepcopy(board)
            count += 1
            tmp.solveOne(sq, v)
            wklist.append(tmp)
    after = time.clock()    
    print("Boards generated:", count)       
    print("Time: %0.2f sec." % (after-before))  
    print("Solutions:", len(solnlist))
    return solnlist

def main():
    filename = getFileName()
    file = open(filename, 'r')
    tmpstr = file.readline().strip()
    puzzle = ''
    while tmpstr != "":
        puzzle += tmpstr
        tmpstr = file.readline().strip()
    board = Board(puzzle)
    print(board)
    soln = solve(board)                
    for i in range(0, len(soln)):
        print(soln[i])
main()