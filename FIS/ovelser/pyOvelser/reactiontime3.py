import time
from random import randint
from easygui import *
import json
# Intro message:
output = [["timestamp", "Reaction time"]]
choice = True
msgbox("This program will measure your reaction time \n")

options = int(choicebox(msg = "How many options?", title ="Options", choices
    = [1,2]))
output_dict = {}
while(choice):

    print("Ready!")
    k = randint(2,5)
    time.sleep(k)

    #random time

    t0 = time.time()
    if options == 1:
        msgbox("Go")
    if options == 2:
        buttonbox(msg ="Press "+str(randint(1 , 2)), title = "Reaction time",
                choices = ["Botton[1]", "Botton[2]"])    
    reaction_time = time.time()-t0
    msgbox("\n Your time was: %.3f sec" %(reaction_time))
    choice=ccbox()
    output_dict["react"]=reaction_time
    output.append(output_dict)
with open ("myjasonfile.jason", "a") as outfile:
    json.dump(output_dict)
print(output)
        
