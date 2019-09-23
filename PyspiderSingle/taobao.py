import requests
import re
import time
import json
import xlwt

url = 'https://s.taobao.com/search?q=python&imgfile=&js=1&stats_click=search_radio_all%3A1&initiative_id=staobaoz_20180430&ie=utf8'
response = requests.get(url)
html = response.text
content = re.findall(r'g_page_config = (.*?) g_srp_loadCss',html,re.S)[0].strip()[:-1]
content = json.loads(content)
data_list = content['mods']['itemlist']['data']['auctions']
DATA=[]
for item in data_list:
    temp = {
        'title': item['title'],
        'view_price': item['view_price'],
        'view_sales': item['view_sales'],
        'view_fee': '否' if float(item['view_fee']) else '是',
        'isTmall': '是' if item['shopcard']['isTmall'] else '否',
        'area': item['item_loc'],
        'name': item['nick'],
        'detail_url': item['detail_url'],
    }
    DATA.append(temp)
cookies = response.cookies
url2 = 'https://s.taobao.com/api?_ksTS=1524836494360_224&callback=jsonp225&ajax=true&m=customized&sourceId=tb.index&q=python&spm=a21bo.2017.201856-taobao-item.1&s=36&imgfile=&initiative_id=tbindexz_20170306&bcoffset=-1&commend=all&ie=utf8&rn=efedc6cda629c8a38008aff6f017b934&ssid=s5-e&search_type=item'

response2 = requests.get(url2, cookies=cookies)
html2 = response2.text

content = re.findall(r'{.*}', html2)[0]
content = json.loads(content)
data_list = content['API.CustomizedApi']['itemlist']['auctions']
for item in data_list:
    temp = {
        'title':item['title'],
        'view_price':item['view_price'],
        'view_sales':item['view_sales'],
        'view_fee': '否' if float(item['view_fee'])else '是',
        'isTmall':'是'  if item['shopcard']['isTmall'] else '否',
        'area': item['item_loc'],
        'name':item['nick'],
        'detail_url':item['detail_url'],
    }
    DATA.append(temp)

url = 'https://s.taobao.com/search?data-key=s&data-value=44&ajax=true&_ksTS=1525143958908_907&callback=jsonp908&q=python&imgfile=&commend=all&ssid=s5-e&search_type=item&sourceId=tb.index&spm=a21bo.2017.201856-taobao-item.1&ie=utf8&initiative_id=tbindexz_20170306&bcoffset=3&ntoffset=0&p4ppushleft=1%2C48'
cookies = response2.cookies

for i in range(1, 10):
    ktsts = time.time()
    _ksTS = '%s_%s' % (int(ktsts * 1000), str(ktsts)[-3:])
    callback = "jsonp%s" % (int(str(ktsts)[-3:]) + 1)
    data_value = 44 * i
    url = 'https://s.taobao.com/search?data-key=s&data-value={}&ajax=true&_ksTS={}&callback={}&q=python&imgfile=&commend=all&ssid=s5-e&search_type=item&sourceId=tb.index&spm=a21bo.2017.201856-taobao-item.1&ie=utf8&initiative_id=tbindexz_20170306&bcoffset=0&ntoffset=6&p4ppushleft=1%2C48&s=44'.format(
        data_value, _ksTS, callback)

f = xlwt.Workbook(encoding='utf-8')
sheet01 = f.add_sheet(u'sheet1', cell_overwrite_ok=True)

sheet01.write(0, 0, '标题')
sheet01.write(0, 2, '标价')
sheet01.write(0, 3, '是否包邮')
sheet01.write(0, 4, '是否天猫')
sheet01.write(0, 5, '地名')
sheet01.write(0, 6, '店名')
sheet01.write(0, 7, 'url')

for i in range(len(DATA)):
    sheet01.write(i + 1, 0, DATA[i]['title'])
    sheet01.write(i + 1, 1, DATA[i]['view_price'])
    sheet01.write(i + 1, 2, DATA[i]['view_sales'])
    sheet01.write(i + 1, 3, DATA[i]['view_fee'])
    sheet01.write(i + 1, 4, DATA[i]['isTmall'])
    sheet01.write(i + 1, 5, DATA[i]['area'])
    sheet01.write(i + 1, 6, DATA[i]['name'])
    sheet01.write(i + 1, 7, DATA[i]['detail_url'])
    f.save(u'搜索python的结果.xls')
