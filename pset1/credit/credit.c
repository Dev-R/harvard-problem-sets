#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DIGIT 16
#define MIN_DIGIT 13

long get_card_number_length();
bool verify_credit_card();
int apply_luns_algorithm();
void invalid_card();
void valid_card();
int concatenate_digits();
void terminate();


//** THIS PROGRAM DOESN NOT OPERATE WITH ODD CREDIT CARD NUMERS SUCH AS 13 OR 15.**//

int main()
{
// num will be used as a multiplier of 10, this is a part of my own algorithm to acess any digit in the card.
    long user_card_number = get_long("Number: ");
    //long user_card_number = 378282246310005 ;

    long num = 10;
//
    int first_card_digit, second_card_digit;
//long user_card_number = get_long("Number: ");
// find how many digits is the card
    int user_card_number_length = get_card_number_length(user_card_number);
// for simplicity
    int card_length = user_card_number_length;
// an array to told the card numbers
    int digit_num[MAX_DIGIT];
// verifying the length of the card
    bool card_length_validity = verify_credit_card(card_length);
// check if the card is fake or not if so -> terminate
    if (card_length_validity)
    {
        invalid_card();
    }
// storing the card digits to an array
    for (int i = card_length - 1; i >= 0; i--)
    {
        if (i == card_length + 1)
        {
            digit_num[i] = user_card_number % num;
        }
        else
        {
            digit_num[i] = (user_card_number % num) / (num / 10);
        }

        num *= 10;
    }
//digit_num[i] = user_card_number %
    first_card_digit = digit_num[0];
    second_card_digit = digit_num[1];
//printf("first digit: %i, second digit: %i \n", first_card_digit,  second_card_digit);
    bool(card_validity) = apply_luns_algorithm(digit_num);
    if (card_validity)
    {
// if the card invalid terminate
        invalid_card();
    }
    else
    {
// if not pass first two digit to determine card
        valid_card(first_card_digit, second_card_digit);
    }
}

// printf("%lli", user_card_number);

void valid_card(int first_card_digit, int second_card_digit)
{
    int first_two_card_digits = concatenate_digits(first_card_digit, second_card_digit);

    switch (first_two_card_digits)
    {
        case 51:
            printf("MASTERCARD\n");
            break;

        case 52:
            printf("MASTERCARD\n");
            break;

        case 53:
            printf("MASTERCARD\n");
            break;

        case 54:
            printf("MASTERCARD\n");
            break;

        case 55:
            printf("MASTERCARD\n");
            break;

        case 34:
            printf("AMEX\n");
            break;

        case 37:
            printf("AMEX\n");
            break;
        default:
            if (first_card_digit == 4)
            {
                printf("VISA\n");
                terminate();
            }
            printf("INVALID\n");

    }




}

void terminate()
{
    exit(0);
}

void invalid_card()
{
    printf("INVALID\n");
    exit(0);
}

int concatenate_digits(int first_card_digit, int second_card_digit)
{

    char first_digit[2];
    char second_digit[2];

    sprintf(first_digit, "%d", first_card_digit);
    sprintf(second_digit, "%d", second_card_digit);

    strcat(first_digit, second_digit);

    int first_and_second_digits_concatenated = atoi(first_digit);

    return first_and_second_digits_concatenated;
}

bool verify_credit_card(int card_length)
{
// if the card in not legit exit
    if (card_length < MIN_DIGIT || card_length > MAX_DIGIT)
    {
        return true;
    }
// if the card is legit continue
    else
    {
        return false;
    }
}

long get_card_number_length(long card_number)
{
    int counter = 0;
    long number = card_number;
    while (number != 0)
    {
        number = number / 10;
        counter++;
    }
    return counter;

}


int apply_luns_algorithm(int *array)
{
// obtaining non -second_to_last_digit

    int j = 1;
    int non_second_to_last_digit[MAX_DIGIT / 2];

    for (int i = 0; i < MAX_DIGIT; i++)
    {

        non_second_to_last_digit[i] = array[MAX_DIGIT - j];

        if (j == MAX_DIGIT - 1)
        {
            j = 0;
            i = 0;
            break;
        }

        j += 2;
    }

// obtaining second_to_last_digit
    j = 2;
    int second_to_last_digit[MAX_DIGIT];

    for (int i = 0; i < MAX_DIGIT; i++)
    {

        second_to_last_digit[i] = array[MAX_DIGIT - j];

        if (j == MAX_DIGIT - 1)
        {
            j = 0;
            i = 0;
            break;
        }
        j += 2;
    }
    /*
     Multiply every other digit by 2,
     starting with the numberb
     */

    for (int i = 0; i < MAX_DIGIT / 2; i++)
    {
        second_to_last_digit[i] = second_to_last_digit[i] * 2;

    }

// spliting two digits into one digit

    int k = 0;
    int current_digit = 0;
    for (int i = 0; i < MAX_DIGIT / 2; i++)
    {
        current_digit = second_to_last_digit[i];
        if (current_digit / 10 > 0)
        {
            second_to_last_digit[(MAX_DIGIT / 2) + k] =
                second_to_last_digit[i] % 10;
            second_to_last_digit[i] = second_to_last_digit[i] / 10;

            k++;
        }

    }
    int sum_of_second_to_last_digit = 0;
    for (int i = 0; i < MAX_DIGIT / 2 + k; i++)
    {

        sum_of_second_to_last_digit += second_to_last_digit[i];
//printf("Current sum: %i \n", sum_of_second_to_last_digit);
    }

// the sum "sum_of_second_to_last_digit + non_second_to_last_digit"
    int final_sum = 0;
    for (int i = 0; i < MAX_DIGIT / 2; i++)
    {

        final_sum += non_second_to_last_digit[i];
    }

//Add the sum to the sum of the digits that weren’t multiplied by 2.
    final_sum += sum_of_second_to_last_digit;

//step-3: If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    if (final_sum % 10 == 0)
    {

        return false;
    }
    else

    {
        return true;
    }
}