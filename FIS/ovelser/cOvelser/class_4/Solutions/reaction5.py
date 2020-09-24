## Measuring reaction time with in Python
## Angelo Basteris - angelobasteris@gmail.com
## Fysisk Interaktiv Software - Syddansk Universitet
from easygui import *
import time
import os												## We use this to play the sound - in reality, os.system("...") executes ... like from the terminal
from random import randint
choice=1
msgbox("This program measures your reaction time.\nIt shows a READY message, followed by a GO message.\nAs you see go, press SPACE.\nStart with your hand on the table\nPress SPACE when ready to start")
while(choice):
	print("Ready")
	os.system("mpg123 ready.mp3 &")
	stimulus=randint(1,2)
	time.sleep(randint(1,4))
	t0=time.time()
	os.system("mpg123 "+str(stimulus)+".mp3 &")								## Have a look at what happens if you do not put & at the end of this line? Can you notice the difference? Note, you may have to install mgp123 with sudo apt-get
	answer=buttonbox(choices=["[1]","[2]"])								## We include the numbers in [] so that one can answer with the keyboard
	reaction_time=time.time()-t0
	choice=ccbox("Your reaction time is: %.3f s\nPress Continue to repeat or Cancel to exit"%(reaction_time))
	
