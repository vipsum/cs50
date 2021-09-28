#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main (void)
{
    float letterCounter = 0;
    float wordCounter = 1;
    float senCounter = 0;
    string text = get_string("Text: ");
    for (int i = 0; i < strlen(text); i++)
    {
        if(isalpha(text[i]))
        {
         letterCounter++;
        }
        if (text[i] == ' ')
        {
            wordCounter++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            senCounter++;
        }
    }
    float letters = 100 * (letterCounter / wordCounter);
    float sentences = 100 * (senCounter / wordCounter);

    float index = round(index = 0.0588 * letters - 0.296 * sentences - 15.8);
       // Return result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(index));
    }
}

