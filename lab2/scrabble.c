#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    string congratPlayer1 = "Player 1 wins!";
    string congratPlayer2 = "Player 2 wins!!";
    string Tie = "Tie!";
    printf("%s %i %s\n", "P1 has", score1, "points");
    printf("%s %i %s\n", "P2 has", score2, "points");
    //Print the winner
    if (score1 > score2)
    {
        printf("%s \n", congratPlayer1);
    }
    else if (score1 < score2)
    {
        printf("%s\n", congratPlayer2);
    }
    else
    {
        printf("%s\n", Tie);
    }
}
//compute the score
int compute_score(string word)
{
    //iterate over each character
    int scoreCounter = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int letra = toupper(word[i]); //handle both uppercase and lowercase
        int numeroDeLetra = letra - 64;
        int pointsIndex = numeroDeLetra - 1;
        if (letra >= 65 && letra <= 90)
        {
            scoreCounter += POINTS[pointsIndex];
        }
    }
    return scoreCounter;
}