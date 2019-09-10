import re
import requests
import codecs
import hashlib
import os

if not os.path.exists('./pic'):
    os.mkdir('pic')
os.chdir('./pic')
header={'Referer':'http://66ppff.com/se/oumeisetu/','User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'}
url0='http://66ppff.com/se/chengrenkatong/665505.html'
tmp=requests.get(url0,headers=header).content
tmp=codecs.decode(tmp)

tmp2=re.findall(r'target="_blank"><img src="(.*?)" border="0" onclick="zoom\(this\)" onload="attachimg\(this, ',tmp)
for i in tmp2:
    pic=requests.get(i,headers=header).content
    name = hashlib.md5(pic).hexdigest()
    with open(name+'.jpg', 'wb') as f:
        f.write(pic)
        print('done.')