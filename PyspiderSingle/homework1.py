def count(i):
    i = int(i)
    e = 1
    tmp = 1.0
    for t in range(1, i + 1):
        tmp /= t
        e += tmp
    return e


if __name__ == '__main__':
    i = input('input e:')
    e = count(i)
    print(f'result is {e}')
