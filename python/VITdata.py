import random

tmp = ['T', 'F']
with open('test.txt', 'w', encoding='utf-8') as f:
    f.write('id gender T/F\n')
    for i in range(1, 51):
        tf = random.choice(tmp)
        f.write(str(i) + '\t' + 'Female' + '\t' + tf)
        f.write('\n')
        tf = random.choice(tmp)
        f.write(str(i) + '\t' + 'Male' + '\t' + tf)
        f.write('\n')
