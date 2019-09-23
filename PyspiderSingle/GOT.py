import re
import os
import chardet
import traceback

os.chdir('/home/lithium/Documents')
dirlist = os.listdir('GOT')
final = open('GOTscript.txt', 'w')

for dir in dirlist:
    filelist = os.listdir(f'GOT/{dir}')
    for file in filelist:

        try:

            f = open(f'GOT/{dir}/{file}', 'rb')
            bcontent = f.read(128 * 2)
            char1 = chardet.detect(bcontent)
            content = f.read().decode(char1['encoding'])
            dia_list = re.findall(r'0000,0000,0000,,(.*?)\\N{\\fnCalibri Italic\\fs18\\1c&H3CF1F3&}(.*?){\\r}', \
                                  content)
            print(dia_list)
            print(f'GOT/{dir}/{file}')
            flag = re.findall(r'(S\d{2}E\d{2})', file)[0]
            final.write(flag + '\n')
            for dia in dia_list:
                final.write(dia[1].replace('-', ' ') + ' ')
            final.write('\n\n')
        except:
            pass
            # f = open(f'GOT/{dir}/{file}', 'rb')
            # content = f.read().decode('utf-8-sig')
            # dia_list = re.findall(r'0000,0000,0000,,(.*?)\\N{\\fnCalibri Italic\\fs18\\1c&H3CF1F3&}(.*?){\\r}', \
            #                       content)
            # print(dia_list)
            # for dia in dia_list:
            #     final.write(dia[1].replace('-', ' ') + ' ')
            # final.write('\n\n')
final.close()
