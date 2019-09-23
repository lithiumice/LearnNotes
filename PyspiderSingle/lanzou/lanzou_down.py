import requests
import re
import json


class lanzou(object):
    def __init__(self):
        login_url = 'https://pc.woozooo.com/account.php'
        login_data = {
            'action': 'login',
            'task': 'login',
            'ref': '/mydisk.php',
            'formhash': 'eba360ff',
            'username': '18623452248',
            'password': '135hualin'
        }
        self.ua_header = {
            'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'}
        self.login_header = {
            'origin': 'https://pc.woozooo.com',
            'referer': 'https://pc.woozooo.com/account.php?action=login&ref=/mydisk.php',
            'upgrade-insecure-requests': '1',
            'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'
        }

        login_response = requests.post(login_url, data=login_data, headers=self.login_header)

        login_cookies = login_response.headers['Set-Cookie']
        self.list_header = {
            'accept': 'application/json, text/javascript, */*; q=0.01',
            'accept-encoding': 'gzip, deflate, br',
            'accept-language': 'zh-CN,zh;q=0.9',
            'content-type': 'application/x-www-form-urlencoded; charset=UTF-8',
            'cookie': login_cookies,
            'origin': 'https://pc.woozooo.com',
            'referer': 'https://pc.woozooo.com/mydisk.php?item=files&action=index&u=18623452248',
            'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36',
            'x-requested-with': 'XMLHttpRequest'
        }
        self.request_url = 'https://pc.woozooo.com/doupload.php'
        print('init done.')

    def file_list(self):

        file_list_page = 1
        post_data = {
            'task': '5',
            'folder_id': '-1',
            'pg': file_list_page
        }
        file_list = requests.post(self.request_url, data=post_data, headers=self.list_header).content.decode()
        file_id_list = re.findall('"id":"(.*?)"', file_list)
        for file_id in file_id_list:
            print(file_id)
            self.catch_file_url(file_id)


    def catch_file_url(self,url):
        request_url_1 = 'https://pc.woozooo.com/doupload.php'
        get_file_url_data_1 = {'task': 22, 'folder_id': url}
        msg_1 = requests.post(request_url_1, json=get_file_url_data_1, headers=self.list_header).content.decode()
        msg_1 = json.loads(msg_1)
        print(msg_1)
        url = msg_1['info']['is_newd'] + '/' + msg_1['info']['f_id'] + msg_1['info']['taoc']
        self.down_url(url)

    def down_url(self, url):
        detail = requests.get(url, headers=self.ua_header).content.decode()
        src = re.search('src="(.*?)"', detail).group(1)
        temp = re.search('f=(.*?)&t=(.*?)&k=(.*?)"', src)
        f = temp.group(1)
        t = temp.group(2)
        k = temp.group(3)
        url = 'https://www.lanzous.com/ajaxm.php'
        data = {
            'action': 'down_process',
            'file_id': f,
            't': t,
            'k': k
        }
        down_main = requests.post(url, data=data, headers=self.ua_header).content.decode()
        down_main = json.loads(down_main)
        down_url = down_main['dom'] + '/file/' + down_main['url']
        print(down_url)

hand=lanzou()
hand.file_list()