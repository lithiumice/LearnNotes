import requests
import pymongo
import random


class ProxyDown(object):
    def __init__(self, db, col):
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
        client = pymongo.MongoClient()
        self.post = client[db][col]

    def get(self, url, timeout, proxy=None, num_retries=6):
        UA = random.choice(self.user_agent_list)
        headers = {'User-Agent': UA}
        if proxy == None:
            try:
                return requests.get(url, headers=headers, timeout=timeout)
            except:
                if num_retries > 0:
                    print(u'获取网页出错，将获取倒数第：', num_retries, u'次')
                    return self.get(url, timeout, num_retries - 1)
                else:
                    print(u'开始使用代理')
                    IP = ''.join(str(random.choice(self.iplist)).strip())
                    proxy = {'http': IP}
                    return self.get(url, timeout, proxy, )
        else:
            try:
                IP = ''.join(
                    str(random.choice(self.iplist)).strip())
                proxy = {'http': IP}
                return requests.get(url, headers=headers, proxies=proxy, timeout=timeout)
            except:

                if num_retries > 0:
                    IP = ''.join(str(random.choice(self.iplist)).strip())
                    proxy = {'http': IP}
                    print(u'正在更换代理，10S后将重新获取倒数第', num_retries, u'次')
                    print(u'当前代理是：', proxy)
                    return self.get(url, timeout, proxy, num_retries - 1)
                else:
                    print(u'代理也不好使了！取消代理')
                    return self.get(url, 3)

    def down(self, url, headers=None, retry_num=7):
        if retry_num > 0:
            temp = self.post.find_one({}, {'ip': 1, 'port': 1, 'protol': 1, '_id': 0})
            ip = temp['ip']
            port = temp['port']
            protol = temp['protol'].lower()
            proxy = ip + ':' + port
            if headers is None:
                UA = random.choice(self.user_agent_list)
                headers = {'User-Agent': UA}
            try:
                con = requests.get(url, headers=headers, proxies={protol: proxy}, timeout=5).content
                return con

            except Exception as e:
                print(e.args)
                self.post.delete_one({'ip': ip if ip else 'null'})
                self.down(url=url, retry_num=retry_num - 1)


request = ProxyDown('spider', 'ip2')
