# encoding=utf-8
import re
from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import pymongo, traceback
from urllib.parse import quote
import lxml.html
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.keys import Keys
from lxml.html.html5parser import html_parser

MONGO_URL = 'localhost'
MONGO_DB = 'zhihu'
MONGO_TABLE = 'hot_50'

cookies = [{'name': 'tgw_l7_route',
            'value': '7c109f36fa4ce25acb5a9cf43b0b6415',
            'path': '/',
            'domain': 'www.zhihu.com',
            'secure': False,
            'httpOnly': False,
            'expiry': 1552104578},
           {'name': '_zap',
            'value': '7806a1ec-85f1-4743-94fd-3e34e13bbfec',
            'path': '/',
            'domain': '.zhihu.com',
            'secure': False,
            'httpOnly': False,
            'expiry': 1615175678},
           {'name': '_xsrf',
            'value': 'ZMwT4sWZH8Xxby9ujno7oy4Fh1G8KFeP',
            'path': '/',
            'domain': '.zhihu.com',
            'secure': False,
            'httpOnly': False,
            'expiry': 1629863678},
           {'name': 'd_c0',
            'value': '"AJBjLVU5GA-PTpUAwdONx9gls-eaRKewj3E=|1552103679"',
            'path': '/',
            'domain': '.zhihu.com',
            'secure': False,
            'httpOnly': False,
            'expiry': 1646711679},
           {'name': 'capsion_ticket',
            'value': '"2|1:0|10:1552104263|14:capsion_ticket|44:YWQ4YTQzMjMyZGJjNDU3MWFlOGNmNzhhYjk2Y2E3MjU=|81367f4acb27bd50604f7942a61ff8eb5233a2756c2832fa200a2bb46ae45d35"',
            'path': '/',
            'domain': '.zhihu.com',
            'secure': False,
            'httpOnly': True,
            'expiry': 1554696263},
           {'name': 'z_c0',
            'value': '"2|1:0|10:1552104445|4:z_c0|92:Mi4xS2lBNkF3QUFBQUFBa0dNdFZUa1lEeWNBQUFDRUFsVk5fY2lxWEFCbTdDZjltUGxNazBnZ2ZGX0RfUGJtN0ZtbFNR|9dc9d375bafa9be7dbdafadfe2eefcbde28cacb746bdd0ac4a3933ca755db343"',
            'path': '/',
            'domain': '.zhihu.com',
            'secure': False,
            'httpOnly': True,
            'expiry': 1554696445},
           {'name': 'tst',
            'value': 'r',
            'path': '/',
            'domain': '.zhihu.com',
            'secure': False,
            'httpOnly': False,
            'expiry': 1554696447},
           {'name': 'q_c1',
            'value': '8c17b426a81b43d483675b8c90a7a011|1552104446000|1552104446000',
            'path': '/',
            'domain': '.zhihu.com',
            'secure': False,
            'httpOnly': False,
            'expiry': 1646712446}]

client = pymongo.MongoClient(MONGO_URL)
db = client[MONGO_DB]
browser = webdriver.Firefox(executable_path=r'D:\data_analysis\geckodriver.exe')
wait = WebDriverWait(browser, 10)

username = '18877520951'
passwd = '135hualin'


def add_cookies():
    for i in cookies:
        browser.add_cookie(i)
add_cookies()

def islogin():
    browser.get('https://www.zhihu.com')
    login_but = browser.find_element_by_css_selector('.SignContainer-switch>span')
    if login_but:
        return False
    else:
        return True


def login():
    browser.get('https://www.zhihu.com')
    login_but = browser.find_element_by_css_selector('.SignContainer-switch>span')

    login_but.click()
    browser.find_element_by_name('username').send_keys(username)
    browser.find_element_by_name('password').send_keys(passwd)
    browser.find_element_by_xpath('//button[@type="submit"]').click()
    ActionChains(browser).send_keys(Keys.ENTER)
    return True


def get_question(url):
    browser.get(url)
    list_items = browser.find_elements_by_xpath('//div[@class="List-item"]')
    for item in list_items:
        try:
            user_info = item.find_element_by_css_selector('[class="ContentItem AnswerItem"]').get_attribute('data-zop')
            voters = item.find_element_by_css_selector('.Voters>button').text
            article_content = item.find_element_by_class_name('RichContent-inner').text
            info = {
                'user_info': user_info,
                'voters': voters,
                'article': article_content,
                'vote_up': item.find_element_by_xpath('//*[@class="Button VoteButton VoteButton--up"]').text,
                'comments':item.find_element_by_xpath('//*[@class="Button ContentItem-action Button--plain Button--withIcon Button--withLabel"]').text
            }
            save_to_mongodb(info,'que_answer')
        except:
            traceback.print_exc()
            continue


def get_que_from_hot():
    try:
        li = db[MONGO_TABLE].find({})
        urls = [i['que_url'] for i in li]
        urls=list(set(urls))
        for i in urls:
            get_question(i)
    except Exception:
        print('fail:', str(Exception.args))


def get_hot():
    hot_url = 'https://www.zhihu.com/hot'
    print('searching...')
    try:
        browser.get(hot_url)
        wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, '.HotItem')))
        total_list = browser.find_elements_by_class_name('HotItem')
        rank = 0
        for item in total_list:
            try:

                rank = item.find_element_by_class_name('HotItem-rank').text
                title = item.find_element_by_css_selector('.HotItem-title').text
                try:
                    detail = item.find_element_by_xpath('div/a/p').text
                except:
                    detail = ''

                que_url = item.find_element_by_xpath('div/a').get_attribute('href')
                try:
                    hot_num = item.find_element_by_xpath('div/div[@class="HotItem-metrics HotItem-metrics--bottom"]').text
                except:
                    hot_num = item.find_element_by_xpath('div/div[@class="HotItem-metrics"]').text

                info = {'rank': rank,
                        'title': title,
                        'detail': detail,
                        'hot_num': hot_num,
                        'que_url': que_url
                        }
                save_to_mongodb(info)
            except:
                traceback.print_exc()
                continue
        if rank == '50':
            return
        else:
            next_page()
    except TimeoutException:
        traceback.print_exc()
        return get_hot()


def next_page():
    print('scrolling page...')
    try:
        chan = ActionChains(browser)
        chan.send_keys(Keys.PAGE_DOWN)
        get_hot()
    except TimeoutException:
        next_page()


def save_to_mongodb(result,table=MONGO_TABLE):
    try:
        if db[table].insert_one(result):
            print('success', result)
    except Exception:
        print('fail', str(Exception))


if __name__ == '__main__':
    try:
        get_hot()
    except:
        traceback.print_exc()
    finally:
        browser.close()
