from cs50 import get_string
from cs50 import get_int
import sys

MAX_DIGIT = 16
MIN_DIGIT = 13


def main():
    # Ask user for card number
    credit_card = input("Number:")
    #credit_card = "4012888888881881"
    # get checksum by implementing Luhn’s Algorithm
    checksum = calculate_checksum(credit_card)
    # validate_checksum(checksum)
    # get card type
    check_starting_digit(credit_card)


# implement Luhn’s Algorithm
def calculate_checksum(credit_card):
    # sum of card digit
    digit_sum = 0
    # used to skip one digit 
    skip_digit = 0
    # loop through card digits
    for digit in credit_card:
        # Multiply every other digit by 2
        new_digit = 2 * int(digit)
        if skip_digit != 1: 
            if (new_digit > 9):
                digit_sum += int(str(new_digit)[0:1])
                digit_sum += int(str(new_digit)[1:2])
                skip_digit = 1 
            else:
                digit_sum += new_digit
                skip_digit = 1 
        # Adding the sum to the sum of the digits that weren’t multiplied by 2
        else:
            digit_sum += int(digit)
            skip_digit = 0
    return digit_sum
            
            
def check_card_length(credit_card):
    # verify length of credit card
    if(len(credit_card) > MIN_DIGIT and len(credit_card) < MAX_DIGIT):
        return True
    else:
        return False


def validate_checksum(checksum):
    if (checksum % 10 != 0):
        sys.exit("INVALID")


def check_starting_digit(credit_card):
    # get first two digit of credit caard
    first_two_digits = int(str(credit_card)[0:2])
    # check if card is MASTER CARD
    if first_two_digits >= 51 and first_two_digits <= 55:
        print("MASTERCARD")
    # check if card is AMEX
    elif first_two_digits == 34 or first_two_digits == 37:
        print("AMEX")
    # check if card is VISA
    elif int(str(credit_card)[0:1]) == 4:
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()