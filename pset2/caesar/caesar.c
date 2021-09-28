#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argumentCount, string argumentList[])
{
    if (argumentCount != 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    //put key into a varable and convert it to integer
    int key = atoi(argumentList[1]);

    //check if int is non negative
    if (key < 0)
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    else
    {
        //get plaintext from user
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int i = 0, leng = strlen(plaintext); i < leng; i++)
        {
            //chequear si la letra es uppercase or lowercase y convertir
            if islower(plaintext[i])
            {
                printf("%c", (((plaintext[i] + key) - 97) % 26) + 97);
            }
            else if isupper(plaintext[i])
            {
                printf("%c", (((plaintext[i] + key) - 65) % 26) + 65);
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
        return 0;
    }
}
