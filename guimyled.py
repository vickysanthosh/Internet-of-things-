import serial
import tkinter
import time
ser=serial.Serial('COM4',9600,timeout=1)
led=tkinter.Tk()
#led.withdraw()
def ledon():
   
    print("LED IS ON")
    while 1:
        val=input(1)
        ser.write(val)
def ledoff():
    #ser=serial.Serial('COM4',9600)
    print("LED IS OFF")
    while 1:
        val=input(0)
        ser.write(val)
l4=tkinter.Label(led,text="VICKY OWN SCADA SYSTEM",fg="blue")
b=tkinter.Button(led,text="LED ON",command=ledon,bg="GREEN")
c=tkinter.Button(led,text="LED OFF",command=ledoff,bg="RED")

l4.pack()
b.pack()
c.pack()

led.mainloop()
