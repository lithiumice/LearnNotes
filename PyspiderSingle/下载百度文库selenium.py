# encoding=utf-8
import re
from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import pymongo, traceback
from html.parser import unescape
from selenium.common.exceptions import ElementNotVisibleException
from selenium.common.exceptions import ElementClickInterceptedException

MONGO_URL = 'localhost'
MONGO_DB = 'baidu'
MONGO_TABLE = 'wenku'
client = pymongo.MongoClient(MONGO_URL)
db = client[MONGO_DB]
col = db[MONGO_TABLE]

chrome_options = webdriver.ChromeOptions()
chrome_options.add_experimental_option('excludeSwitches', ['enable-automation'])
# chrome_options.add_argument('--headless')
prefs = {"profile.managed_default_content_settings.images": 2}
browser = webdriver.Chrome(executable_path=r'D:\data_analysis\chromedriver.exe', chrome_options=chrome_options)
wait = WebDriverWait(browser, 10)



def scroll_by_js():
    page = browser.find_element_by_xpath('//*[@class="moreBtn goBtn"]')
    browser.execute_script("arguments[0].scrollIntoView(false);", page)
    WebDriverWait(browser, 10).until(EC.element_to_be_clickable((By.XPATH, '//*[@class="moreBtn goBtn"]'))).click()


def next_page():
    print('scrolling page...')
    try:
        chan = ActionChains(browser)
        chan.send_keys(Keys.PAGE_DOWN).perform()
    except TimeoutException:
        next_page()


def init():
    test_url = 'https://wenku.baidu.com/view/7de3484f59fb770bf78a6529647d27284a733748.html?from=search'
    browser.get(test_url)


def get_all():
    while True:
        try:
            more_btn = browser.find_element_by_xpath('//*[@class="moreBtn goBtn"]')
            more_btn.click()

        except ElementNotVisibleException:
            break

        except Exception:
            traceback.print_exc()
            scroll_by_js()


def get_content():
    raw_text = wait.until(
        EC.presence_of_element_located((By.CSS_SELECTOR, '.main'))).text

    content = ''
    page_list = browser.find_elements_by_class_name('reader-txt-layer')
    for page in page_list:
        content += (unescape(page.text) + '\n')
    return content, raw_text


def get_title():
    tmp = browser.find_element_by_id('doc-tittle-0')
    title = tmp.text
    return title


def main():
    init()
    get_all()
    title = get_title()
    content, raw = get_content()
    info = {
        'title': title,
        'content': content,
        'raw': raw
    }
    save_to_mongo(info)


def save_to_mongo(result):
    try:
        if db[MONGO_TABLE].insert_one(result):
            print('success')
    except:
        traceback.print_exc()



get_all()
title = get_title()
content, raw = get_content()
info = {
    'title': title,
    'content': content,
    'raw': raw
}
save_to_mongo(info)
