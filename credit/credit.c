#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

unsigned long long get_credit(void);
unsigned long long get_decimal(unsigned long long credit);
unsigned long long get_digitsum(unsigned long long credit);
unsigned long long Check_AE(unsigned long long credit, unsigned long long decimals);
unsigned long long Check_VISA(unsigned long long credit, unsigned long long decimals);
unsigned long long Check_MASTERCARD(unsigned long long credit, unsigned long long decimals);

int main(void)
{
    // AMERICAN EXPRESS; 15 digits, start with 34 or 37
    // MASTERCARD; 16 digits, starts with 51-55
    // VISA; 13 or 16 digits, starts with 4
    // every credit card validates a check sum
    // If invalid, check INVALID

    // Ask human for the credit number
    unsigned long long credit = get_credit();

    // Work out how many numbers given
    unsigned long long decimals = get_decimal(credit);

    // check sum to make sure number valid
    unsigned long long digitsum = get_digitsum(credit);

    if (digitsum % 10 != 0)
    {
        printf("INVALID\n");
    }

    else
    {
        // Check for American Express
        unsigned long long check_AE = Check_AE(credit, decimals);

        // Check for VISA
        unsigned long long check_VISA = Check_VISA(credit, decimals);

        // Check for Mastercard
        unsigned long long check_MASTERCARD = Check_MASTERCARD(credit, decimals);

        if (check_AE == 0 && check_VISA == 0 && check_MASTERCARD == 0)
        {
            printf("INVALID\n");
        }
    }

}


unsigned long long get_credit(void)
{
    // Get credit number here, repeat if entered incorrectly.
    unsigned long long credit;
    do
    {
        credit = get_long("Credit Number: ");
    }
    while (credit < 0);

    return credit;
}

unsigned long long get_decimal(unsigned long long credit)
{
    // Work out how long the number is
    long counter = 0;
    while (credit >= 10)
    {
        counter++;
        credit = credit / 10;
    }

    counter++;

    return counter;
}

unsigned long long get_digitsum(unsigned long long credit)
{
    // initialise variables here for neatness
    unsigned long long credit_1 = 0;
    unsigned long long lildig_1 = 0;
    unsigned long long number_1 = 0;
    unsigned long long int multiply = 0;
    unsigned long long int multiplys = 0;

    credit_1 = credit;

    credit_1 = credit_1 / 10;

    // Extract first set of numbers from sequence and x2. Keep counter to add them up
    while (credit_1 >= 10)
    {
        lildig_1 = credit_1 / 10;
        lildig_1 = lildig_1 * 10;
        multiply = (credit_1 - lildig_1) * 2;

        if (multiply >= 10)
        {
            multiplys = multiply / 10;
            number_1 = number_1 + multiplys;
            multiplys = multiplys * 10;
            multiply = multiply - multiplys;
        }

        if (multiply < 10)
        {
            number_1 = number_1 + multiply;
        }

        if (credit_1 >= 10)
        {
            credit_1 = credit_1 / 100;
        }
    }

    credit_1 = credit_1 * 2;

    // if the first number is >=5 make sure to deal with it's individual digits
    if (credit_1 >= 10)
    {
        multiply = credit_1 / 10;
        number_1 = number_1 + multiply;
        multiply = multiply * 10;
        credit_1 = credit_1 - multiply;
    }

    number_1 = number_1 + credit_1;

    unsigned long long credit_2 = 0;
    unsigned long long lildig_2 = 0;
    unsigned long long number_2 = 0;


    credit_2 = credit;

    // Now extract second part of digits and do not multiply.
    while (credit_2 >= 10)
    {
        lildig_2 = credit_2 / 10;
        lildig_2 = lildig_2 * 10;
        multiply = credit_2 - lildig_2;
        number_2 = number_2 + multiply;

        if (credit_2 >= 10)
        {
            credit_2 = credit_2 / 100;
        }
    }

    number_2 = number_2 + credit_2;

    return (number_1 + number_2);

}

unsigned long long Check_AE(unsigned long long credit, unsigned long long decimals)
{
    // check for American Express
    if (decimals == 15)
    {
        if (credit / 10000000000000 == 34 || credit / 10000000000000 == 37)
        {
            printf("AMEX\n");
            return 1;
        }
        else
        {
            return 0;
        }
    }

    else
    {
        return 0;
    }
}

unsigned long long Check_VISA(unsigned long long credit, unsigned long long decimals)
{
    // check for VISA. 13 or 16 digits, starts with 4
    if (decimals == 13)
    {
        if (credit / 1000000000000 == 4)
        {
            printf("VISA\n");
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (decimals == 16)
    {
        if (credit / 1000000000000000 == 4)
        {
            printf("VISA\n");
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

unsigned long long Check_MASTERCARD(unsigned long long credit, unsigned long long decimals)
{
    // Check for MASTERCARD; 16 digits, starts with 51-55
    if (decimals == 16)
    {
        if (credit / 100000000000000 < 56 && credit / 100000000000000 > 50)
        {
            printf("MASTERCARD\n");
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
