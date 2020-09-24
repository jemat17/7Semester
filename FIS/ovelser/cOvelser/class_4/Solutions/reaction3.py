## Measuring reaction time with in Python
## Angelo Basteris - angelobasteris@gmail.com
## Fysisk Interaktiv Software - Syddansk Universitet
from easygui import *
import time
from random import randint
choice=1
msgbox("This program measures your reaction time.\nIt shows a READY message, followed by a GO message.\nAs you see go, press SPACE.\nStart with your hand on the table\nPress SPACE when ready to start")
while(choice):
	print("Ready")
	time.sleep(randint(1,4))
	t0=time.time()
	msgbox("Go")
	choice=ccbox("Your reaction time is: %.3f s\nPress Continue to repeat or Cancel to exit"%(time.time()-t0))