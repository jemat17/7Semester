## Measuring reaction time with in Python
## Angelo Basteris - angelobasteris@gmail.com
## Fysisk Interaktiv Software - Syddansk Universitet
from easygui import *
import time
from random import randint			## In this way we sleep for a random number of seconds
msgbox("This program measures your reaction time.\nIt shows a READY message, followed by a GO message.\nAs you see go, press SPACE.\nStart with your hand on the table\nPress SPACE when ready to start")	## Intro message
for i in range(5):
	print("Ready")										## Get ready
	time.sleep(randint(1,4))
	t0=time.time()
	msgbox("Go")										## Show the cue
	msgbox("Your reaction time is: %.3f s\nPress any key to continue"%(time.time()-t0))	## Reaction time
