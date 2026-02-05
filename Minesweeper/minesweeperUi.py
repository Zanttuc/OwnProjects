import random
import tkinter as tk

from tkinter import PhotoImage

#Game constants
BOARD_ROW_SIZE = 15
BOARD_COL_SIZE = 15
NUM_MINES = 50

class Stopwatch:
    def __init__(self, timer):
        self.timer = timer
        self.running = False
        self.elapsed_time = 0

    def start(self):
        if not self.running:
            self.running = True
            self.update_elapsed_time()
    
    def stop(self):
        if self.running:
            self.running = False

    def update_elapsed_time(self):
        if self.running:
            self.elapsed_time += 1
            self.timer.after(1000, self.update_elapsed_time)
        self.timer.config(text=self.elapsed_time)

class Cell:
    def __init__(self, row: int, col: int):
        self.row = row
        self.col = col
        self.is_mine = False
        self.is_flagged = False
        self.is_revealed = False
        self.adjacent_mines = 0

class Minesweeper:
    def __init__(self, master):
        self.master = master
        self.board = self.create_board()
        self.num_of_revealed = 0
        self.mines_left = NUM_MINES
        self.game_over = False
        self.image_null = PhotoImage(file="graphics/empty_59x59.png")
        self.image_smiley = PhotoImage(file="graphics/smiley_small.png")
        self.image_smiley_dead = PhotoImage(file="graphics/smiley_small_dead.png")
        self.image_flag = PhotoImage(file="graphics/flag_small.png")
        self.image_mine = PhotoImage(file="graphics/mine_small.png")
        self.image_black = PhotoImage(file="graphics/black.png")
        self.stopwatch = None
        self.add_mines()
        self.check_adjacent_mines()
        self.create_grid()

    def create_board(self):
        board = []
        for row in range(BOARD_ROW_SIZE):
            board.append([])
            for col in range(BOARD_COL_SIZE):
                board[row].append(Cell(row, col))
        return board

    def add_mines(self):
        mines_to_plant = NUM_MINES
        attempts = 0
        max_attempts = BOARD_ROW_SIZE * BOARD_COL_SIZE
        while mines_to_plant != 0 and attempts < max_attempts:
            random_row = random.randint(0, BOARD_ROW_SIZE - 1)
            random_col = random.randint(0, BOARD_COL_SIZE - 1)
            if not self.board[random_row][random_col].is_mine:
                self.board[random_row][random_col].is_mine = True
                mines_to_plant -= 1
            attempts += 1

    def check_adjacent_mines(self):
        for row in range(BOARD_ROW_SIZE):
            for col in range(BOARD_COL_SIZE):
                if not self.board[row][col].is_mine:
                    for neighbor_row, neighbor_col in [
                        (row - 1, col),
                        (row + 1, col),
                        (row, col - 1),
                        (row, col + 1),
                        (row - 1, col - 1),
                        (row - 1, col + 1),
                        (row + 1, col - 1),
                        (row + 1, col + 1)
                    ]:
                        if (
                            0 <= neighbor_row < len(self.board)
                            and 0 <= neighbor_col < len(self.board[0])
                        ):
                            if self.board[neighbor_row][neighbor_col].is_mine:
                                self.board[row][col].adjacent_mines += 1

    def create_grid(self):
        mineCounter = tk.Label(
            master=self.master,
            text=self.mines_left,
            font=("Arial", 25),
            fg="red",
            image=self.image_black,
            compound="c",
            relief="sunken"
        )
        mineCounter.grid()

        newGameButton = tk.Button(
            self.master,
            image=self.image_smiley,
            anchor=tk.CENTER,
            command=self.new_game
        )
        middle = BOARD_COL_SIZE//2
        newGameButton.grid(row=0, column=middle)

        timer = tk.Label(
            master=self.master,
            font=("Arial", 25),
            text="0",
            fg="red",
            image=self.image_black,
            compound="c",
            relief="sunken"
        )
        timer.grid(row=0, column=BOARD_COL_SIZE-1)
        self.stopwatch = Stopwatch(timer)

        for row in range(BOARD_ROW_SIZE):
            for col in range(BOARD_COL_SIZE):
                button = tk.Button(
                    self.master,
                    text="",
                    font=("Arial", 25),
                    image=self.image_null,
                    compound="c",
                    command=lambda r=row, c=col: self.reveal_cell(r, c)
                )
                button.bind("<Button-3>", lambda event, r=row, c=col: self.right_click(r, c))
                button.grid(row=row+1, column=col)

    def right_click(self, row, col):
        self.stopwatch.start()
        if not self.board[row][col].is_revealed:
            if self.board[row][col].is_flagged:
                self.board[row][col].is_flagged = False
                self.mines_left += 1
                self.master.grid_slaves(row=row+1, column=col)[0].config(
                    image=self.image_null
                )
                self.master.grid_slaves(0, 0)[0].config(
                    text=self.mines_left
                )
            else:
                self.board[row][col].is_flagged = True
                self.mines_left -= 1
                self.master.grid_slaves(row=row+1, column=col)[0].config(
                    image=self.image_flag
                )
                self.master.grid_slaves(0, 0)[0].config(
                    text=self.mines_left
                )

    def new_game(self):
        self.master.destroy()
        main()

    def reveal_cell(self, row, col):
        if not self.game_over:
            self.stopwatch.start()
        if not self.board[row][col].is_flagged:
            if self.board[row][col].is_revealed:
                flags_around = 0
                neighbors = [
                    (row - 1, col),
                    (row + 1, col),
                    (row, col - 1),
                    (row, col + 1),
                    (row - 1, col - 1),
                    (row - 1, col + 1),
                    (row + 1, col - 1),
                    (row + 1, col + 1)
                ]
                for neighbor_row, neighbor_col in neighbors:
                    if (
                        0 <= neighbor_row < len(self.board)
                        and 0 <= neighbor_col < len(self.board[0])
                    ):
                        if self.board[neighbor_row][neighbor_col].is_flagged:
                            flags_around += 1

                if flags_around == self.board[row][col].adjacent_mines:
                    for neighbor_row, neighbor_col in neighbors:
                        if (
                            0 <= neighbor_row < len(self.board)
                            and 0 <= neighbor_col < len(self.board[0])
                        ):
                            if not self.board[neighbor_row][neighbor_col].is_flagged and not self.board[neighbor_row][neighbor_col].is_revealed and not self.board[neighbor_row][neighbor_col].is_mine:
                                self.reveal_cell(neighbor_row, neighbor_col)
            elif not self.board[row][col].is_revealed:
                self.board[row][col].is_revealed = True
                self.num_of_revealed += 1
                if self.board[row][col].is_mine:
                    self.game_over = True
                    self.reveal_all()
                elif self.board[row][col].adjacent_mines == 0:
                    for neighbor_row, neighbor_col in [
                        (row - 1, col),
                        (row + 1, col),
                        (row, col - 1),
                        (row, col + 1),
                        (row - 1, col - 1),
                        (row - 1, col + 1),
                        (row + 1, col - 1),
                        (row + 1, col + 1)
                    ]:
                        if (
                            0 <= neighbor_row < len(self.board)
                            and 0 <= neighbor_col < len(self.board[0])
                        ):
                            if not self.board[neighbor_row][neighbor_col].is_mine:
                                self.reveal_cell(neighbor_row, neighbor_col)
                # Update button text based on revealed cell info
                button_text = ""
                button_text_color = "black"
                button_background = "#cecece"
                button_relief = "sunken"
                button_image = self.image_null
                if self.board[row][col].is_mine:
                    button_relief = "raised"
                    button_image = self.image_mine
                    self.master.grid_slaves(row=0, column=BOARD_COL_SIZE//2)[0].config(
                        image=self.image_smiley_dead
                    )
                elif self.board[row][col].adjacent_mines > 0:
                    button_text = self.board[row][col].adjacent_mines
                    if button_text == 1:
                        button_text_color = "#0100fb"
                    elif button_text == 2:
                        button_text_color = "#027f01"
                    elif button_text == 3:
                        button_text_color = "#f70302"
                    elif button_text == 4:
                        button_text_color = "#01007f"
                    elif button_text == 5:
                        button_text_color = "#7d0302"
                    elif button_text == 6:
                        button_text_color = "#00817f"
                    elif button_text == 7:
                        button_text_color = "#000000"
                    elif button_text == 8:
                        button_text_color = "#808080"
                    
                self.master.grid_slaves(row=row+1, column=col)[0].config(text=button_text, 
                                                                         fg=button_text_color, 
                                                                         bg=button_background, 
                                                                         relief=button_relief,
                                                                         image=button_image)
                if self.num_of_revealed == BOARD_ROW_SIZE * BOARD_COL_SIZE - NUM_MINES:
                    self.game_over = True
                    self.reveal_all()

    def reveal_all(self):
        self.stopwatch.stop()
        # Reveal all cells after game over
        for row in range(BOARD_ROW_SIZE):
            for col in range(BOARD_COL_SIZE):
                self.reveal_cell(row, col)

    def printBoard(self): #Only for developing purposes
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
                if cell.is_mine:
                        print("M", end="  ")
                else:
                        print(cell.adjacent_mines, end="  ")
            print("\n")


def main():
    # Create the main window and initialize the game
    root = tk.Tk()
    root.title("Minesweeper")
    game = Minesweeper(root)
    root.mainloop()


if __name__ == "__main__":
    main()