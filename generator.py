/*
* Random Array Generator to avoid hardcoded strings with sensitive data.
*
* By ClaudiaD
*/

#!/usr/bin/env python2
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

result_ascii = """
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
