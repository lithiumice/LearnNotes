import requests
import lxml.html
import pymongo
import logging
import re
import random

class get_xici(object):
    def __init__(self, flag):
        self.user_agent_list = [
            "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/22.0.1207.1 Safari/537.1",
            "Mozilla/5.0 (X11; CrOS i686 2268.111.0) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.57 Safari/536.11",
            "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.6 (KHTML, like Gecko) Chrome/20.0.1092.0 Safari/536.6",
            "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/536.6 (KHTML, like Gecko) Chrome/20.0.1090.0 Safari/536.6",
            "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/19.77.34.5 Safari/537.1",
            "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.9 Safari/536.5",
            "Mozilla/5.0 (Windows NT 6.0) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.36 Safari/536.5",
            "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.3 (KHTML, like Gecko) Chrome/19.0.1063.0 Safari/536.3",
            "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/536.3 (KHTML, like Gecko) Chrome/19.0.1063.0 Safari/536.3",
            "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_8_0) AppleWebKit/536.3 (KHTML, like Gecko) Chrome/19.0.1063.0 Safari/536.3",
            "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/536.3 (KHTML, like Gecko) Chrome/19.0.1062.0 Safari/536.3",
            "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.3 (KHTML, like Gecko) Chrome/19.0.1062.0 Safari/536.3",
            "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/536.3 (KHTML, like Gecko) Chrome/19.0.1061.1 Safari/536.3",
            "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.3 (KHTML, like Gecko) Chrome/19.0.1061.1 Safari/536.3",
            "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/536.3 (KHTML, like Gecko) Chrome/19.0.1061.1 Safari/536.3",
            "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/536.3 (KHTML, like Gecko) Chrome/19.0.1061.0 Safari/536.3",
            "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/535.24 (KHTML, like Gecko) Chrome/19.0.1055.1 Safari/535.24",
            "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/535.24 (KHTML, like Gecko) Chrome/19.0.1055.1 Safari/535.24"
        ]
        self.flag = flag
        self.client = pymongo.MongoClient()
        self.post = self.client['spider']['ip2']

        self.host = 'http://www.qydaili.com/free/'
        self.start_url = 'http://www.qydaili.com/free/?action=china'

    def start(self):
        self.down_ip(self.start_url)

    def down_ip(self, url):
        UA = random.choice(self.user_agent_list)
        header = {'User-Agent': UA}
        content = requests.get(url, headers=header,proxies={'http':'116.209.57.36:9999'}).content
        selector = lxml.html.fromstring(content)
        main_page = selector.xpath('//table[@class="table table-bordered table-striped"]/tbody')[0].xpath('tr')
        for ip_info in main_page:
            info = ip_info.xpath('td/text()')
            ip_list = {}
            ip = info[0]
            port = info[1]
            protol = info[3]
            speed = info[5]
            ip_list['ip'] = ip
            ip_list['port'] = port
            ip_list['protol'] = protol
            ip_list['speed'] = speed
            # if int(speed.rstrip('秒'))>10:
            #     continue
            self.post.insert(ip_list)
            print(ip + ':' + port + ' ' + protol)
        if not self.flag:
            return

        next_btn = selector.xpath('//nav[@aria-label="Page navigation"]/ul[@class="pagination"]/li')[7]
        href = next_btn.xpath('a/@href')[0]
        self.down_ip(self.host + href)



h = get_xici(True)
h.start()
