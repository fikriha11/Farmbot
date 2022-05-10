from tkinter import *
import tkinter.font
import serial
import os

dtterima = ' '
n_images = 10
ser = serial.Serial('/dev/ttyUSB0',9600)

class main:
    def __init__(self,root):
        self.root=root
        self.changefont = tkinter.font.Font(font="montserrat_bold" ,size=18)
        self.bckg = PhotoImage(file = "window 1/background2.png")
        self.lbl_bg = Label(self.root, image=self.bckg).pack()
        self.root.title("Agribot")
        self.root.geometry("800x480")

        self.suhu=StringVar()
        self.kelembapan=StringVar()
        self.intensitas=StringVar()
        self.kelembapan_tanah=StringVar()

        self.l_suhu = Label(root,text='', textvariable=self.suhu, font = self.changefont, bg = '#C6E9FC').place(x=685, y=156)
        self.l_kelembapan = Label(root,text='', textvariable=self.kelembapan, font = self.changefont, bg = '#F2F2F2').place(x=685, y=214)
        self.l_intensitas = Label(root,text='', textvariable=self.intensitas, font = self.changefont, bg = '#C6E9FC').place(x=685, y=272)
        self.l_kelembapan_tanah = Label(root,text='', textvariable=self.kelembapan_tanah, font = self.changefont, bg = '#F2F2F2').place(x=685, y=328)
        
        self.root.after(100,self.bacadata)
    
    def playsound(self, event):
        os.system('python3 gtexttospeech.py')
        print("Clicked at : ", event.x, event.y)
    
    def nextwindow(self, event):
        print("Clicked at : ", event.x, event.y)
    
    def bacadata(self):
        dtterima=ser.readline()
        dtterima=dtterima.decode("utf-8")
        
        nA = dtterima.index('A')
        nB = dtterima.index('B')
        nC = dtterima.index('C')
        nD = dtterima.index('D')
        nE = dtterima.index('E')
        nF = dtterima.index('F')

        p_status = dtterima[nA+1:nB]
        p_suhu = dtterima[nB+1:nC]
        p_kelembapan = dtterima[nC+1:nD]
        p_intensitas = dtterima[nD+1:nE]
        p_kelembapan_tanah = dtterima[nE+1:nF]
        
        self.image = PhotoImage(file = "emoji/" + p_status + ".png")
        self.lbl_img = Label(self.root, image=self.image, bg="#FFFFFF")
        self.lbl_img.bind("<Button-1>", self.playsound)
        self.lbl_img.place(x=35,y=115)

        self.suhu.set(p_suhu)
        self.kelembapan.set(p_kelembapan)
        self.intensitas.set(p_intensitas)
        self.kelembapan_tanah.set(p_kelembapan_tanah)

        self.root.after(50,self.bacadata)
        #print(dtterima)
        self.root.update()

agribot = Tk()
main(agribot)
agribot.mainloop()
ser.close 
