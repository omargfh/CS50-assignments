#include <cs50.h>
#include <stdio.h>

long validate(string content);
bool card_check(long card_number);
bool luhn_check(long card_number);
long get_digit_count(long number);
long get_digit_at(long place, long number, long digit_count);


int main(void)
{

    validate("Number: ");
    return 0;

}

// calls for a valid card number
long validate(string content)
{

    long card_number;
    bool is_valid;
    do
    {

        card_number = get_long("%s", content);
        is_valid = card_check(card_number);

    }
    while (!is_valid && card_number < 1);
    return card_number;

}

// checks if the number corresponds to a valid card and the type of that card
bool card_check(long card_number)
{

    string type;
    bool checked = true;

    long digit_count = get_digit_count(card_number);
    long first_digit = get_digit_at(1, card_number, digit_count);
    long second_digit = get_digit_at(2, card_number, digit_count);

    if (digit_count == 15 && (first_digit == 3 && (second_digit == 4 || second_digit == 7)))
    {

        type = "AMEX\n";

    }
    else if (digit_count == 16 && (first_digit == 5 && (second_digit == 1 || second_digit == 2 || second_digit == 3
                                   || second_digit == 4 || second_digit == 5)))
    {

        type = "MASTERCARD\n";

    }
    else if ((digit_count == 13 || digit_count == 16) && first_digit == 4)
    {

        type = "VISA\n";

    }
    else
    {
        type = "INVALID\n";
        checked = false;

    }

    bool valid = checked;
    if (checked)
    {

        valid = luhn_check(card_number);

    }
    else
    {

        valid = false;

    }

    if (valid)
    {

        printf("%s", type);

    }
    else
    {
        printf("INVALID\n");
    }

    return valid;

}

// performs Luhn's Algorithim
bool luhn_check(long card_number)
{

    // create an array with all digits in the number
    long digit_count = get_digit_count(card_number);
    long digits[digit_count];
    for (int i = 0; i < digit_count; i++)
    {

        digits[i] = get_digit_at(i + 1, card_number, digit_count);
        // printf("Digit %ld\n", digits[i]);

    }

    // multiply every other number by two and store it in another array
    int manipulated_digits_count = (digit_count % 2 == 0) ? digit_count / 2 : (digit_count - 1) / 2;
    int manipulated_sec_digits_count = (digit_count % 2 == 0) ? digit_count / 2 : (digit_count + 1) / 2;
    long manipulated_digits[manipulated_digits_count];
    for (int i = 0; i < manipulated_digits_count; i++)
    {

        manipulated_digits[i] = digits[digit_count - 2 - (i * 2)] * 2;
        // printf("Manipulated Digit %ld\n", manipulated_digits[i]);

    }

    // add the sums of every other number to two independent variables, add them both later
    long first_half = 0;
    long second_half = 0;
    long final = 0;
    for (int i = 0; i < manipulated_digits_count; i++)
    {

        // check if the number has more than one digit, if so add each independently
        if (manipulated_digits[i] < 10)
        {

            first_half += manipulated_digits[i];
            // printf("First half A %ld\n", first_half);

        }
        else
        {

            first_half = first_half + (manipulated_digits[i] / 10 % 10) + (manipulated_digits[i] % 10);
            // printf("First half B %ld\n", first_half);

        }

    }


    for (int i = 0; i < manipulated_sec_digits_count; i++)
    {
        second_half = second_half + digits[digit_count - 1 - (i * 2)];
        // printf("Second half %ld\n", second_half);
    }

    // printf("first %ld\n second %ld\n", first_half, second_half);
    final = first_half + second_half;

    // check if the last digit in the Luhn's algoritihim result is a zero
    if (final % 10 == 0)
    {

        // printf("true\n");
        return true;

    }
    else
    {

        // printf("false\n");
        return false;

    }

}

// returns the count of digits in a number
long get_digit_count(long number)
{

    long digit_count = 0;
    do
    {

        digit_count++;
        number /= 10;

    }
    while (number != 0);
    return digit_count;

}

// returns a digit at a certain placement (1 for first, 2 for second, etc...)
long get_digit_at(long place, long number, long digit_count)
{

    digit_count = digit_count - place;
    long multiplier = 1;
    while (digit_count > 0)
    {

        multiplier *= 10;
        digit_count--;

    }
    long return_number = number / multiplier % 10;
    return return_number;

}
