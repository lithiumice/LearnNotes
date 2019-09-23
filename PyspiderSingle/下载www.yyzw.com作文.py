import requests
import csv
import lxml.html
import asyncio
import time
import random
import traceback
import re

header = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'}
host = 'http://www.yyzw.com'
first_url = 'http://www.yyzw.com/daxue/'


def write_csv():
    with open('dxzw2.csv', 'w', encoding='utf-8') as f:
        fp = csv.DictWriter(f, fieldnames=['title', 'article'])
        fp.writeheader()
        while True:
            a = yield True
            fp.writerow({'title': a[0], 'article': a[1]})


def main_parse():
    for i in range(1, 100):
        try:
            url = f'http://www.yyzw.com/daxue/list_4_{i}.html'
            temp = requests.get(url, headers=header).content.decode('gb2312')
            selector = lxml.html.fromstring(temp)
            url_list = selector.xpath('//a[@class="title"]/@href')
            for u in url_list:
                await main(host + u)
        except:
            tra = traceback.format_exc()
            if 'illegal multibyte sequence' in tra:
                pass
            else:
                print(i)
                return
    try:
        next_url = selector.xpath('//ul[@class="pagelist"]/li')[-3].xpath('a/@href')[0]
        main_parse(first_url+next_url)
    except:
        print('end')



def detail(url):
    temp = requests.get(url).content.decode('gb2312')
    sel = lxml.html.fromstring(temp)
    title = sel.xpath('//div[@class="article-title"]/h1/text()')[0]
    art = sel.xpath('//div[@class="content"]')[0].text_content().replace('\t', '').splitlines()[:-5]
    article = ''
    for a in art:
        if a:
            article += a
    arti = re.findall(r'[a-z]|[A-Z]|\W.*', article)
    article = ''.join(arti)
    print(title + ':' + article)
    handler.send([title, article])
