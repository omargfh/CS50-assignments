from sys import argv, exit
import csv
import cs50

if len(argv) != 2:
    print("SyntaxError. Usage python import.py [CSVFILE]")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

with open(argv[1], "r") as file:
    literal = [dict()]
    reader = csv.DictReader(file)
    for row in reader:
        literal.append(row)
    literal.pop(0)

for entry in literal:
    name = entry['name'].split()
    first, middle, last = "", "", ""
    first = name[0]
    if len(name) is 2:
        last = name[1]
    elif len(name) is 3:
        middle = name[1]
        last = name[2]
    middle = middle if not middle is "" else None
    house = entry['house']
    birth = entry['birth']
    db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)', first, middle, last, house, birth)