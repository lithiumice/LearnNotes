# coding:utf-8
import requests
import json
import re
import pymongo
import random
import time
import logging
import os
from multiprocessing.dummy import Pool

class GetPixiv(object):
    def __init__(self):
        self.USER_AGENT_LIST = [
            'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36',
            "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36",
            "Dalvik/1.6.0 (Linux; U; Android 4.2.1; 2013022 MIUI/JHACNBL30.0)",
            "Mozilla/5.0 (Linux; U; Android 4.4.2; zh-cn; HUAWEI MT7-TL00 Build/HuaweiMT7-TL00) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1",
            "AndroidDownloadManager",
            "Apache-HttpClient/UNAVAILABLE (java 1.4)",
            "Dalvik/1.6.0 (Linux; U; Android 4.3; SM-N7508V Build/JLS36C)",
            "Android50-AndroidPhone-8000-76-0-Statistics-wifi",
            "Dalvik/1.6.0 (Linux; U; Android 4.4.4; MI 3 MIUI/V7.2.1.0.KXCCNDA)",
            "Dalvik/1.6.0 (Linux; U; Android 4.4.2; Lenovo A3800-d Build/LenovoA3800-d)",
            "Lite 1.0 ( http://litesuits.com )",
            "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET4.0C; .NET4.0E; .NET CLR 2.0.50727)",
            "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/38.0.2125.122 Safari/537.36 SE 2.X MetaSr 1.0",
            "Mozilla/5.0 (Linux; U; Android 4.1.1; zh-cn; HTC T528t Build/JRO03H) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30; 360browser(securitypay,securityinstalled); 360(android,uppayplugin); 360 Aphone Browser (2.0.4)",
        ]
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

        self.pool=Pool(5)

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
            filename = title + f'({afterfix})'
			filename = re.sub('/', '', filename)

            if not os.path.exists(filepath):
                os.mkdir(filepath)

			f=open(f'{filepath}/{filename}','w')
            f.close()
			
            with open(f'{filepath}/{filename}', 'wb') as f:
                img_content = self.random_proxy_down_content(img_url)
                f.write(img_content)
            print(f'save image done,current path is {os.getcwd()}')
        except Exception as e:
            self.logger.error('save image error.', exc_info=True)

    def random_proxy_down_content(self, url):
        # time.sleep(random.randint(1, 4))
        # random_header = self.header
        # random_header['user-agent'] = random.choice(self.USER_AGENT_LIST)
        content = requests.get(url, headers=self.header, proxies=self.proxy).content
        print('request done.')
        return content

    def fetch_all_pic(self, user_id):
        try:
            json_url = f'https://www.pixiv.net/ajax/user/{user_id}/profile/all'
            json_content = self.random_proxy_down_content(json_url).decode()
            json_pic = json.loads(json_content)
            pic_list = json_pic['body']['illusts']
            print('fetch pic list done.')
            for pic in pic_list:
                if not self.is_exists(pic):
                    continue
                self.down_detail(pic)
        except:
            print('error skipped.')

    def get_all_usr_pic(self):
        user_list = self.post.find({}, {'user_id': 1, '_id': 0})
        temp_iter=[]
        for user in user_list:
            temp_iter.append(user['user_id'])
        self.pool.map(self.fetch_all_pic,temp_iter)


# start download pic of pixiv
handler = GetPixiv()
# handler.down_pic()
handler.get_all_usr_pic()
print('All done!')
