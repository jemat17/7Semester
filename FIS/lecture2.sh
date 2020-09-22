#!/bin/bach

for val in (0..1000) 
do
	time eval $(xdotool getmouselocation --shell)
	echo $time
done

spd-say "Hallo World"
echo return 0
