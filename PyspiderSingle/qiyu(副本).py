import requests
import lxml.html
import pymongo
import logging


class get_xici(object):
    def __init__(self, flag):
        self.header = {'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:64.0) Gecko/20100101 Firefox/64.0', }
        self.flag = flag
        self.client = pymongo.MongoClient()
        self.post = self.client['spider']['ip_list_qy']

        self.logger = logging.getLogger(__name__)
        self.logger.setLevel(level=logging.INFO)
        handler = logging.FileHandler("qiyu_log.txt")
        handler.setLevel(logging.INFO)
        formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
        handler.setFormatter(formatter)
        console = logging.StreamHandler()
        console.setLevel(logging.INFO)
        self.logger.addHandler(handler)
        self.logger.addHandler(console)
        self.host = 'http://www.qydaili.com/free/'
        self.start_url = 'http://www.qydaili.com/free/?action=unchina'

    def start(self):
        self.down_ip(self.start_url)

    def down_ip(self, url):
        content = requests.get(url, headers=self.header).content
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
            self.post.insert(ip_list)
            self.logger.info(ip + ':' + port + ' ' + protol)
        if not self.flag:
            return
        try:
            next_btn = selector.xpath('//nav[@aria-label="Page navigation"]/ul[@class="pagination"]/li')[7]
            href = next_btn.xpath('a/@href')[0]
            self.down_ip(self.host + href)
        except:
            pass


h = get_xici(True)
h.start()
