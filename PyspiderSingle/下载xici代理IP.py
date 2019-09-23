from ip_queue import ProxyRequest
import lxml.html
import pymongo
import logging
import random
import time
import threading
import traceback
import redis
import requests
import urllib3
urllib3.disable_warnings()

header = {'Host': 'www.xicidaili.com',
          'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:64.0) Gecko/20100101 Firefox/64.0',
          }
client = pymongo.MongoClient()
post = client['spider']['xici:ip']
host = 'https://www.xicidaili.com'
hand = redis.Redis()
redis_table = 'list:xici:ip:https'


def request_by_proxy(url, headers):
    random_num = random.randint(0, hand.llen(redis_table) + 1)
    proxy_ip = hand.lrange(redis_table, random_num, random_num)[0].decode()
    proxies = {'https': proxy_ip}
    print(proxy_ip)
    tmp = requests.get(url=url, proxies=proxies, headers=headers)
    return tmp


def start_down(aferfix):
    time.sleep(1)
    xici = request_by_proxy(url=f'https://www.xicidaili.com/{aferfix}', headers=header).content
    print(xici)
    sel = lxml.html.fromstring(xici)
    main_page = sel.xpath('//table[@id="ip_list"]')[0].xpath('tr')
    for ip_info in main_page:
        info = ip_info.xpath('td/text()')
        if not info:
            continue
        ip_list = {}
        ip = info[0]
        port = info[1]
        protol = info[4]
        ip_list['ip'] = ip
        ip_list['port'] = port
        ip_list['protol'] = protol
        post.insert(ip_list)
        print(ip_list)
    next_page = sel.xpath('//*[@class="next_page"]/@href')[0]
    next_url = host + next_page
    recusive(next_url)


def recusive(url):
    xici = request_by_proxy(url, headers=header).content
    sel = lxml.html.fromstring(xici)
    main_page = sel.xpath('//table[@id="ip_list"]')[0].xpath('tr')
    for ip_info in main_page:
        info = ip_info.xpath('td/text()')
        if not info:
            continue
        ip_list = {}
        ip = info[0]
        port = info[1]
        protol = info[4]
        ip_list['ip'] = ip
        ip_list['port'] = port
        ip_list['protol'] = protol
        post.insert(ip_list)
        print(ip_list)
    next_page = sel.xpath('//*[@class="next_page"]/@href')[0]
    next_url = host + next_page
    recusive(next_url)


def down_all_ip():
    xici_list = ['nt/', 'nn/']
    # xici_list = ['wn', 'wt', 'nt', 'nn']
    # try:
    #     for xici in xici_list:
    #         start_down(xici)
    # except:
    #     traceback.print_exc()
    for xici in xici_list:
        start_down(xici)


if __name__ == "__main__":
    down_all_ip()
    # random_num = random.randint(0, hand.llen(redis_table) + 1)
    # proxy_ip = hand.lrange(redis_table, random_num, random_num)[0].decode()
    # proxies={'https': proxy_ip}
    # print(proxy_ip)
    # tmp = requests.get(url='https://www.baidu.com', proxies=proxies,headers=header,verify=False)
    # print(tmp.content.decode())
