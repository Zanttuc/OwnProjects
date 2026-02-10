import tkinter as tk
import random

from tkinter import messagebox
from customtkinter import CTkButton
from PIL import Image, ImageTk

#Constants
ROW_SIZE = 7 #Changing may results in errors
COL_SIZE = 7 #Changing may results in errors
pathToImageFolder = "Cards/Small"

class Player():
    def __init__(self, name: str, playerNum: int, row = 1, col = 1):
        self.drinkCount = 0
        self.name = name
        self.playerNum = playerNum
        self.row = row
        self.col = col
        self.cardsOpened = 0

class Card():
    def __init__(self, suit: int, num: int, pathToImage=pathToImageFolder):
        self.suit = suit
        self.num = num
        self.isRevealed = False
        self.isHighlighted = False
        self.isCounted = False
        self.imageBlankPath = f"{pathToImage}/blank.png"
        self.imageFacePath = f"{pathToImage}/{num}_{suit}.png" 
        self.imageBackPath = f"{pathToImage}/card_back_small.png"
        self.imageBlank = getImage(self.imageBlankPath)
        self.imageFace = getImage(self.imageFacePath)
        self.imageFaceR = getImage(self.imageFacePath, True, 90)
        self.imageBack = getImage(self.imageBackPath)
        self.imageBackR = getImage(self.imageBackPath, True, 90)
    
class Deck():
    def __init__(self):
        self.__deck = []
        self.hasHiglighted = None
        self.initDeck()
        self.shuffleDeck()

    def initDeck(self):
        for suit in range(4):
            for num in range(13):
                card = Card(suit+1, num+1)
                self.__deck.append(card)
    
    def shuffleDeck(self):
        random.shuffle(self.__deck)

    def getCard(self):
        card = self.__deck.pop(0)
        return card
    
    def returnCardToDeck(self, card: Card):
        self.__deck.append(card)

