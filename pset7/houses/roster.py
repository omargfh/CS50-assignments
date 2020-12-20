from sys import argv, exit
import csv
import cs50

if len(argv) != 2:
    print("SyntaxError. Usage python roster.py HOUSENAME")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

house = argv[1]

results = db.execute('SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first', house)

for result in results:
    if result['middle'] == None:
        print(f"{result['first']} {result['last']}, born {result['birth']}")
    else:
        print(f"{result['first']} {result['middle']} {result['last']}, born {result['birth']}")