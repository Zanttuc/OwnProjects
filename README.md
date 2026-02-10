# OwnProjects

Welcome to my personal collection of projects! 🎉  

This repository contains projects I’ve created primarily to **learn new skills, experiment, and challenge myself**. Each project serves as a learning experience and a reflection of my growth as a programmer. Currently, there are **three projects** in this collection:

---

## Projects

### 1. LeasingDistanceCounter
A **C++ terminal program** designed to track the remaining kilometers in a personal vehicle leasing contract.  

**Purpose:** To manage my car lease efficiently and practice C++ programming in a simple, functional project.  

**How it works:**  
When you run the program, it asks for:
- Lease start date
- Lease length in years
- Contracted kilometer limit
- Driven kilometers  

It then calculates:  
- Kilometers used  
- Kilometers left in total and for the current year  
- Daily allowed kilometers to stay within the contract  

**Example Terminal Output:**
```
Welcome to your leasing car distance counter!
Please set the date you started your lease (DDMMYYYY): 10032023
Please set the length of your leasing contract in years: 4
Please set the limit assigned in your leasing contract in kilometers: 60000
Please set your driven kilometers: 39061

You have used 39061 kilometers.
You have 20939 kilometers left in your leasing contract.
You have 5939 kilometers left for this year.
You have 52 kilometers / day left in your leasing contract.
You have 169 kilometers / day left for this year.

Thank you for using leasing car distance counter - designed by Zanttuc!
```
---
### 2. Minesweeper
A **Python single-file Minesweeper game** with a basic UI built using `tkinter`.  

**Purpose:** To challenge myself to create a working Minesweeper game purely in Python, including the graphical interface, without relying on other UI frameworks.  

**How to run:**  
```
python3 ./minesweeperUI.py
```
**Features:**

- Standard Minesweeper gameplay
- Simple, intuitive interface
- Fully implemented in Python
---
### 3. TowerDrinkingGame

A Python card game for social play. Players guess if the next card is higher or lower than a revealed one in a tower-like layout.

**Purpose:** To create a fun game for friends and practice programming game logic in Python.

Gameplay Overview:
- Cards are dealt in a tower layout
- Reveal corners and middle card
- Players guess higher/lower for neighboring cards
- Correct guess: continue or pass
- Wrong guess: turn ends, cards are redealt, and the player drinks the number of redealt cards
- Game ends when all cards are revealed

**How to run:**
You need to install a couple of libraries to use the application.

Run the following commands:
```
pip install customtkinter
python -m pip install pillow
```
When you have the libraries installed just run ```python3 ./TowerDrinkingGame.py```

**Planned updates:**
- Make the application window scalable
- Add a possibility to change player amount
- Get rid of the popup window after wrong guess and implement it to the player tiles
---
## About Me

I am a self-driven developer who enjoys creating projects for learning and fun. These projects showcase my curiosity and willingness to challenge myself with new languages, logic, and programming concepts.

---
***Designed and coded by Zanttuc***