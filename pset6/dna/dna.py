import csv
import sys
# error checking
if len(sys.argv) != 3:
    print("ERROR. Usage: Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)
#opening csv file and sequence texts
csvFile = open(sys.argv[1])
DNAsequence = open(sys.argv[2]).read()
# reading csv file onto a dictionary
csvReader = csv.DictReader(csvFile)
peopleList = []
for person in csvReader:
    peopleList.append(person)
# Short Tandem Repeats (STRs). An STR is a short sequence of DNA bases that 
# tends to repeat consecutively numerous times at specific locations inside of a person’s DNA.
# grabbing keys (str) from csvReader and passing them onto a list
strList = list(peopleList[0].keys())
# removing the name key from the list since i dont want it
strList.remove("name")
strCounter = {}
for strKey in strList:
    tmpDNAsequence = DNAsequence
    strCounter[strKey] = 0
    counter = 0
    strPosition = tmpDNAsequence.find(strKey)
    while strPosition >= 0:
        counter += 1
        tmpDNAsequence = tmpDNAsequence.replace(strKey, "", 1)
        tmpStrPosition = tmpDNAsequence.find(strKey)
        if strPosition != tmpStrPosition:
            if counter > int(strCounter[strKey]):
                strCounter[strKey] = str(counter)
            counter = 0
        strPosition = tmpStrPosition
for person in peopleList:
    clonePerson = person.copy()
    del clonePerson["name"]
    if clonePerson == strCounter:
        print(person["name"])
        sys.exit(0)
print("No match")
