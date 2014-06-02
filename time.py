import csv

file1="time_input.txt"

with open('workfile', 'r') as f:
	reader = f.read()
	for row in reader:
		print row 