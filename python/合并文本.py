import os
import re

filelist=os.listdir()
for file in filelist:
    chp=file.split(' ')[0]
    with open(chp+'.txt','w+',encoding='utf-8') as f:
        f.write(open(file,'r',encoding='utf-8').read())