import requests
import lxml.html
import asyncio
import threading
import traceback
import re
import pymongo

host = 'http://www.imdb.cn'
url_1 = 'http://www.imdb.cn/IMDB250/'
url_2 = 'http://www.imdb.cn/imdb250/{}'
header = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'}
thread_list = []


def main_parse():
    error_num = 0
    for i in range(100, 252):
        try:
            if i == 1:
                url = url_1
            else:
                url = url_2.format(i)
            print(url)
            temp = requests.get(url, headers=header).content.decode()
            selector = lxml.html.fromstring(temp)
            url_list = selector.xpath('//div[@class="ss-3 clear"]/a/@href')
            for u in url_list:
                print(u)
                thread = threading.Thread(target=detail(host + u))
                thread_list.append(thread)
                thread.setDaemon(daemonic=True)
                thread.start()

        except:
            error_num += 1
            if error_num >= 20:
                return
            traceback.print_exc()


def process_info(li: list) -> str:
    l = ''  # concentrate with ;
    l = ';'.join(li)
    return l


def detail(url):
    temp = requests.get(url).content.decode()
    sel = lxml.html.fromstring(temp)

    de_list = sel.xpath('//div[@class="bdd clear"]/ul')[0].xpath('li')

    stars = sel.xpath('//div[@class="hdd"]/span/i/text()')[0]

    movie_name = de_list[0].xpath('a/text()')[0]
    el_name = de_list[1].xpath('a/text()')[0]

    director = process_info(de_list[2].xpath('a/text()'))
    main_actors = process_info(de_list[3].xpath('a/text()'))

    time_len = de_list[4].xpath('text()')[0].replace('&nbsp', '')

    language = process_info(de_list[4].xpath('a/text()'))

    t = de_list[5].text_content().replace('&nbsp', '').replace('\t', '').replace('\xa0', '')

    try:
        first_show = re.search('上映时间：(\d{4})', t).group(1)
    except:
        first_show=''
    try:
        category = re.search('类型：(.*)  分级', t).group(1)
    except:
        category=''
    try:
        levels = re.search('分级：(.*)颜色', t).group(1)

    except:
        levels=''
    try:
        color = re.search('颜色：(.*)', t).group(1)

    except:
        color=''
    try:
        b = de_list[6].text_content().replace('\r\n', '').replace('\t', '').replace('\xa0', '')
        country = re.search('国家：(.*?)声音', b).group(1)
        sound = re.search('声音：(.*)', b).group(1)
    except:
        country=''
        sound=''

    item = {
        'stars': stars,
        'movie_name': movie_name,
        'el_name': el_name,
        'director': director,
        'main_act': main_actors,
        'time_len': time_len,
        'language': language,
        'first_show': first_show,
        'category': category,
        'levels': levels,
        'color': color,
        'country': country,
        'sound': sound
    }
    print(item)
    handler.insert_one(item)


client = pymongo.MongoClient()
handler = client.spider.imdb
main_parse()
for t in thread_list:
    if t.is_alive():
        print('not end')
client.close()

import csv
fp=open('imdb250.csv','w',encoding='utf-8')
wri=csv.DictWriter(fp,fieldnames=[
        'stars',
        'movie_name',
        'el_name',
        'director',
        'main_act',
        'time_len',
        'language',
        'first_show',
        'category',
        'levels',
        'color',
        'country',
        'sound'
    ])