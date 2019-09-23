import requests, re, urllib.parse, lxml.html, traceback
import lxml.html
import pymongo
import redis
import threading
from multiprocessing.pool import Pool
import time

host = 'https://www.imsdb.com'
header = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36',
    'DNT': '1'}

detail_list = []
cate_list = []
info_item = []

client = pymongo.MongoClient()
handler = client.spider.movie_script
r_handler = redis.Redis()

# cate_url = 'https://www.imsdb.com/scripts/Godfather.html'
# cate_temp = requests.get(cate_url, headers=header)
# sel = lxml.html.fromstring(cate_temp.content.decode())
# cate_url_list = sel.xpath('//tr/td/a/@href')
# cate_url_list = list(set(cate_url_list))
# for i in cate_url_list:
#     if '/genre/' in i:
#         cate_list.append(host + i)
# print(cate_list)

def get_movie_of_category(url):
    de_temp = requests.get(url, headers=header).content.decode('iso-8859-1')
    dsel = lxml.html.fromstring(de_temp)
    movie_list = dsel.xpath('//*[@id="mainbody"]/table[2]/tr/td[@valign="top"]/p')
    for i in movie_list:
        url = host + i.xpath('a/@href')[0]
        r_handler.lpush('movie:dp0', url)
        detail_list.append(url)


def parse_detail(url):
    print(threading.currentThread())
    temp1 = requests.get(url, headers=header).content.decode('iso-8859-1')
    temp2 = lxml.html.fromstring(temp1)

    raw_info = temp2.xpath('//*[@id="mainbody"]/table[2]/tr/td[3]/table[1]/tr[2]/td[2]')[0].text_content().replace(
        '\r\n', '').replace('\t', '').replace('\xa0', ' ').replace('  ', '')
    # raw_info = temp2.xpath('//*[@id="mainbody"]/table[2]/tr/td[3]/table[1]/tr[2]/td[2]')[0].text_content().replace(
    #     '\r\n', '').replace('\t', '').replace('\xa0', ' ').replace('  ', '')

    item = {}
    _ = re.search('Writers(.*)Genres', raw_info)
    writer = _.group(1) if _ else ''

    _ = re.search('Genres(.*)Script', raw_info)
    genres = _.group(1) if _ else ''

    _ = re.findall('Date :(.*)Read', raw_info)
    script_date = _[0] if _ else ''

    script_url = host + temp2.xpath('//*[@class="script-details"]/tr[2]/td[2]/a/@href')[-1]
    # script_url=urllib.parse.quote(script_url)

    item['writer'] = writer
    item['genres'] = genres
    item['script_date'] = script_date
    item['script_url'] = script_url

    get_script(script_url, item)


def get_script(url, item):
    print('detail:'+url)
    temp = requests.get(url, headers=header).content.decode('iso-8859-1')
    temp = lxml.html.fromstring(temp)
    try:
        script_main = temp.xpath('//*[@id="mainbody"]/table[2]/tr/td[3]/table/tr/td/pre')[0]
        script_raw = script_main.text_content()

    except:
        try:
            print(traceback.format_exc())
            script_main = temp.xpath('//*[@id="mainbody"]/table[2]/tr/td[3]/table/tr/td')[0]
            script_raw = script_main.text_content()
        except:
            script_raw=''
            traceback.print_exc()

    try:
        filename=re.findall('scripts/(.*)\.html',item['script_url'])[0]
    except:
        filename=int(time.time())
    fp=open('movie_scripts/{}.txt'.format(filename),'w',encoding='utf-8')
    fp.write(script_raw)
    fp.close()
    item0={}
    item0['info']=item
    item0['script_raw'] = script_raw
    handler.insert_one(item0)

# url_list=[]
# # while True:
# #     url=r_handler.lpop('movie:dp0').decode()
# #     if not url:
# #         break
# #     url_list.append(url)
# # fp=open('movie_urls.txt','a+')
# # for i in url_list:
# #     fp.writelines([i,'\n'])
# # fp.close()
p=Pool()
fp=open('movie_urls.txt','r')
url_list=fp.read().splitlines()
fp.close()
r=p.map(parse_detail,url_list)
# for cate in cate_list:
#     get_movie_of_category(cate)

# flag=1
# thread_list = []
# import os
# if not os.path.exists('movie_scripts'):
#     os.mkdir('movie_scripts')
# while flag:
#     url = r_handler.lpop('movie:dp0').decode()
#     # url=urllib.parse.unquote(url)
#     print(url+';')
#     if not url:
#         break
#     t = threading.Thread(parse_detail(url))
#     # t.setDaemon(daemonic=True)
#     thread_list.append(t)
#     # for i in thread_list:
#     #     if i.is_alive():
#     #         break
#     # flag=0
#     t.start()
#     t.join()
#     print(thread_list.__len__())


