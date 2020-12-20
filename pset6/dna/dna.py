from sys import argv, exit
import csv
import re

if len(argv) != 3:
    print("missing argument. usage: python dna.py [DATABASE] [SEQUENCE]")
    exit(1)

database = argv[1]
sequence = argv[2]

with open(database, "r") as file:
    literal = list()
    data = [dict()]
    csv_reader = csv.reader(file, delimiter=",")
    for row in csv_reader:
        literal = row.copy()
        break
    file.seek(0)
    csv_reader = csv.DictReader(file)
    for row in csv_reader:
        data.append(row)
    data.pop(0)

iteration = dict()
for item in literal:
    iteration.update({item: 0})

with open(sequence, "r") as file:
    csv_reader = csv.reader(file)
    for row in csv_reader:
        sequence = "".join(row)
    for cats in literal:
        regex = re.findall(f'(?:{cats})+', sequence)
        res = 0 if not regex else round(len(max(regex)) / len(cats))
        iteration[cats] = res

for i in range(len(data)):
    error = 0
    for cats in literal:
        if cats != 'name':
            if int(data[i][cats]) != iteration[cats]:
                error += 1
    if error is 0:
        iteration['name'] = data[i]['name']
        break
    else:
        iteration['name'] = "No match"

print(iteration['name'])