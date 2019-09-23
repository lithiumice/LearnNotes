import requests
import csv

header = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'}

url = 'http://hitokoto.jijidown.com/v2/api/hitokoto?count=1000'

ret = requests.get(url, headers=header).json()
rer = ret['res']

with open('quote_anim.csv', 'w', encoding='utf-8') as f:
    fp = csv.DictWriter(f, fieldnames=['source', 'quote'])
    fp.writeheader()
    for i in rer:
        fp.writerow({'source': i['source'], 'quote': i['hitokoto']})
