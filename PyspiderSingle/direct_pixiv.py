# coding:utf-8
import requests
import json
import re
import pymongo
import random
import time
import logging
import os
from steam_down import *


# from mylib.random_proxy_request import *


class RandomProxyDown(object):
    def __init__(self, url, headers, timeout=7, retry_num=5):
        self.url = url
        self.headers = headers
        self.timeout = timeout
        self.retry_num = retry_num
        client = pymongo.MongoClient()
        self.post = client['spider']['ip_list_qy']
        self.down()

    def down(self):
        while self.retry_num:
            ip, port = self.post.find_one({}, {'ip': 1, 'port': 1, '_id': 0})
            proxy = ip + ':' + port
            try:
                request = requests.get(self.url, headers=self.headers, timeout=self.timeout, proxies=proxy)
                return request
            except:
                self.post.delete_one({'ip': ip if ip else 'null'})
                self.retry_num = self.retry_num - 1
        # can not request
        return -1


class GetPixiv(object):
    def __init__(self):
        self.header = {'accept': '*/*',
                       'Cookie': 'first_visit_datetime_pc=2019-01-26+11%3A45%3A54; p_ab_id=0; p_ab_id_2=5; p_ab_d_id=1547886661; __utma=235335808.2046861432.1548470757.1548470757.1548602022.2; __utmz=235335808.1548470757.1.1.utmcsr=baidu|utmccn=(organic)|utmcmd=organic; __utmv=235335808.|2=login%20ever=no=1^9=p_ab_id=0=1^10=p_ab_id_2=5=1^11=lang=zh=1; _ga=GA1.2.2046861432.1548470757; PHPSESSID=32448730_854cb92f139dd0486d5235e6cbab7982; __utmb=235335808.1.10.1548602022; __utmc=235335808; __utmt=1; login_bc=1; _gid=GA1.2.606105584.1548602070; device_token=9ae999ac1319ed92e6399f7b02eb4210; _gat=1',
                       'accept-encoding': 'gzip, deflate, br',
                       'accept-language': 'zh-CN,zh;q=0.9',
                       'referer': 'https://www.pixiv.net/discovery',
                       'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36', }
        self.host = 'https://www.pixiv.net/member_illust.php?mode=medium&illust_id='
        self.url = 'https://www.pixiv.net/rpc/recommender.php?type=illust&sample_illusts=auto&num_recommendations=1000&page=discovery&mode=all'
        self.proxy = {'https': '127.0.0.1:45981'}
        client = pymongo.MongoClient(host='127.0.0.1')
        self.post = client['spider']['pixiv_illust_id']
        self.logger = logging.getLogger(__name__)
        self.logger.setLevel(level=logging.INFO)
        handler = logging.FileHandler("pic_log.txt")
        handler.setLevel(logging.INFO)
        formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
        handler.setFormatter(formatter)

        console = logging.StreamHandler()
        console.setLevel(logging.INFO)

        self.logger.addHandler(handler)
        self.logger.addHandler(console)

        self.downer = SteamDown()

        if not os.path.exists('./img'):
            os.mkdir('./img')
        os.chdir('./img')
        print('init finished.')

    def down_pic(self):
        jss = self.random_proxy_down_content(self.url)
        print('download id list done.')
        jrr = json.loads(jss)
        ill_list = jrr['recommendations']
        for ill in ill_list:
            if not self.is_exists(ill):
                continue
            self.down_detail(ill)

    def is_exists(self, pic_id):
        if self.post.find({'pic_id': pic_id}).count():
            print(f'id {pic_id} already exists.')
            return False
        else:
            return True

    def down_detail(self, ill):
        try:
            jsr = self.random_proxy_down_content(url=self.host + str(ill)).decode('utf-8')
            print('download page source done.')
            title = re.search('"illustTitle":"(.*?)"', jsr).group(1)
            img_url_temp = re.search('"original":"(http.*?)"', jsr).group(1)
            user_id = re.search('"userId":"(.*?)"', jsr).group(1)
            img_url = ''.join(img_url_temp.split('\\'))
            illust_info = {}
            illust_info['pic_id'] = ill
            illust_info['user_id'] = user_id
            illust_info['title'] = title
            illust_info['url'] = img_url
            self.post.insert(illust_info)
            self.save_image(img_url, title, filepath='./')
            print(f'process pic url:{img_url} done!')
        except:
            self.logger.error('Fail.', exc_info=True)

    def save_image(self, img_url, title, filepath):
        try:
            temp = img_url.split('/')[-1]
            afterfix = ''.join(temp.split('_p0'))
            filename = title + f'{afterfix}'
            filename = re.sub('/', '', filename)

            if not os.path.exists(filepath):
                os.mkdir(filepath)

            f=open(f'{filepath}/{filename}','w')
            f.close()

            with open('{}/{}'.format(filepath,filename), 'wb') as f:
                img_content = self.random_proxy_down_content(img_url)
                f.write(img_content)
            # print(f'save image done,current path is {os.getcwd()}')
        except Exception:
            self.logger.error('save image error.', exc_info=True)

    def random_proxy_down_content(self, url):
        # random_header = self.header
        # random_header['user-agent'] = random.choice(self.USER_AGENT_LIST)
        content = requests.get(url=url, headers=self.header, proxies=self.proxy).content
        print('request done.')
        return content

    def fetch_all_pic(self, user_id):
        json_url = f'https://www.pixiv.net/ajax/user/{user_id}/profile/all'
        json_content = self.random_proxy_down_content(json_url).decode()
        json_pic = json.loads(json_content)
        pic_list = json_pic['body']['illusts']
        print('fetch pic list done.')
        for pic in pic_list:
            if not self.is_exists(pic):
                continue
            self.down_detail(pic)

    def get_all_usr_pic(self):
        user_list = self.post.find({}, {'user_id': 1, '_id': 0})
        temp_iter = []
        for user in user_list:
            temp_iter.append(user['user_id'])
        temp_iter = list(set(temp_iter))
        for temp in temp_iter:
            self.fetch_all_pic(temp)


try:
    # start download pic of pixiv
    handler = GetPixiv()
    # handler.down_pic()
    handler.get_all_usr_pic()
    print('All done!')
except:
    pass
finally:
    pass
    # os.system('shutdown -h')
    # os.system('shutdown -h -s 1')
