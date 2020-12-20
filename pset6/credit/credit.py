from cs50 import get_int


def main():
    card = get_int("Number: ")
    if luhn(card):
        cardtype(card)
    else:
        print("INVALID")


def luhn(card):
    digits = [int(x) for x in str(card)]
    digits.reverse()
    cursor = 0
    first = list()
    second = list()
    for num in digits:
        if cursor is 0:
            first.append(num)
            cursor = 1
        elif cursor is 1:
            second.append(num * 2)
            cursor = 0
    first_total = 0
    for num in first:
        first_total += num
    second_total = 0
    for num in second:
        if num >= 10:
            num = num % 10 + 1
        second_total += num
    sum = first_total + second_total
    if sum % 10 is 0:
        return True
    else:
        return False


def cardtype(card):
    digits = [int(x) for x in str(card)]
    if len(digits) is 15:
        if digits[0] * 10 + digits[1] in [34, 37]:
            print("AMEX")
        else:
            print("INVALID")
    elif len(digits) in [13, 16]:
        if digits[0] is 4:
            print("VISA")
        elif len(digits) is 16 and digits[0] * 10 + digits[1] in [51, 52, 53, 54, 55]:
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


main()
