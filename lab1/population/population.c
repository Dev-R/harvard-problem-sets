#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int start_size = 0;
    int end_size = 0;
    // Each year, n / 3 new llamas are born, and n / 4 llamas pass away.

    int total_years = 0;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);
    do
    {
        end_size = get_int("End size: ");
    } 
    while (end_size < start_size);
    
    //calculates the number of years required for the population to 
    //grow from the start size to the end size.
    // current_year  = start_size ;
    
    int current_year = 0 ;
    
    if (end_size != start_size)
    {
        for (int i = 0; current_year < end_size; i++)
        {
            if (i == 0)
            { 
                current_year = start_size + (start_size / 3) - (start_size / 4);
            }
            else
            {
                current_year = current_year + (current_year / 3) - (current_year / 4);
            } 
            total_years ++; 
        }
    }
    printf("Years: %i", total_years);
    // start_size = get_int("Start size: ");
    // end_size = get_int("End size: ");
    //  end_year  = start_size + born - death 
}
