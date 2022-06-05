#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score();
int get_word_length();



int main(void)
{
    //xstring word = "Bye";
    //xint word_length = strlen(word);
    //xprintf("%d \n", word_length);

    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    //printf("Player one score:%i \n", score1);
    //printf("Player two score:%i \n", score2);

    // check for player with the heights score
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}



int compute_score(string word) 
{
    // find length of the POINTS array
    int POINTS_length = sizeof(POINTS) / sizeof(int);
    // find length of the user word
    int word_length = strlen(word);
    //Check 0
    //printf("Check 0 done\n");

    // Assigning char for ASCII reference
    char char_a = 'a';
    char char_z = 'z';
    char char_A = 'A';
    char char_Z = 'Z';
    // This array is 2D that will store in first column the lower case letter, second column upper case letter, third comma the points of the lower and upper case points
    // 3 = 'lower' 'upper' 'points'
    // [no.rows] = [POINTS_length]

    int lower_upper_point[POINTS_length][3];

    // initalize low letters to the array
    for (int i = 0, j = 0; i <= (char_z - char_a); i++, j++) 
    {
        lower_upper_point[i][0] = char_a + j;
    }
    //Check 1
    //printf("Check 1 done\n");
    // initalize Capital letters to the array
    for (int i = 0, j = 0; i <= (char_Z - char_A); i++, j++) 
    {
        lower_upper_point[i][1] = char_A + j;
    }
    //Check 2
    //printf("Check 2 done\n");

    // initalize Points to the letters in the array
    for (int i = 0, j = 0; i < POINTS_length; i++, j++) 
    {
        lower_upper_point[i][2] = POINTS[i];
    }
    //Check 3
    //printf("Check 3 done\n");
    //

    // keep truck of the player score
    int player_score = 0;

    /*
    for (int current_char = 0; current_char <= word_length; current_char++)
    {
        for (int j = 0; j <= POINTS_length; j++)
        {
            if ( word[current_char] == lower_upper_point[j][0] ||  word[current_char] == lower_upper_point[j][1] )
            {
                player_score += lower_upper_point[j][2];
                printf("Current Player score:%i \n", player_score);

            }

        }
    }
    */

    int current_exe_condation = 0;
    // calculate over all scores for the players
    for (int current_char = 0; current_char <= word_length; current_char++) 
    {
        // check whether the letter has been found or not if so it will become 1 to end the below loop
        current_exe_condation = 0;
        // looping and comparing the current word char to the all char in the arrays
        for (int j = 0; j < POINTS_length && current_exe_condation != 1; j++) 
        {
            if (word[current_char] == lower_upper_point[j][0] || word[current_char] == lower_upper_point[j][1]) 
            {
                player_score += lower_upper_point[j][2];
                //printf("Current Player score:%i \n", player_score);
                current_exe_condation += 1;

            }

        }
    }

    return player_score;
}