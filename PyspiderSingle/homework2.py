import random


def generate_random_coordinates(frequency=1e+6):
    rand_x_y_list = []
    frequency = int(frequency)
    for i in range(frequency):
        x = random.random()
        y = random.random()
        rand_x_y_list.append((x, y))
    print('the number of random coordinates: {}'.format(rand_x_y_list.__len__()))
    return rand_x_y_list


def get_probability(rand_x_y_list):
    in_num = 0
    for x, y in rand_x_y_list:
        if (0 < x < 0.5) and (0 < y < 1):
            in_num += 1
        if (0.5 < x < 1) and (0.5 < y < 1) and (y > x):
            in_num += 1
    print('the num of coordinates in odd number is: {}'.format(in_num))
    return in_num


if __name__ == '__main__':
    t = 1e+6
    rand_x_y_list = generate_random_coordinates(t)
    in_num = get_probability(rand_x_y_list)
    print('the probability of landing in odd region is: {}'.format(in_num / t))
