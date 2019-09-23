import re
import requests
import lxml.html
import hashlib


class hentai(object):
    host_url = 'https://3dhentai.club/page/{}/'
    header = {
        'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'}

    def down_all_page(self):
        for i in range(25):
            url = self.host_url.format(i)
            main_page = requests.get(url, headers=self.header).content.decode()
            detail_url = lxml.html.fromstring(main_page).xpath('//*[@id="main"]')[0].xpath('div/article/a/@href')
            for url in detail_url:
                print(url)
                self.parse_detail(url)

    def parse_detail(self, url):
        detail_page = requests.get(url, headers=self.header).content.decode()
        # 'https://3dhentai.club/video/samus-bent-over-and-fucked-metroid-rule34/'
        # selector=lxml.html.fromstring(detail_page)
        video_url = re.search(r'<source src="(.*?)" type="video/', detail_page).group(1)
        print(video_url)
        self.downloader(video_url)

    def downloader(self, url):
        video = requests.get(url, headers=self.header).content
        name = hashlib.md5(video)
        with open(name, 'wb') as f:
            f.write(video)
            print('done.')

hand=hentai()
hand.down_all_page()