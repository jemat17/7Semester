import time
from random import randint
from easygui import *

# Intro message:
msgbox("This program will measure your reaction time \n")

print("Ready!")
k = randint(2,5)
time.sleep(k)

#random time

t0 = time.time()
msgbox("Go!")
msgbox("\n Your time was: %.3f sec" %(time.time()-t0))
