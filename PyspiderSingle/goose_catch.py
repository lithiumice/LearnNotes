import json
import requests
import sys

reload(sys)
sys.setdefaultencoding('utf-8')


def seek_goose(page_num=0, filename='goose'):
    HEADER = {
        'appVersion': '1.2.4',
        'signature': 'df0a8a2284f338c1ad7dcba87b946029',
        'channel': 'qq',
        'signId': '8im84hwudGI=',
        'version': '1.2',
        'deviceId': '869402036996450',
        'nonce': '34109',
        'platform': 'ANDROID',
        'osVersion': '8.1.0',
        'id': '111892',
        'device': 'vivo_vivo Z1',
        'timestamp': '1547824199991',
        'User-Agent': 'Dalvik/2.1.0 (Linux; U; Android 8.1.0; vivo Z1 Build/OPM1.171019.011)',
        'Host': 'goosetalk.com',
        'Accept-Encoding': 'gzip',
        'Connection': 'keep-alive',

    }
    url = 'http://goosetalk.com/api/card/view?id=136' + str(page_num) + '&'
    goose_source = requests.get(url, headers=HEADER).content.decode()
    goose_view = json.loads(goose_source)
    print(goose_view)
    content_main = goose_view['resData']

    f = open('{}.txt'.format(filename), 'a')
    f.write(content_main['summary'])
    content_text = content_main['words']
    for text in content_text:
        f.write('({}):'.format(text['title'].encode()) + text['content'].encode() + '\n')
    opinions = content_main['opinions']
    for comment in opinions:
        f.write('{}:'.format(comment['user']['nickname'].encode()) + comment['content'].encode() + '\n')
    f.close()


for i in range(0, 100):
    try:
        seek_goose(i, 'goose_%.2g' % i)
    except Exception:
        pass
