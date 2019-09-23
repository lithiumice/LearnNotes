import requests
import pymongo


class RandomProxyDown(object):
    def __init__(self, db, col):
        client = pymongo.MongoClient()
        self.post = client[db][col]

    def down(self, url, headers, retry_num=5):
        while retry_num:
            ip, port = post.find_one({}, {'ip': 1, 'port': 1, '_id': 0})
            proxy = ip + ':' + port
            try:
                request = requests.get(url, headers=headers, proxies=proxy)
                return request
            except:
                self.post.delete_one({'ip': ip if ip else 'null'})
                retry_num -= 1
        return -1
