import tkinter.font
import requests
import cv2
from serial import Serial
from tkinter import *
from tkinter import ttk
from gtexttospeech import TextToSpeech
from getData import DataArduino

serialPort = "/dev/ttyUSB0"
baudRate = 9600
ser = Serial(serialPort, baudRate, timeout=0, writeTimeout=0)
camPort = 0

path = '/home/pi/Documents/Farmbot/'
# path = ''

def playsound(event):
    TextToSpeech(p_suhu,p_intensitas,p_kelembapan,p_kelembapan_tanah)
    print("Clicked at : ", event.x, event.y)

def showframe(frame):
    frame.tkraise()


root = Tk()
changefont = tkinter.font.Font(font="montserrat_bold", size=18)
root.title("Agribot")
root.geometry("800x480")
root.attributes('-zoomed', False)

# dynamic variable
suhu = StringVar()
kelembapan = StringVar()
intensitas = StringVar()
kelembapan_tanah = StringVar()
serBuffer = ''

frame1 = Frame(root)
frame2 = Frame(root)

frame1.grid(row=0, column=0, sticky='nsew')
frame2.grid(row=0, column=0, sticky='nsew')


# ========================FRAME 1================================
bckg = PhotoImage(file=path + "GUI/window 1/background2.png")
lbl_bg = Label(frame1, image=bckg).pack()

btnext = PhotoImage(file=path + "GUI/window 1/next.png")
lbl_btnext = Button(frame1, image=btnext, background='#FFFFFF',
                    command=lambda: showframe(frame2)).place(x=757, y=197)

# dynamic label untuk diisi dari data serial
l_suhu = Label(frame1, text='', textvariable=suhu,
               font=changefont, bg='#C6E9FC').place(x=670, y=156)
l_kelembapan = Label(frame1, text='', textvariable=kelembapan,
                     font=changefont, bg='#F2F2F2').place(x=670, y=214)
l_intensitas = Label(frame1, text='', textvariable=intensitas,
                     font=changefont, bg='#C6E9FC').place(x=670, y=272)
l_kelembapan_tanah = Label(frame1, text='', textvariable=kelembapan_tanah,
                           font=changefont, bg='#F2F2F2').place(x=670, y=328)

# dynamic image untuk dirubah dari data serial
img = PhotoImage(file=path + "GUI/emoji/1.png")
lbl_img = ttk.Label(frame1, image=img, background='#FFFFFF')
lbl_img.place(x=35, y=115)


# ========================FRAME 2================================
bckg2 = PhotoImage(file=path + "GUI/window 2/bg.png")
lbl_bg2 = Label(frame2, image=bckg2).pack()

btnext2 = PhotoImage(file=path + "GUI/window 2/back.png")
lbl_btnext2 = Button(frame2, image=btnext2,
                     background='#FFFFFF', command=lambda: showframe(frame1))
lbl_btnext2.place(x=43, y=20)

# # source image untuk pot
planted = PhotoImage(file=path + "GUI/window 2/planted.png")
unplanted = PhotoImage(file=path + "GUI/window 2/empty.png")

# static image. pot baris 1 (p11-p16)
p11 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=117, y=32)
p12 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=225, y=32)
p13 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=333, y=32)
p14 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=441, y=32)
p15 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=549, y=32)
p16 = Label(frame2, image=planted, background='#FFFFFF').place(x=657, y=32)
# static image. pot baris 1 (p21-p26)
p21 = Label(frame2, image=planted, background='#FFFFFF').place(x=117, y=134)
p22 = Label(frame2, image=planted, background='#FFFFFF').place(x=225, y=134)
p23 = Label(frame2, image=planted, background='#FFFFFF').place(x=333, y=134)
p24 = Label(frame2, image=planted, background='#FFFFFF').place(x=441, y=134)
p25 = Label(frame2, image=planted, background='#FFFFFF').place(x=549, y=134)
p26 = Label(frame2, image=planted, background='#FFFFFF').place(x=657, y=134)
# static image. pot baris 1 (p31-p36)
p31 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=117, y=236)
p32 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=225, y=236)
p33 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=333, y=236)
p34 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=441, y=236)
p35 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=549, y=236)
p36 = Label(frame2, image=planted, background='#FFFFFF').place(x=657, y=236)
# static image. pot baris 1 (p41-p46)
p41 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=117, y=338)
p42 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=225, y=338)
p43 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=333, y=338)
p44 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=441, y=338)
p45 = Label(frame2, image=unplanted, background='#FFFFFF').place(x=549, y=338)
p46 = Label(frame2, image=planted, background='#FFFFFF').place(x=657, y=338)


