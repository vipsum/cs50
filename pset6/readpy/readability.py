from cs50 import get_string
# getting input from user
# initializing variables
text = get_string("Text: ")
lettercount = 0
wordcount = 1
sentencecount = 0
for i in range(len(text)):
    if text[i].isalpha():
        lettercount += 1
    if text[i] == ' ':
        wordcount += 1
    if text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentencecount += 1
letters = 100 * (lettercount / wordcount)
sentences = 100 * (sentencecount / wordcount)
index = round(0.0588 * letters - 0.296 * sentences - 15.8, 2)
index = int(round(index))
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade " + str(index))