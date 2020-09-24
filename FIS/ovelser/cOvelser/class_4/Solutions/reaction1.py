## Measuring reaction time with in Python
## Angelo Basteris - angelobasteris@gmail.com
## Fysisk Interaktiv Software - Syddansk Universitet
from easygui import *
import time
## Intro message
msgbox("This program measures your reaction time.\nIt shows a READY message, followed by a GO message.\nAs you see go, press SPACE.\nStart with your hand on the table\nPress SPACE when ready to start")
# We use print because if we used easygui the program would wait for input
print("Ready")
time.sleep(2)							## Ideally it should sleep for a random time
t0=time.time()				
msgbox("Go")							## Show the cue
msgbox("Your reaction time is: %.3f s"%(time.time()-t0))	## Show the reaction time
