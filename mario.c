#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height of the pyramid: ");
    } while (height <= 0 || height > 20);

    /*
    ...#  -> row 1, 1 hash, 3 spaces
    ..##  -> row 2, 2 hashes, 2 spaces
    .###  -> row 3, 3 hashes, 1 space
    ####  ->
    for each row -> spaces + hashes = total height - hashes
    */
    for (int row = 1; row <= height; row++)
    {
        for (int spaces = 1; spaces <= height - row; spaces++)
        {
            printf(" ");
        }
        //print hashtag for each row
        for (int hash = 1; hash <= row; hash++)
        {
            printf("#");
        }
        printf(" ");
        printf(" ");
        for (int hash = 1; hash <= row; hash++)
        {
            printf("#");
        }

        printf("\n");
    }
}
