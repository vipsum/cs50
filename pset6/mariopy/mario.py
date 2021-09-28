from cs50 import get_int
height = 0
while True:
    height = get_int("Height of the pyramid: ")
    if height > 0 and height < 9:
             break


for row in range(height):
    for spaces in range(height - row - 1):
        print(" ", end = "")
    for hash in range(row + 1):
        print("#", end = "")
    print(" ", end = "")
    print(" ", end = "")
    for hash in range(row + 1):
        print("#", end = "")
    print("")
