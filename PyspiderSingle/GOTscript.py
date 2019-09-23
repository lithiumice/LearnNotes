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
            print(f'GOT/{dir}/{file}')
        # try:
            f = open(f'GOT/{dir}/{file}', 'rb')
            bcontent = f.read(32)
            char1 = chardet.detect(bcontent)
            content = f.read().decode(char1['encoding'])
            s_list = content.splitlines()
            for s in s_list:
                tmp = re.findall(r'0000,0000,0000,,(.*)\\N{\\f.*}(.*)', s)
                if not tmp:
                    continue
                tmp=tmp[0]

                tmp2 = tmp[1].replace('{\\r}','') + '  ' + tmp[0].replace('{\\r}','') + '\n'
                print(tmp2)
                final.write(tmp2)

            final.write('\n\n\n')
        # except:
        #     traceback.print_exc()


final.close()
