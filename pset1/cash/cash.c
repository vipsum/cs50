#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        change = get_float("Change owed: ");
    } while (change <= 0);

    int cents = round(change * 100);
    int monedasPosibles[] = {25, 10, 5, 1};
    int contador = 0;
    for (int i = 0; i < 4; i++)
    {
        while (cents - monedasPosibles[i] >= 0)
        {
            cents -= monedasPosibles[i];
            contador++;
        }
        if (cents == 0)
        {
            break;
        }
    }
    printf("%i\n", contador);
}
