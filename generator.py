#!/usr/bin/env python2

"""
By ClaudiaD (anonops.com)

Note: you can put the string after the script name if you wish to execute it more efficiently

I'm lazy to copy the 674 lines of GNU GPL so I'm just gonna specify a very important license (see, I invented a license).

LICENSE:

You must provide the license along with the program.
You must provide the source code along with the program (if compiled).
You don't have to mention the original author as long as you don't mention anyone else.
	If you received a version without anyone mentioned, then you cannot mention anyone.

-------------------

^ ik, the "mentioned" is weird but credited accredited wtf it's just a huge mess

btw if u break the license, you're gonna get sniped by the anonops sniper team

Coded with <3 for Case

"""

from __future__ import division
import random
import sys

string = sys.argv[1] if len(sys.argv) > 1 else raw_input(">")

length = len(string)

chars = [None] * length
positions = [None] * length

for i in range(length):
	char = string[i]
	while True:
		position = random.randrange(length)
		percentage = (i/length)*100
		if percentage < 10:
			print str("{0:.11f}".format(percentage)) + "%:   " + str(position)
		else:
			print str("{0:.10f}".format(percentage)) + "%:   " + str(position)
		if chars[position] is None:
			chars[position] = char
			positions[i] = position
			break
		else:
			continue

print("\n" + str(chars))

print("\n-------------------------------------------\n\nCheck:\n")

result = "chars = " + str(chars) + "\n\nresult = "

for i,position in enumerate(positions):
	result = result + "chars["+str(position)+"] + "
	print chars[position],
	if i == len(positions)-1:
		result = result[:-3]

result_ascii = """ #<-- most important part of the code
 ____  _____ ____  _   _ _   _____ 
|  _ \| ____/ ___|| | | | | |_   _|
| |_) |  _| \___ \| | | | |   | |  
|  _ <| |___ ___) | |_| | |___| |  
|_| \_\_____|____/ \___/|_____|_|  
                                   
"""

print("\n\n-------------------------------------------\n" + result_ascii)

print("---------------------------------------------------------------\n")
print result
print("\n---------------------------------------------------------------")
