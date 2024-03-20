import random

#Game constants
BOARD_SIZE = 9
NUM_MINES = 10

class Cell:
    def __init__(self, row: int, col: int, isMine = False):
        self.row = row
        self.col = col
        self.isMine = isMine
        self.isFlagged = False
        self.isRevealed = False
        self.adjacentMines = 0

class Minesweeper:
    def __init__(self, master):
        self.board = self.createBoard()
        self.numOfRevealed = 0
        self.gameOver = False
        self.addMines()
        self.checkAdjacentMines()
        self.createGrid()

    def createBoard(self):
        board = []
        for row in range(BOARD_SIZE):
            board.append([])
            for col in range(BOARD_SIZE):
                board[row].append(Cell(row, col))
        return board
    
    def addMines(self):
        minesToPlant = NUM_MINES
        attempts = 0
        maxAttempts = BOARD_SIZE * BOARD_SIZE
        while minesToPlant != 0 and attempts < maxAttempts:
            randomRow = random.randint(0, BOARD_SIZE-1)
            randomCol = random.randint(0, BOARD_SIZE-1)
            if self.board[randomRow][randomCol].isMine == False:
                self.board[randomRow][randomCol].isMine = True
                minesToPlant -= 1
            attempts +=1
    
    def checkAdjacentMines(self):
        for row in range(BOARD_SIZE):
            for col in range(BOARD_SIZE):
                if not self.board[row][col].isMine:
                    for neighbor_row, neighbor_col in [(row - 1, col), (row + 1, col),
                                                       (row, col - 1), (row, col + 1),
                                                       (row - 1, col - 1), (row - 1, col + 1),
                                                       (row + 1, col - 1), (row + 1, col + 1)]:
                        if 0 <= neighbor_row < len(self.board) and 0 <= neighbor_col < len(self.board[0]):
                            if self.board[neighbor_row][neighbor_col].isMine:
                                self.board[row][col].adjacentMines += 1

    def printBoard(self):
        rowNum = 0
        print("  ", end=" ")
        for colNum in range(len(self.board)):
            colNum += 1
            print(colNum, end=". ")
        print()
        for row in self.board:
            rowNum += 1
            print(rowNum, end=". ")
            for cell in row:
                if cell.isRevealed:
                    if cell.isMine:
                        print("M", end="  ")
                    else:
                        print(cell.adjacentMines, end="  ")
                elif cell.isFlagged:
                    print("F", end="  ")
                else:
                    print("\u2588", end="  ")
            print("\n")

    def revealCell(self, row: int, col: int, flag: bool):
        if not self.board[row][col].isRevealed:
            if flag:
                self.board[row][col].isFlagged = True
            else:
                self.board[row][col].isRevealed = True
                self.numOfRevealed += 1
                if self.board[row][col].isMine:
                    self.gameOver = True
                    self.revealAll()
                    self.printBoard()
                    print("That was a mine!\nGame Over!")
                elif self.board[row][col].adjacentMines == 0:
                    for neighbor_row, neighbor_col in [(row - 1, col), (row + 1, col),
                                                    (row, col - 1), (row, col + 1)]:
                        if 0 <= neighbor_row < len(self.board) and 0 <= neighbor_col < len(self.board[0]):
                            self.revealCell(neighbor_row, neighbor_col, False)
                            
        if self.numOfRevealed == BOARD_SIZE*BOARD_SIZE - NUM_MINES:
            self.gameOver = True
            self.revealAll()
            self.printBoard()
            print("You won!")

    def revealAll(self):
        for row in range(BOARD_SIZE):
            for col in range(BOARD_SIZE):
                self.board[row][col].isRevealed = True

        
def getUserInput():
    flag = False
    while True:
        userInput = input(f"Please enter a row and column of the tile you want to open seperated by comma. "
                           "If you want to flag a tile, input 'f'': ")
        if userInput == "f":
            flag = True
            userInput = input("Please enter a row and column of the tile you want to flag seperated by comma: ")
        try: 
            num1, num2 = map(int, userInput.split(","))
            return num1, num2, flag
        except:
            print("Invalid input. Please try again: ")
            userInput = getUserInput()


minesweeper = Minesweeper()
while minesweeper.gameOver == False:
    minesweeper.printBoard()
    row, col, flag = getUserInput()
    minesweeper.revealCell(row-1, col-1, flag)
