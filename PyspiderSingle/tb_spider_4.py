# encoding=utf-8
import re
from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import pymongo, traceback
from urllib.parse import quote
import time,random
import lxml.html

MONGO_URL = 'localhost'
MONGO_DB = 'taobao'
MONGO_TABLE = 'temp'

KEYWORD = 'book'

SERVICE_ARGS = ['--load-images=false', '--disk-cache=true']
client = pymongo.MongoClient(MONGO_URL)
db = client[MONGO_DB]
# browser = webdriver.PhantomJS(service_args=SERVICE_ARGS)
# browser = webdriver.Chrome()
browser=webdriver.Firefox()
wait = WebDriverWait(browser, 10)
# browser.set_window_size(1400, 900)

search_url = 'https://uland.taobao.com/sem/tbsearch?keyword={}&page={}'


def search():
    print('searching...')
    try:
        browser.get(search_url.format(quote(KEYWORD), 0))
        total = wait.until(
            EC.presence_of_element_located((By.CSS_SELECTOR, '.totalPage')))
        get_products()
        return total.text
    except TimeoutException:
        return search()


def next_page(page_number):
    print('scrolling page...', page_number)
    try:
        get_products()
        url = search_url.format(quote(KEYWORD), page_number)
        browser.get(url)
    except TimeoutException:
        next_page(page_number)


def get_products():
    wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, '#searchResult>div>div.item')))
    html = browser.page_source
    sel = lxml.html.fromstring(html)
    items = sel.xpath('//div[@id="searchResult"]/div/div/a')
    for item in items:
        product = {
            'image': item.xpath('div[1]/span/img/@src'),
            'price': item.xpath('div/p/span[@class="pricedetail"]')[0].text_content().replace('\xa5', '').replace(
                '\xa0', ''),
            'shop&deal': item.xpath('div/p[@class="shopName"]')[0].text_content().replace('\xa5', '').replace('\xa0',
                                                                                                              ''),
            'title': item.xpath('div/span[@class="title"]/@title')[0].replace('\xa5', '').replace('\xa0', ''),
            'dsr_info': item.xpath('div/div/div[@class="dsr-info"]')[0].text_content().replace('\xa5', '').replace(
                '\xa0', '')

        }
        save_to_mongo(product)


def save_to_mongo(result):
    try:
        if db[MONGO_TABLE].insert_one(result):
            print('success', result)
    except:
        print('fail', result)


def on_broke_to_search(page, total):
    print('broke searching...', page)
    try:
        url = search_url.format(quote(KEYWORD), page)
        browser.get(url)
        get_products()

        for i in range(2, total + 1):
            next_page(i)
            time.sleep(1)

    except TimeoutException:
        next_page(page)


if __name__ == '__main__':
    try:
        total = search()
        total = int(re.search('(\d+)', total).group(1))
        for i in range(2, total + 1):
            next_page(i)
    except:
        traceback.print_exc()
    finally:
        browser.close()
