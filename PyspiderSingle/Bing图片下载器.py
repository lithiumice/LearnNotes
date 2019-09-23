import requests
import json
from urllib.parse import urlencode
import hashlib
import html
import re
import random
import time
from proxy_request import request


class BingImage(object):
    def __index__(self):
        self.header = {
            'Cookie': 'ipv6=hit=1549006281456&t=4; MMCA=ID=06D6699E55FC44D4B208ACB449C8E8DD; _IDET=NVNoti=1&MIExp=0&InsSte=0100001; MUID=363A09941623690F32C1057812236AB3; SRCHD=AF=NOFORM; SRCHUID=V=2&GUID=9B44D3F7CBE3446EBB876552AE59CDFF&dmnchg=1; SRCHUSR=DOB=20190126&T=1549002677000; MUIDB=363A09941623690F32C1057812236AB3; SRCHHPGUSR=CW=1841&CH=503&DPR=1&UTC=480&WTS=63684599477; _ITAB=STAB=TR; _SS=SID=2D25AACFB52A6D0F39E4A639B4046C22&HV=1549004389; _EDGE_S=mkt=zh-cn&ui=zh-cn&SID=2D25AACFB52A6D0F39E4A639B4046C22; ENSEARCH=BENVER=0',
            'referer': 'https://cn.bing.com/images/search?view=detailV2&ccid=ohfhEthz&id=36EA18FC7916F1AEEF1574AD5735BE371170077C&thid=OIP.ohfhEthzMcqmgZsjjIiWFgAAAA&mediaurl=http%3a%2f%2fimg.app178.com%2ftu%2f201605%2fliawo0lftlo.jpg&exph=597&expw=440&q=%e6%b8%85%e7%ba%af%e5%a6%b9%e5%ad%90%e5%9b%be&simid=608044716297357277&selectedIndex=187&mode=overlay',
            'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'}
        # self.header = {'accept': '*/*',
        #                'accept-encoding': 'gzip, deflate, br',
        #                'accept-language': 'zh-CN,zh;q=0.9',
        #
        #                'referer': 'https://cn.bing.com/images/search?view=detailV2&ccid=ohfhEthz&id=36EA18FC7916F1AEEF1574AD5735BE371170077C&thid=OIP.ohfhEthzMcqmgZsjjIiWFgAAAA&mediaurl=http%3a%2f%2fimg.app178.com%2ftu%2f201605%2fliawo0lftlo.jpg&exph=597&expw=440&q=%e6%b8%85%e7%ba%af%e5%a6%b9%e5%ad%90%e5%9b%be&simid=608044716297357277&selectedIndex=187&mode=overlay',
        #                'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'}
        self.host_url = 'https://cn.bing.com/images/api/custom/search?'

    def start_catch(self):
        offset = 25
        while True:
            jsone = {'q': '清纯妹子图',
                     'count': '25',
                     'offset': f'{offset}',
                     'skey': 'GbIRbWjevUU1ByxWrEtSJc6fM9UK4yDLxx2V7JQf2z8',
                     'safeSearch': 'Strict',
                     'mkt': 'zh-cn',
                     'setLang': 'zh-cn',
                     'IG': 'D0E84834161E4C73896C245BD82D26CF',
                     'IID': 'idpfs',
                     'SFX': '1'}
            url = self.host_url + urlencode(jsone)
            source = requests.get(url, headers=self.header).content.decode()
            content = json.loads(source)
            offset = content['queryContext']['nextOffset']
            img_url = content['value']['contentUrl']
            afix = content['value']['encodingFormat']
            for img, fix in zip(img_url, afix):
                yield img, fix

    def down_pic(self):
        for img, fix in self.start_catch():
            img_con = requests.get(img, headers=self.header).content
            img_md5 = hashlib.md5(data=img_con).hexdigest()
            with open(img_md5 + '.' + fix, 'wb') as f:
                f.write(img_con)


class BingDown(object):
    def __init__(self):
        self.header = {
            'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'}

    def start_catch(self, start, count):
        url = f'https://cn.bing.com/images/async?q=%E6%B8%85%E7%BA%AF%E5%A6%B9%E5%AD%90%E5%9B%BE\
        &first={start}&count={count}&relo=2&relp=11&cw=1841&ch=610&scenario=ImageBasicHover&datsrc=N_I\
        &layout=ColumnBased&mmasync=1&dgState=c*9_y*1215s1047s1164s1099s1160s1112s1111s1102s1189_i*38_w*191\
        &IG=FE023EA00AC642E68FFBD9E44F8A563B&SFX=2&iid=idpfs_1.5675'
        co = requests.get(url, headers=self.header).content.decode()
        ra = html.unescape(co)
        img_list = re.findall('murl":"(.*?)"', ra)
        for img in img_list:
            yield img

    def down(self, s, c):
        for img in self.start_catch(s, c):
            try:
                con=requests.get(url=img,headers=self.header).content
                has = hashlib.md5(con).hexdigest()
                with open(f'./im/{has}.jpg', 'wb') as f:
                    f.write(con)
                print('done.')
            except:
                pass

            # con = random_proxy_request.RandomProxyDown.down(img, headers=self.header, stream=True)
            # totalsize = int(con.headers['Content-Length'])
            # tempsize = 0
            # has = hashlib.md5(con.content).hexdigest()
            # with open(f'./im/{has}.jpg', 'wb') as f:
            #     for te in con.iter_content(chunk_size=499):
            #         if te:
            #             f.write(te)
            #             f.flush()
            #             tempsize += len(te)
            #             progress = int(50 * tempsize / totalsize)
            #             sys.stdout.write(f"\r[{'*' * progress}{' ' * (50 - progress)}] {2 * progress}%")
            #             sys.stdout.flush()
            # print()

    def main(self):
        start = 211
        count = 30
        while True:

            print(f'download from {start} to {start + count}')
            self.down(start, count)
            start += count




handle=BingDown()
handle.main()
print('all done.')

