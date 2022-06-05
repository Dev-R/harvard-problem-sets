#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <wctype.h>
#include <math.h>
#include <stdlib.h>

void validate_input();
int get_number_of_letters();
void teriminate_case_1();// user command line argument input is lesser or greater than 26 character
void teriminate_case_2();// user command line argument input contain non alphabetic character
void teriminate_case_3();// user command line argument input contain repeated character or empty input
string apply_cipher();

#define NUM_OF_ALPHABETIC 26  // number of Alphapetics

int main(int argc, string argv[])
{
    // verify user input is clear of invalid inputs
    validate_input(argc, argv[1]);

    //take user encrpytion key
    string user_key = argv[1];
    //take user plaint_text
    string plaint_text = get_string("plaintext:");

    //getting the cipher text(encrypterd message)
    string cipher_text = apply_cipher(user_key, plaint_text);
    printf("ciphertext: %s\n ", cipher_text);

}

//applying and getting the cipher text(encrypterd message)
string apply_cipher(string user_key, string plaint_text)
{

    //int k = 0;
    int n_row = 3;
    int n_col = NUM_OF_ALPHABETIC;

    // 3 column array ['key']['a']['A'],[key][Small Alpha][Capital Alpha]
    char array[n_col][n_row];

    for (int i = 0 , k = 0; i < NUM_OF_ALPHABETIC; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if (j == 0)
            {
                // associate one key char to the first column of the array in the [i] row
                //
                if (user_key[k] >= 'a' && user_key[k] <= 'z')
                {

                    array[i][j] = user_key[k] - ('a' - 'A');
                    k++;
                }
                else
                {
                    array[i][j] = user_key[k];
                    k++;
                }
            }
            else if (j == 1)
            {
                array[i][j] = 'a' + i;
            }
            else if (j == 2)
            {
                {
                    array[i][j] = 'A' + i;
                }
            }
        }
    }

    // substitute plaintext with ciphertext
    for (int c = 0; c < strlen(plaint_text); c++)
    {

        char current_char = plaint_text[c];

        for (int i = 0; i < NUM_OF_ALPHABETIC; i++)
        {
            for (int j = 1; j <= 2; j++)
            {
                if (current_char == array[i][1])
                {
                    plaint_text[c] = (array[i][0] + ('a' - 'A'));
                }
                else if (current_char == array[i][2])
                {
                    plaint_text[c] = array[i][0];
                }
            }
        }
    }
    return (plaint_text);
}

// validate user_input
void validate_input(int argc, string argv)
{
    //#case 1: check for non-alphabet char
    //if key_length = 1, this is an error that a non valid char exist.
    if (argc == 1)
    {
        teriminate_case_2();
    }

    //#case 2: check length
    int key_length = get_number_of_letters(argv);

    if (key_length > NUM_OF_ALPHABETIC || key_length < NUM_OF_ALPHABETIC)
    {
        teriminate_case_1();
    }
    else if (key_length == 0)
    {
        teriminate_case_3();
    }

    //#case 3: check for repeated characters
    for (int i = 0; i < key_length; i++)
    {
        char current_char = argv[i];
        for (int j = i + 1; j < key_length; j++)
        {
            if (current_char == argv[j])
            {
                teriminate_case_3();
            }
        }
    }
}


//find num of letters in a text
int get_number_of_letters(string text)
{

    int text_length = strlen(text);
    //counter for number of letters
    int num_letters = 0;
    int invalid_char = 0;
    //count number of letters in user text

    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
        {
            num_letters++;
            //printf("No.letters : %i \n", num_letters);
        }
        else
        {
            invalid_char++;
        }
    }
    //printf("check 2 string char num: %i \n", num_letters - 1);
    if (invalid_char > 0)
    {
        //this indicate an error that a non valid char exist
        return 1;
    }
    return num_letters;
}

void teriminate_case_1()
{
    printf("Key must contain 26 characters.\n");
    exit(1);
}

void teriminate_case_2()
{
    printf("Usage: ./substitution key\n");
    exit(1);
}

void teriminate_case_3()
{
    printf("Key must not contain repeated characters.\n");
    exit(1);
}