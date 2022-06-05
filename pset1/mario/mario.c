#include <stdio.h>
#include <cs50.h>


//the user doesn’t, in fact, input a positive integer between 1 and 8, inclusive, when prompted, the program should re-prompt the user until they cooperate:

int main(void)
{
    int user_input = 0;
    // get user_input
    do
    {
        user_input = get_int("Height: ");
        
    } 
    while (user_input < 1 || user_input > 8);
    // store the required space to form the hiearachy shape
    int required_hiearachy_space = user_input ; 
    
    for (int height = 1; height < user_input + 1; height++)
    {
        // adding space to the # to make it look like a hiearachy
        for (int add_space = 1; add_space < required_hiearachy_space; add_space++)
        {
            printf(" ");
        }
        // adding blocks to the hiearachy
        for (int width = 1; width <= 2 * height; width++)
        {
            printf("#");
            // if 
            if (width == height)
            {
                printf("  ");
            }
        }
        printf("\n");
        // Decrement the spaces needed for the hiearachy
        required_hiearachy_space--;
    }
    
}
