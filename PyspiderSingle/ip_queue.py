import requests
import pymongo
import random
import time
import redis
import traceback
from requests.exceptions import Timeout
import ssl
ssl._create_default_https_context = ssl._create_unverified_context

client = pymongo.MongoClient()
post = client['spider']['ip_list_qy']

hand = redis.Redis()
redis_table = 'list:xici:ip:https'


def mongodb_to_redis():
    for i in post.find():
        proxy = i['ip'] + i['port']
        hand.sadd('xici:ip', proxy)


def mongodb_to_list():
    for i in post.find():
        proxy = i['ip'] + ':' + i['port']
        hand.lpush('list:xici:ip:2', proxy)


def mongodb_to_list_2():
    for i in post.find():
        protol = i['protol'].lower()
        if protol == 'http':
            proxy = protol + '://' + i['ip'] + ':' + i['port']
            hand.lpush('list:xici:ip:http', proxy)
        elif protol == 'https':
            proxy = protol + '://' + i['ip'] + ':' + i['port']
            hand.lpush('list:xici:ip:https', proxy)


# def request_by_proxy(url, retry_num, timeout, **kwargs):
#     timeout = timeout / retry_num
#     for i in range(retry_num):
#         random_num = random.randint(0, table_len + 1)
#         try:
#             proxy_ip = hand.lrange(redis_table, random_num, random_num).decode()
#             proxies = {'https': proxy_ip}
#             tmp = requests.get(url, timeout, proxies=proxies, **kwargs)
#             return tmp
#         except:
#             hand.lset(redis_table, random_num, 'del')
#             hand.lrem(redis_table, 0, 'del')
#             print('delete proxy')
def request_by_proxy(url, headers):
    for i in range(5):
        random_num = random.randint(0, hand.llen(redis_table) + 1)
        try:
            proxy_ip = hand.lrange(redis_table, random_num, random_num)[0].decode()
            proxies = {'https': proxy_ip}
            tmp = requests.get(url, proxies=proxies, headers=headers)
            return tmp
        except:
            hand.lset(redis_table, random_num, 'del')
            hand.lrem(redis_table, 0, 'del')
            print('delete proxy',random_num)


class ProxyRequest(object):
    def __init__(self, redis_table_name='list:xici:ip:https'):
        self.hand = redis.Redis()
        redis_table = redis_table_name
        self.table_len = hand.llen(redis_table)
        print(self.table_len)

    # def request_by_proxy(self,url, retry_num=5, timeout=20, **kwargs):
    #
    #     timeout = timeout / retry_num
    #     for i in range(retry_num):
    #         random_num = random.randint(0, self.table_len + 1)
    #         try:
    #             proxy_ip = self.hand.lrange(redis_table, random_num, random_num).decode()
    #             proxies = {'https': proxy_ip}
    #             tmp = requests.get(url, timeout=timeout, proxies=proxies, **kwargs)
    #             return tmp
    #         except:
    #             traceback.print_exc()
    #             self.hand.lset(redis_table, random_num, 'del')
    #             self.hand.lrem(redis_table, 0, 'del')
    #             print('delete proxy')
    #     raise Timeout('proxy fail')

    def request_by_proxy(self,url, **kwargs):
        for i in range(5):
            print(i)
            random_num = random.randint(0, hand.llen(redis_table) + 1)
            print(random_num)
            proxies=''
            try:
                proxy_ip = self.hand.lrange(redis_table, random_num, random_num)[0].decode()
                print(proxy_ip)
                proxies = {'https': proxy_ip}
                print(proxies)
                tmp = requests.get(url,  proxies=proxies, **kwargs)
                print(tmp)
                return tmp
            except:
                print(proxies)
                traceback.print_exc()
                self.hand.lset(redis_table, random_num, 'del')
                self.hand.lrem(redis_table, 0, 'del')
                print('delete proxy')
        raise Timeout('proxy fail')
    def get(self,**kwargs):
        return request_by_proxy(**kwargs)