class Window():
    def __init__(self, master):
        self.master = master
        self.deck = Deck()
        self.players = self.addPlayers()
        self.activePlayer = 0
        self.counter = 0
        self.drinkAmount = 0
        self.totalDrinkAmount = 0
        self.board = self.createBoard()
        self.createWindow()

    def addPlayers(self):
        players = []
        for player in range(4):
            playerName = f"Player {player+1}"
            if player == 0:
                player = Player(playerName, player)
            elif player == 1:
                player = Player(playerName, player, 1, 4)
            elif player == 2:
                player = Player(playerName, player, 4, 4)
            elif player == 3:
                player = Player(playerName, player, 4)
            players.append(player)
        return players

    def createBoard(self):
        board = []
        for row in range(ROW_SIZE):
            board.append([])
            for col in range(COL_SIZE):
                if row in [1, 2, 4, 5] and col in [1, 2, 4, 5]:
                    board[row].append(None)
                else:
                    board[row].append(self.deck.getCard())
        
        return board

        #For development purposes
        for row in board:
            for card in row:
                if card != None:
                    print(card.num, end=" ")
                else:
                    print(" ")
        print("\n")
                
    def createWindow(self):
        #Create buttons for all the cards
        for row in range(ROW_SIZE):
            for col in range(COL_SIZE):
                if row in [1, 2, 4, 5] and col in [1, 2, 4, 5]:
                    pass
                else:
                    button = CTkButton(master=self.master,
                                       image=self.board[row][col].imageBlank,
                                       text="",
                                       font=("helvetica", 30),
                                       corner_radius=20,
                                       fg_color="grey",
                                       hover_color="dark gray",
                                       command=lambda r=row, c=col: self.revealCard(r, c, 1))
                    button.bind("<Button-2>", lambda event, r=row, c=col: self.revealCard(r, c, 2))
                    button.bind("<Button-3>", lambda event, r=row, c=col: self.revealCard(r, c, 3))
                    button.grid(row=row, column=col)
                    self.updatePicture(row, col)

        #Create labels for player stats
        for playerLabel in range(4):
            player = self.players[playerLabel]
            label = tk.Label(master=self.master,
                            text="",
                            height=6,
                            width=18,
                            padx=0,
                            pady=0,
                            compound="c",
                            borderwidth=30,
                            fg="black")
            
            label.grid(row=player.row, column=player.col, columnspan=2, rowspan=2)
            self.updateLabel(player)
            if playerLabel == 0:
                self.master.grid_slaves(row=player.row, column=player.col)[0].configure(relief="sunken",
                                                                                        bd=25,
                                                                                        bg="#2e2e2e",
                                                                                        fg="white")
                
            button = tk.Button(master=self.master,
                            text="End turn",
                            font=("helvetica", 15),
                            command=lambda num = player.playerNum: self.changePlayer(num))
            button.grid(row=player.row+1, column=player.col, columnspan=2)

    def updatePicture(self, row: int, col: int, revealed = False):
        self.counter += 1
        card = self.board[row][col]
        picture = card.imageBlank
        #Add images for revealed and rotated cards
        if row in [0, 6] and col in [0, 6]:
            card.isRevealed = True
            card.isCounted = True
            picture = card.imageFaceR
        #Add image for the revealed center card
        elif row==3 and col==3:
            card.isRevealed = True
            card.isCounted = True
            picture = card.imageFace
        #Add images for unrevealed and rotated cards
        elif row in [0, 6] or col in [1, 2, 4, 5]:
            if revealed:
                picture = card.imageFaceR
            else:
                picture = card.imageBackR
        #Add image for unrevealed not rotated cards
        else:
            if revealed:
                picture = card.imageFace
            else:
                picture = card.imageBack
        self.master.grid_slaves(row=row, column=col)[0].configure(image=picture)

    def updateLabel(self, player):
        updatedText = (f"{player.name}\n"
                       f"Drinks consumed: {player.drinkCount}")
        self.master.grid_slaves(row=player.row, column=player.col)[0].configure(text=updatedText,
                                                                                font=("helvetica", 30),
                                                                                relief="ridge",
                                                                                bd=8,
                                                                                bg="light gray",
                                                                                fg="black")

    def revealCard(self, row: int, col: int, mouseBtn: int):
        card = self.board[row][col]
        player = self.players[self.activePlayer]

        #Check that the card is not already revealed
        if not card.isRevealed:
            #Check that a source card is selected
            if self.deck.hasHiglighted != None:
                #Check that the source card is one of the surrounding cards
                if self.checkSelected(row+1, col) or self.checkSelected(row-1, col) or self.checkSelected(row, col+1) or self.checkSelected(row, col-1):
                    player.cardsOpened += 1

                    #Update image
                    self.updatePicture(row, col, True)

                    #Change reveal status
                    card.isRevealed = True
                    card.isCounted = True
                    self.master.update()

                    if not self.checkValidity(mouseBtn, card):
                        self.calculateDrinks(row, col)
                        self.showMessage(mouseBtn)
                        self.redealCard(row, col)
                        self.changePlayer()
                        player.drinkCount += self.drinkAmount
                        self.updateLabel(player)
                        self.drinkAmount = 0
                        
                    self.deck.hasHiglighted = None
                    
                    
                    
        else:
            color = ""
            #Unselect card
            if card.isHighlighted:
                color = "grey"
                card.isHighlighted = False
                self.deck.hasHiglighted = None
            #Select card
            elif self.deck.hasHiglighted == None:
                color = "red"
                card.isHighlighted = True
                self.deck.hasHiglighted = card
            #Incase card is already selected and user tries to select another card
            else:
                return
            self.master.grid_slaves(row=row, column=col)[0].configure(fg_color=color)
    
    def checkSelected(self, row, col):
        try:
            card = self.board[row][col]
            if card.isHighlighted:
                self.master.grid_slaves(row=row, column=col)[0].configure(fg_color="grey")
                card.isHighlighted = False
                return True
        except:
            return False
        
    def checkValidity(self, mouseBtn: int, card: Card):
        if mouseBtn == 1 and card.num <= self.deck.hasHiglighted.num:
            return False
        elif mouseBtn == 2 and card.num != self.deck.hasHiglighted.num:
            return False
        elif mouseBtn == 3 and card.num >= self.deck.hasHiglighted.num:
            return False
        else:
            return True
        
    def calculateDrinks(self, row: int, col: int):
        card = self.board[row][col]
        if card != None and card.isRevealed:
            if card.isCounted:
                card.isCounted = False
                self.drinkAmount += 1
                for neighborRow, neighborCol in [
                            (row -1, col),
                            (row +1, col),
                            (row, col -1),
                            (row, col +1)
                        ]:
                            if (
                                0 <= neighborRow < len(self.board)
                                and 0 <= neighborCol < len(self.board[0])
                            ):
                                self.calculateDrinks(neighborRow, neighborCol)
        
    def redealCard(self, row: int, col: int):
        card = self.board[row][col]
        if card != None:
            if card.isRevealed:
                card.isRevealed = False
                card.isHighlighted = False
                self.deck.returnCardToDeck(card)
                self.board[row][col] = self.deck.getCard()
                self.updatePicture(row, col)

                for neighborRow, neighborCol in [
                            (row -1, col),
                            (row +1, col),
                            (row, col -1),
                            (row, col +1)
                        ]:
                            if (
                                0 <= neighborRow < len(self.board)
                                and 0 <= neighborCol < len(self.board[0])
                            ):
                                self.redealCard(neighborRow, neighborCol)
        
    def showMessage(self, messageType: int):
        if messageType == 1:
            messagebox.showerror(title="Game Over", message=f"The card you chose was not larger!\n"
                                                            f"Drink {self.drinkAmount}!")
        elif messageType == 2:
            messagebox.showerror(title="Game Over", message=f"The card you chose was not the same!\n"
                                                            f"Drink {self.drinkAmount}!")
        elif messageType == 3:
            messagebox.showerror(title="Game Over", message=f"The card you chose was not smaller!\n"
                                                            f"Drink {self.drinkAmount}!")
            
    def changePlayer(self, playerNum = None):
        previousPlayer = self.players[self.activePlayer]

        if playerNum == None or (playerNum == self.activePlayer and previousPlayer.cardsOpened >= 3):
            if self.activePlayer < 3:
                self.activePlayer += 1
            else:
                self. activePlayer = 0
            nextPlayer = self.players[self.activePlayer]

            previousPlayer.cardsOpened = 0

            self.master.grid_slaves(row=nextPlayer.row, column=nextPlayer.col)[0].configure(relief="sunken",
                                                                                            bd=25,
                                                                                            bg="#2e2e2e",
                                                                                            fg="white")
            self.master.grid_slaves(row=previousPlayer.row, column=previousPlayer.col)[0].configure(relief="ridge",
                                                                                                    bd=8,
                                                                                                    bg="light gray",
                                                                                                    fg="black")
            

    

def getImage(imagePath: str, rotate=False, degrees=0):
    img = Image.open(imagePath)
    
    if rotate:
        img = img.rotate(degrees, expand=True)

    convertedPhoto = ImageTk.PhotoImage(img)
    return convertedPhoto




def main():
    root = tk.Tk()
    root.title("TowerOfDrinks")
    root.geometry("1650x1350")
    root.configure(background="grey")
    
    game = Window(root)
    root.mainloop()

if __name__ == "__main__":
    main()