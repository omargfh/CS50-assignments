from cs50 import get_int
height = 0
while height < 1 or height >= 9:
    height = get_int("Height: ")
for i in range(height):
    print(" " * (height - (i + 1)) + "#" * (i + 1) + "  " + "#" * (i + 1))
