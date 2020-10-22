## Circle drawing task full program
## Angelo Basteris 8-10-20
## This program reads the mouse position, asking one to draw a circle in 3 seconds, stores the trajectories and indicators
import easygui as eg			## For input/output
import pyautogui			## For reading the mouse position
import time				
import pandas as pd			## pandas is a library for data analysis that we use for processing
import csv				## Trajectories are saved as csv
import json				## Indicators as json

data=[["time","x","y"]]		## The header for our .csv file. Note this is a list containing a list ([[]])
results={}				## A dictionary for our indicators
height=pyautogui.size().height		## The screen height
eg.msgbox("Please click and then draw a circle with the mouse over the next 3 seconds - the program shows how good you are")
t0=time.time()				## The time at which the saving starts
tQ = 0.01
filename="data/data-"+str(t0)+"-"+str(tQ)		## We use this time also in the filename, so that our program saves a unique filename

while(time.time()-t0)<3:		## For three seconds
	mouse=pyautogui.position()	## mouse is a Point type, that has .x and .y
	mouse_pos={"x":mouse.x,"y":height-mouse.y}  ## we create a dictionary mouse_pos and change the y, because the original trajectory appeared reversed on the vertical axis
	data.append([time.time()-t0,mouse_pos["x"],mouse_pos["y"]])	## data is a list containing our trajectory. We add a list of three elements at each cycle
	time.sleep(tQ)		## By adding this time.sleep for .01 s we make so that our sampling will be approx 1/.01=100 Hz

## Saving our data in the .csv file
with open(filename+".csv","w") as my_file:
	my_writer=csv.writer(my_file)
	for each_row in data:
		my_writer.writerow(each_row)

## Loads the .csv file that we just saved as a panda dataframe named dat
dat=pd.read_csv(filename+".csv")

## We calculate some indicators using pandas min,man,mean,std,diff functions
ratio=(dat.x.max()-dat.x.min())/(dat.y.max()-dat.y.min())		## Ratio between horizontal and vertical axis
error=abs(1-ratio)							## The higher the error, the worse the circle
trajectory_length=((dat.x.diff()**2+dat.y.diff()**2)**.5).sum()	

center={"x":dat.x.mean(),"y":dat.y.mean()}				## The center of our trajectory is the mean point

distances=((dat.x-center["x"])**2+(dat.y-center["y"])**2)**.5		## The distance of each point from the center
mean_r=distances.mean()						## In a perfect circle, this is r and stdev=0
stdev=distances.std()							## The higher the worse the circle is

## We create a dictionary with these values and save the .json file
results={"ratio":ratio,"error":error,"trajectory_length":trajectory_length,"mean_r":mean_r,"stdev":stdev}

myfigure = dat.time.diff().plot().get_figure()
myfigure.savefig(filename+"samplingInterval.png")
with open(filename+".json","w") as jsonfile:
	json.dump(results,jsonfile)

## We save and display the figure, with all the values on the window
fig=dat.plot(x="x",y="y").get_figure()
fig.savefig(filename+".png")
mytext=""

for k in results.keys():				## In this way we concatenate all the results in mytext
	mytext=mytext+k+": %.2f / "%(results[k])
eg.msgbox(msg=mytext,image=filename+".png")
	
