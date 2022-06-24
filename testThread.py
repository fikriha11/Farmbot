# Import Module
from tkinter import *
import time
from threading import *
from GUI.gtexttospeech import TextToSpeech
from GUI.getData import DataArduino

# Create Object
root = Tk()

# Set geometry
root.geometry("400x400")

# use threading

def threading():
	# Call work function
	t1=Thread(target=playsound)
	t1.start()

def thread1():
    t1 = Thread(target=work)
    t1.start()
    root.after(20000,thread1)

def thread2():
    t1 = Thread(target=get)
    t1.start()
    root.after(10000,thread2)  

def get():
	print(DataArduino)

def playsound():
    TextToSpeech(100,20,12,15)

# work function
def work():
	print("sleep time start")
	for i in range(10):
		print(i)
		time.sleep(1)
	print("sleep time stop")

# Create Button
Button(root,text="Click Me",command = threading).pack()

root.after(20000,thread1)
root.after(10000,thread2)
root.mainloop()
