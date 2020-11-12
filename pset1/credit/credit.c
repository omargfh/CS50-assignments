#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void validate(string content);
bool card_check(long card_number);
bool luhn_check(long card_number);
bool INNRange(long number, long start_range, long end_range);
long get_digit_count(long number);
long get_digit_at(long place, long number);
string card_type(long card_number);


int main(void)
{

    validate("Number: ");
    return 0;

}

// calls for a valid card number
void validate(string content)
{

    long card_number;
    bool is_valid;
    do
    {

        card_number = get_long("%s", content);
        is_valid = card_check(card_number);

    }
    while (!is_valid && card_number < 1);

}

// checks if the number corresponds to a valid card and the type of that card
bool card_check(long card_number)
{

    bool checked = true;
    string type = card_type(card_number);
    if (!strncmp(type, "INVALID", 7))
    {
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

        printf("%s\n", type);

    }
    else
    {
        printf("INVALID\n");
    }

    return valid;

}

string card_type(long card_number)
{
    string type;

    long digit_count = get_digit_count(card_number);
    long first_digit = get_digit_at(1, card_number);
    long second_digit = get_digit_at(2, card_number);

    if (digit_count == 15 && (first_digit == 3 && (second_digit == 4 || second_digit == 7)))
    {

        type = "AMEX";

    }
    else if (digit_count == 16 && ((first_digit == 5 && (second_digit == 1 || second_digit == 2 || second_digit == 3
                                   || second_digit == 4 || second_digit == 5)) || INNRange(card_number, 222100, 272099)))
    {

        type = "MASTERCARD";

    }
    else if (digit_count == 14 && (first_digit == 3 && second_digit == 6))
    {
        type = "DINERS INTL";
    }
    else if ((digit_count == 13 || digit_count == 16) && first_digit == 4)
    {

        type = "VISA";

    }
    else
    {
        type = "INVALID";

    }

    return type;

}

// performs Luhn's Algorithim
bool luhn_check(long card_number)
{

    // create an array with all digits in the number
    long digit_count = get_digit_count(card_number);
    long digits[digit_count];
    for (int i = 0; i < digit_count; i++)
    {

        digits[i] = get_digit_at(i + 1, card_number);

    }

    // multiply every other number by two and store it in another array
    int manipulated_digits_count = (digit_count % 2 == 0) ? digit_count / 2 : (digit_count - 1) / 2;
    int manipulated_sec_digits_count = (digit_count % 2 == 0) ? digit_count / 2 : (digit_count + 1) / 2;
    long manipulated_digits[manipulated_digits_count];
    for (int i = 0; i < manipulated_digits_count; i++)
    {

        manipulated_digits[i] = digits[digit_count - 2 - (i * 2)] * 2;

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

        }
        else
        {

            first_half = first_half + (manipulated_digits[i] / 10 % 10) + (manipulated_digits[i] % 10);

        }

    }


    for (int i = 0; i < manipulated_sec_digits_count; i++)
    {
        second_half = second_half + digits[digit_count - 1 - (i * 2)];
    }

    final = first_half + second_half;

    // check if the last digit in the Luhn's algoritihim result is a zero
    if (final % 10 == 0)
    {

        return true;

    }
    else
    {

        return false;

    }

}

bool INNRange(long number, long start_range, long end_range)
{

  long number_digit_count = get_digit_count(number);
  long range_digit_count = (get_digit_count(start_range) == get_digit_count(end_range))
                        ? get_digit_count(start_range) : 0;
  long numbers_check[range_digit_count];
  long number_check = 0;
  for(int i = 0; i < range_digit_count; i++)
  {
    numbers_check[i] = get_digit_at(i + 1, number);
    number_check = number_check + numbers_check[i] * ( pow(10, range_digit_count - i) / 10 );
  }
  if (number_check >= start_range && number_check <= end_range)
  {

    return true;

  }
  else
  {
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
long get_digit_at(long place, long number)
{

    long digit_count = get_digit_count(number) - place;
    long multiplier = 1;
    while (digit_count > 0)
    {

        multiplier *= 10;
        digit_count--;

    }
    long return_number = number / multiplier % 10;
    return return_number;

}