# static label. text baris 1 (t11-t16)
t11 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=159, y=122, anchor=CENTER)
t12 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=267, y=122, anchor=CENTER)
t13 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=375, y=122, anchor=CENTER)
t14 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=483, y=122, anchor=CENTER)
t15 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=591, y=122, anchor=CENTER)
t16 = Label(frame2, text='seledri', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=699, y=122, anchor=CENTER)
# static label. text baris 1 (t21-t26)
t21 = Label(frame2, text='seledri', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=159, y=224, anchor=CENTER)
t22 = Label(frame2, text='seledri', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=267, y=224, anchor=CENTER)
t23 = Label(frame2, text='seledri', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=375, y=224, anchor=CENTER)
t24 = Label(frame2, text='seledri', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=483, y=224, anchor=CENTER)
t25 = Label(frame2, text='seledri', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=591, y=224, anchor=CENTER)
t26 = Label(frame2, text='seledri', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=699, y=224, anchor=CENTER)
# static label. text baris 1 (t31-t36)
t31 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=159, y=326, anchor=CENTER)
t32 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=267, y=326, anchor=CENTER)
t33 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=375, y=326, anchor=CENTER)
t34 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=483, y=326, anchor=CENTER)
t35 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=591, y=326, anchor=CENTER)
t36 = Label(frame2, text='seledri', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=699, y=326, anchor=CENTER)
# static label. text baris 1 (t41-t46)
t41 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=159, y=428, anchor=CENTER)
t42 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=267, y=428, anchor=CENTER)
t43 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=375, y=428, anchor=CENTER)
t44 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=483, y=428, anchor=CENTER)
t45 = Label(frame2, text='-', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=591, y=428, anchor=CENTER)
t46 = Label(frame2, text='seledri', justify=CENTER, font=changefont,
            bg="#FFFFFF").place(x=699, y=428, anchor=CENTER)

# =========================SERIAL DATA PROCESS===================

def readSerial():
    while True:
        c = ser.read()
        if len(c) == 0:
            break

        global serBuffer
        global p_status, p_suhu, p_kelembapan, p_kelembapan_tanah, p_intensitas

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

            # isi dynamic variable
            suhu.set(p_suhu)
            kelembapan.set(p_kelembapan)
            intensitas.set(p_intensitas)
            kelembapan_tanah.set(p_kelembapan_tanah)

            # ubah dynamic image
            img = PhotoImage(file=path + "GUI/emoji/" + p_status + ".png")

            lbl_img.configure(image=img)
            lbl_img.image = img

            serBuffer = ""
        else:
            serBuffer += c.decode("utf-8")

    lbl_img.bind("<Button-1>", playsound)

    root.after(2000, readSerial)
    root.update

def SendSerial():
  ser.write(bytes(DataArduino(),'utf-8'))
  root.after(5000, SendSerial)
  root.update

def captureImage():

    cap = cv2.VideoCapture(camPort)
    result, image = cap.read()

    if result:
        cv2.imwrite(path + "picture.png", image)
        cap.release()
    else:
        print("No image detected. Please! try again")   

def UpdateDatabase():
  captureImage()
  headers = {
    'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Mobile Safari/537.36'
}
  url = 'http://farmbot.belajarobot.com/sensor/1'
  name_img = path + 'picture.png'
    
  img = open(name_img, 'rb')
  data = {
    'moist': p_kelembapan_tanah,
    'lumen': p_intensitas,
    'temp': p_suhu,
    'humid': p_kelembapan,
  }
  files = {'image': (name_img,img,'images/png')}

  try:
    res = requests.post(url, data=data, files=files, headers=headers)
    print(res.text)
  except Exception as error:
    print(error)

  root.after(20000, UpdateDatabase)
  root.update

showframe(frame1)
root.after(2000, readSerial)
root.after(5000, SendSerial)
root.after(20000, UpdateDatabase)
root.mainloop()
