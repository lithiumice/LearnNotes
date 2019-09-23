import requests
import re
import json
import os
from urllib.parse import urlencode
from ToolFuc.tools import ChromeHeaders2Dict

login_header = {}
ua_header = {
    'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'}


def cookies_to_dict(cookies: str):
    cookies_dict = {}
    cook_split = cookies.split(';')
    for cook in cook_split:
        cook = cook.strip(' ')
        name, value = cook.split('=')
        name = name.strip(' ')
        value = value.strip(' ')
        cookies_dict[name] = value
    return cookies_dict


def login():
    login_url = 'https://pc.woozooo.com/account.php'
    login_data = {
        'action': 'login',
        'task': 'login',
        'ref': '/mydisk.php',
        'formhash': 'eba360ff',
        'username': '18623452248',
        'password': '135hualin'
    }
    raw_header = {
        'origin': 'https://pc.woozooo.com',
        'referer': 'https://pc.woozooo.com/account.php?action=login&ref=/mydisk.php',
        'upgrade-insecure-requests': '1',
        'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'
    }
    login_response = requests.post(login_url, data=login_data, headers=raw_header)
    login_cookies = login_response.headers['Set-Cookie']
    login_header = {
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


def test_login():
    post_data = {
        'task': '5',
        'folder_id': '-1',
        'pg': '1',
    }
    response = requests.post('https://pc.woozooo.com/doupload.php', data=post_data, headers=login_header)
    print(response.headers)
    print(response.content.decode())


file_to_backup = './world.zip'


def post_file():
    post_file_url = 'https://pc.woozooo.com/fileup.php'
    post_cookies = {
        'UM_distinctid': '167c148f761119-0cc301b871f4a8-76123f4b-144000-167c148f76221f',
        'PHPSESSID': 'bj9saraupquc6nesfrci3gn5eaceth9f',
        'phpdisk_info': 'BzRfZVI3UGoEMgBiCllWOAFYUWJdPAJjVGVSMQEzCj1RZ15uUTcANFNYAjEIZFdvB2QDNws2AmADNQZgVzNQZQc7X29SN1BrBGAAYgpgVmgBY1FjXWYCbFRvUjMBNwppUWJeOlE2ADtTYwJbCGNXNQdhAzMLYQJhAzUGZFdjUGYHOw%3D%3D',
        'ylogin': '787642',
        'CNZZDATA1253610886': '371681567-1545134562-https%253A%252F%252Fpc.woozooo.com%252F%7C1553670951'
    }
    post_file_header = {'accept': '*/*',
                        'accept-encoding': 'gzip, deflate, br',
                        'accept-language': 'zh-CN,zh;q=0.9',
                        'content-length': '12320',
                        'content-type': 'multipart/form-data; boundary=----WebKitFormBoundaryHB9AHAASh8Mf1CG3',
                        'cookie': 'UM_distinctid=167c148f761119-0cc301b871f4a8-76123f4b-144000-167c148f76221f; PHPSESSID=bj9saraupquc6nesfrci3gn5eaceth9f; phpdisk_info=BzRfZVI3UGoEMgBiCllWOAFYUWJdPAJjVGVSMQEzCj1RZ15uUTcANFNYAjEIZFdvB2QDNws2AmADNQZgVzNQZQc7X29SN1BrBGAAYgpgVmgBY1FjXWYCbFRvUjMBNwppUWJeOlE2ADtTYwJbCGNXNQdhAzMLYQJhAzUGZFdjUGYHOw%3D%3D; ylogin=787642; CNZZDATA1253610886=371681567-1545134562-https%253A%252F%252Fpc.woozooo.com%252F%7C1553670951',
                        'origin': 'https://pc.woozooo.com',
                        'referer': 'https://pc.woozooo.com/mydisk.php?item=files&action=index&u=18623452248',
                        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36'}
    post_file_formdata = {'task': (None, '1'),
                          'folder_id': ('-1'),
                          'id': (None, 'WU_FILE_1'),
                          'size': (None, '11354'),
                          'upload_file': ('readmdict.7z', open(r'D:\data_analysis\py-spider\readmdict.7z', 'rb'),
                                          'application/octet-stream')}
    post_result = requests.post(url=post_file_url, cookies=post_cookies, files=post_file_formdata).content.decode()
    print(post_result)

if __name__=='main':
    login()
    post_file()
    print('finished!')
