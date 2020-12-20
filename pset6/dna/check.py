import os
import re

with open("makefile", "r") as file:
    data = file.read().split('\n')
    i, error = 1, 0
    for argument in data:
        pattern = re.compile(r'(?:as\s)(python)(\sdna.py\sdatabases/[a-zA-Z]+\.csv\ssequences/[0-9]+\.txt)')
        command = pattern.finditer(argument)
        namept = re.compile(r'(No\s)?[a-zA-Z]+\.$')
        name = namept.search(argument)
        name = name.group(0).replace(".", "")
        for arg in command:
            command = arg.group(1) + "3" + arg.group(2)
        stream = os.popen(command)
        output = stream.read()
        if output.rstrip("\n").lower() != name.rstrip("\n").lower():
            print("error at", i)
            error += 1
        i += 1
    if error is 0:
        print("No errors detected!")
