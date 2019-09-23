import re
import requests
import lxml.html
import hashlib


host_url = 'https://3dhentai.club/page/{}/'
header = {'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'}

def down_all_page():
    for i in range(25):
        url = host_url.format(i)
        main_page = requests.get(url, headers=header).content.decode()
        detail_url = lxml.html.fromstring(main_page).xpath('//*[@id="main"]')[0].xpath('div/article/a/@href')
        for url in detail_url:
            print(url)
            parse_detail(url)

def parse_detail( url):
    detail_page = requests.get(url, headers=header).content.decode()
    # 'https://3dhentai.club/video/samus-bent-over-and-fucked-metroid-rule34/'
    # selector=lxml.html.fromstring(detail_page)
    video_url = re.search(r'<source src="(.*?)" type="video/', detail_page).group(1)
    print(video_url)
    downloader(video_url)

def downloader( url):
    video = requests.get(url, headers=header).content
    name = hashlib.md5(video).hexdigest()
    with open(name+'.jpg', 'wb') as f:
        f.write(video)
        print('done.')

hand=hentai()
hand.down_all_page()