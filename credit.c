#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
string isValid(long creditNumber);
bool checkLuhn(long creditNumber);

int main(void)
{
    long creditNumber;
    do
    {
        creditNumber = get_long("Number: ");

    } while (creditNumber > 0 && creditNumber <= 16);
    string is_valid_return = isValid(creditNumber);
    printf("%s\n", is_valid_return);
}

string isValid(long creditNumber)
{
    if (checkLuhn(creditNumber) == true)
    {
        long creditNumber10 = creditNumber;
        int count = 0;
        while (creditNumber10 > 0)
        {
            creditNumber10 /= 10;
            count++;
        }
        char creditNumberToStr[count];
        sprintf(creditNumberToStr, "%ld", creditNumber);
        char firsttwo[2];
        strncpy(firsttwo, creditNumberToStr, 2);
        int firstTwoDigits = atoi(firsttwo);
        char firstdigitinstr[] = {creditNumberToStr[0], '\0'};

        if (count >= 13 && count <= 16 && strcmp(firstdigitinstr, "4") == 0)
        {
            return "VISA";
        }
        else if (count == 16 && firstTwoDigits >= 51 && firstTwoDigits <= 55)
        {
            return "MASTERCARD";
        }
        else if (count == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
        {
            return "AMEX";
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
}

bool checkLuhn(long creditNumber)
{
    long creditNumber10 = creditNumber;
    int count = 0;
    while (creditNumber10 > 0)
    {
        creditNumber10 /= 10;
        count++;
    }
    char creditNumberToStr[count];
    sprintf(creditNumberToStr, "%ld", creditNumber);

    int sumOfODD = 0;
    int sumOfEven = 0;

    int lastindex = count - 1;
    int lastindexresto = lastindex % 2;

    for (int i = lastindex; i >= 0; i--)
    {
        int iresto = i % 2;

        if (lastindexresto == 0)
        {
            if (iresto == 0)
            {
                iresto = 1;
            }
            else
            {
                iresto = 0;
            }
        }

        if (iresto == 0)
        {
            int digit = 0;
            char digitinstr[] = {creditNumberToStr[i], '\0'};
            sscanf(digitinstr, "%d", &digit);
            digit *= 2;
            if (digit / 10 < 1)
            {
                sumOfEven += digit;
            }
            else
            {
                char digitToString[3];
                sprintf(digitToString, "%d", digit);
                char firtinstr[] = {digitToString[0], '\0'};
                char twoinstr[] = {digitToString[1], '\0'};
                sumOfEven += atoi(firtinstr) + atoi(twoinstr);
            }
        }
        else
        {
            int digit = 0;
            char digitinstr[] = {creditNumberToStr[i], '\0'};
            sscanf(digitinstr, "%d", &digit);
            sumOfODD += digit;
        }
    }

    if ((sumOfODD + sumOfEven) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
