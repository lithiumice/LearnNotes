import math


def is_prime(num: int):
    if num <= 1:
        return -1
    if num == 2:
        return 1
    for i in range(2, num):
        if (num % i) == 0:
            return 0
    return 1


def is_palin(num: int):
    tmp1 = str(num)
    tmp2 = tmp1[::-1]
    if tmp1 == tmp2:
        return 1
    else:
        return 0


if __name__ == "__main__":
    count = 0
    i = 100
    while (count <= 100):
        if (is_prime(i) and is_palin(i)):
            print(i, end='')
            if ((count != 0) & (count % 10 == 0)):
                print('\n', end='')
            else:
                print('\t', end='')
            count += 1
        i += 1
