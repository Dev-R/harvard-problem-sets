#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include <wctype.h>
#include<math.h>

int get_number_of_letters();
int get_number_of_words();
int get_number_of_sentences();
float apply_coleman_liau_indexing();
void display_user_text_grade();

int main(void)
{

    // get text input from user
    string user_text = get_string("Text:");
    // find length of the user text
    int text_length = strlen(user_text);
    // get and store number of letters
    int num_letters = get_number_of_letters(user_text);
    //printf("No.letters : %i \n", num_letters);
    // get and store number of letters
    int num_words = get_number_of_words(user_text);
    //printf("No.words : %i \n", num_words);
    // get and store number of sentences
    int num_sentences = get_number_of_sentences(user_text);
    //printf("No.sentences : %i \n", num_sentences);
    // stores and get The Coleman-Liau index Reading grade
    float index_result = round(apply_coleman_liau_indexing(num_letters, num_words, num_sentences));
    // outputting the (U.S.) grade level of the user
    display_user_text_grade((int)index_result);

}

//outputting the (U.S.) grade level of the user
void display_user_text_grade(int index_result)
{
    if (index_result > 0 && index_result < 16)
    {
        printf("Grade %i\n", index_result);
    }
    else if (index_result >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}

// finding what (U.S.) grade level is needed to understand the text. Based on The Coleman-Liau index
float apply_coleman_liau_indexing(int num_letters, int num_words, int num_sentences)
{
    //index = 0.0588 *
    // find the average number of letters text
    float avg_num_letters = (((float) num_letters / (float) num_words) * 100);
    // find the average number of sentences text
    float avg_num_sentences = (((float) num_sentences / (float) num_words) * 100);
    // applying The Coleman-Liau index formula
    float index = ((0.0588 * (float) avg_num_letters) - (0.296 * (float) avg_num_sentences) - 15.8);

    return index;
}




// find num of sentences in a  text
int get_number_of_sentences(string text)
{
    // find length of the user text
    int text_length = strlen(text);
    // num of sentence counter
    int num_sentences = 0;
    // find num of sentences of the user text
    for (int i = 0; i < text_length; i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            num_sentences++;
            //printf("No.sentence : %i \n", num_sentences);
        }
    }
    return num_sentences;
}

// find num of words in a text
int get_number_of_words(string text)
{
    // find length of the user text
    int text_length = strlen(text);
    // counter for numbers of words
    int num_words = 0;
    // find num of words of the user text
    for (int i = 0 ; i < text_length; i++)
    {
        if (iswspace(text[i]))
        {
            num_words++;
            //printf("No.words : %i \n", num_words);
        }
    }
    // since it will always return num_words - 1, adding 1 to fix this issue.
    return num_words + 1;
}




// find num of letters in a text
int get_number_of_letters(string text)
{
    int text_length = strlen(text);
    // counter for number of letters
    int num_letters = 0;

    // count number of letters in user text

    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
        {
            num_letters++;
            //printf("No.letters : %i \n", num_letters);
        }

    }
    return num_letters;
}
