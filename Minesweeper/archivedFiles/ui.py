import tkinter as tk

class ButtonHandler:
  def __init__(self, button):
    self.button = button
    self.button.config(command=self.change_relief)

  def change_relief(self):
    current_relief = self.button["relief"]
    if current_relief == "raised":
        self.button.config(relief="sunken")
               
window = tk.Tk()
window.title("Testing app")

for i in range(5):
    for j in range(5):
        button = tk.Button(
            master=window,
            relief="raised",
            width=2,
            height=1,
            borderwidth=2
        )
        handler = ButtonHandler(button)
        button.grid(row=i, column=j)

window.mainloop()


