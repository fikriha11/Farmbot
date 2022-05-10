from serial import *
from tkinter import *
from tkinter import ttk
import tkinter.font

serialPort = "/dev/ttyUSB0"
baudRate = 9600
ser = Serial(serialPort , baudRate, timeout=0, writeTimeout=0)

def playsound(event):
    os.system('python3 gtexttospeech.py')
    print("Clicked at : ", event.x, event.y)

def nextwindow():
    print("Clicked at : ")

root = Tk()
changefont = tkinter.font.Font(font="montserrat_bold" ,size=18)
bckg = PhotoImage(file = "window 1/background2.png")
lbl_bg = Label(root, image=bckg).pack()
root.title("Agribot")
root.geometry("800x480")

suhu=StringVar()
kelembapan=StringVar()
intensitas=StringVar()
kelembapan_tanah=StringVar()
serBuffer = ''

l_suhu = Label(root,text='', textvariable=suhu, font = changefont, bg = '#C6E9FC').place(x=685, y=156)
l_kelembapan = Label(root,text='', textvariable=kelembapan, font = changefont, bg = '#F2F2F2').place(x=685, y=214)
l_intensitas = Label(root,text='', textvariable=intensitas, font = changefont, bg = '#C6E9FC').place(x=685, y=272)
l_kelembapan_tanah = Label(root,text='', textvariable=kelembapan_tanah, font = changefont, bg = '#F2F2F2').place(x=685, y=328)

img = PhotoImage(file = "emoji/1.png")
lbl_img = ttk.Label(root, image=img, background='#FFFFFF')
lbl_img.place(x=35,y=115)

btnext = PhotoImage(file = "window 1/next.png")
lbl_btnext = Button(root, image=btnext, background='#FFFFFF', command=nextwindow)
lbl_btnext.place(x=757,y=197)

def readSerial():
    while True:
        c = ser.read() 
        if len(c) == 0:
            break
        
        global serBuffer
        
        if c == '\r':
            c = ''
            
        if c == b'\n':
            serBuffer += "\n" 
            print(serBuffer)
            
            nA = serBuffer.index('A')
            nB = serBuffer.index('B')
            nC = serBuffer.index('C')
            nD = serBuffer.index('D')
            nE = serBuffer.index('E')
            nF = serBuffer.index('F')

            p_status = serBuffer[nA+1:nB]
            p_suhu = serBuffer[nB+1:nC]
            p_kelembapan = serBuffer[nC+1:nD]
            p_intensitas = serBuffer[nD+1:nE]
            p_kelembapan_tanah = serBuffer[nE+1:nF]

            suhu.set(p_suhu)
            kelembapan.set(p_kelembapan)
            intensitas.set(p_intensitas)
            kelembapan_tanah.set(p_kelembapan_tanah)

            img = PhotoImage(file = "emoji/" + p_status + ".png")
            lbl_img.configure(image=img)
            lbl_img.image = img

            serBuffer = "" 
        else:
            serBuffer += c.decode("utf-8") 

  
    lbl_img.bind("<Button-1>", playsound)
    # lbl_btnext.bind("<Button-1>", nextwindow)

    root.after(200, readSerial) 
    root.update

root.after(100, readSerial)
root.mainloop()