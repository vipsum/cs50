 
from cs50 import get_float
while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

cents = round(change * 100)
monedasPosibles = [25, 10, 5, 1]
counter = 0
for i in range(4):
    while cents - monedasPosibles[i] >= 0:
        cents -= monedasPosibles[i]
        counter += 1
    if cents == 0:
         break
print(counter)
