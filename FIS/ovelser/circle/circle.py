#!/usr/bin/env python
#We design and develop software that 
#requires the user to draw circles with the mouse
#1.    Give some instructions to the person;
#2.    Store the trajectory in a file;
#3.    Display the trajectory;
#4.    Processes the trajectory;
#5.    Store the results
from Xlib import display
import sys
import os
import time
import easygui as eg
import csv
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

outputMousePosition =[["X-pos" , "Y-pos"]]

eg.msgbox("Please draw a circle with the mouse")

def mousePosition():
    data = display.Display().screen().root.query_pointer()._data
    return data["root_x"], data ["root_y"]

def drawWithMouse():
    print(" ")

def plotData():
    df = pd.read_csv("circle_mousepos.csv")
    x = df["X-pos"].to_numpy()
    y = df["Y-pos"].to_numpy()
    plt.plot( x , y )
    plt.ylabel("Y-postion")
    plt.xlabel("X-postion")
    plt.savefig("myfigure.png")
    

def circleScore():
    df = pd.read_csv("circle_mousepos.csv")
    x = df["X-pos"].to_numpy()
    y = df["Y-pos"].to_numpy()
    #Perfekt cirle is 1
    print(type(x[1]) , type(y[2]))
    ratio = (x[2:,].max() - x[2:,].min() ) / ( y[2:,].max() - y[2:,].min() ) 
    error = abs( 1 - ratio )

    center = {"x_mean":x.mean, "y_mean":y.mean}
    
    distances = (x - center["x_mean"])**2 + (y
                                                          - center["y_mean"]**2)**.5
    trajectory_length = (((x - center["x_mean"])**2 + (y
                                                  - center["y_mean"])**2)**.5).sum()
    mean_radius = mean(distances)
    sd_radius = std(distances)

    plt.plot(x = "x_mean", y = "y_mean").get_figure()
    plt.savefig("myfigure2.jpg")

if __name__ == '__main__':
    t0 = time.time()
    while(time.time()-t0 < 3):
        outputMousePosition.append([mousePosition()])
    with open("circle_mousepos.csv", "w") as outfile:
        outwriter = csv.writer(outfile)
        for values in outputMousePosition:
            outwriter.writerow(values)
    plotData()
    circleScore()
