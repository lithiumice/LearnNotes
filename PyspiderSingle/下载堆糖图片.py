import sys
import requests
import json
import re
import os

head = {
    'Host': 'www.duitang.com',
    'Referer': 'https://www.duitang.com/album/?id=72928964',
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:64.0) Gecko/20100101 Firefox/64.0', }
# header={
# 'Host': 'www.duitang.com',
# 'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:64.0) Gecko/20100101 Firefox/64.0',
# 'Accept': 'text/plain, */*; q=0.01',
# 'Accept-Language': 'zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2',
# 'Accept-Encoding': 'gzip, deflate, br',
# 'Referer': 'https://www.duitang.com/album/?id=72928964',
# 'X-Requested-With': 'XMLHttpRequest',
# 'Connection': 'keep-alive',
# 'Cookie': 'sessionid=7b63fcae-9e3f-42b9-bd24-08b89ffd4883; Hm_lvt_d8276dcc8bdfef6bb9d5bc9e3bcfcaf4=1548778590,1548862896; js=1; Hm_lpvt_d8276dcc8bdfef6bb9d5bc9e3bcfcaf4=1548863118; dt_auth=eyJhbGciOiJIUzI1NiJ9.eyJleHAiOjE1NDg5NDg4MjEsInN1YiI6IuS_oeS7sOWcqOmjjuS4remjmOaJrCIsImlkIjoxOTU2MTczMiwicGxhdGZvcm0iOiJXRUIiLCJ2ZXJzaW9uIjoxfQ.BXFG48FxvuRkwi3wVrAcqKmu04_zkiwOsLXknCNh6ls; _auth_user_id=19561732; username=%E4%BF%A1%E4%BB%B0%E5%9C%A8%E9%A3%8E%E4%B8%AD%E9%A3%98%E6%89%AC; _fromcat=category; sgm=usedtags%3D%25u5BB6%25u5C45%253B%25u8BBE%25u8BA1%253B%25u63D2%25u753B%253B%25u7535%25u5F71%253B%25u65C5%25u884C%253B%25u624B%25u5DE5%253B%25u5973%25u88C5%253B%25u7537%25u88C5%253B%25u914D%25u9970%253B%25u7F8E%25u98DF%253B%25u6444%25u5F71%253B%25u827A%25u672F%253B%257C%253B%25u5C01%25u9762%253B%25u52A8%25u6F2B%253B%25u6000%25u65E7%253B%25u8857%25u62CD%253B%25u5C0F%25u5B69%253B%25u5BA0%25u7269%253B%25u690D%25u7269%253B%25u4EBA%25u7269'
# }
start = 72
i = 0
while True:
    url = f'https://www.duitang.com/napi/blog/list/by_album/?album_id=72928964&limit=24&start={start}'
    response = requests.get(url, headers=head).content.decode()
    js = json.loads(response)
    try:
        start = js['data']['next_start']
    except:
        break
    mlist = js['data']['object_list']
    for m in mlist:
        img = m['photo']['path']
        # title = m['msg']
        r = requests.get(img, stream=True)
        total_size = int(r.headers['Content-Length'])
        temp_size = 0
        with open(f'./im/{i}' + '.jpeg', 'wb') as f:
            if int(f.readline()) > 100*1024:
                continue
            for chunk in r.iter_content(chunk_size=1024):
                if chunk:
                    temp_size += len(chunk)
                    f.write(chunk)
                    f.flush()
                    done = int(50 * temp_size / total_size)
                    sys.stdout.write(f"\r[{'█' * done}{' ' * (50 - done)}] {int(100 * temp_size / total_size)}%")
                    sys.stdout.flush()
        print()
        i += 1
