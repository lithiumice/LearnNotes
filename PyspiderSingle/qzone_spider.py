import time
import re
import lxml.html
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import pymongo, traceback
from html.parser import unescape
from selenium.common.exceptions import ElementNotVisibleException

cook = [{'name': 'zzpaneluin',
         'value': '',
         'path': '/',
         'domain': '.qzone.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'zzpanelkey',
         'value': '',
         'path': '/',
         'domain': '.qzone.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'pgv_pvi',
         'value': '466124800',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False,
         'expiry': 2147385600},
        {'name': 'pgv_si',
         'value': 's1212299264',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'pgv_pvid',
         'value': '7007334810',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False,
         'expiry': 2147385600},
        {'name': 'pgv_info',
         'value': 'ssid=s7046027100',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'uin',
         'value': 'o2729020028',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'skey',
         'value': '@HoCibf9hX',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'ptisp',
         'value': 'cnc',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'RK',
         'value': 'STC0dG6s++',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False,
         'expiry': 2147483647},
        {'name': 'show_id',
         'value': '6765616b637240686f746d61696c2e636f6d',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'ptcz',
         'value': 'db43f3e9e696f489de8fe2dba5cb2d893f028dd4b0e82669b36883357841a12f',
         'path': '/',
         'domain': '.qq.com',
         'secure': False,
         'httpOnly': False,
         'expiry': 2147483647},
        {'name': 'p_uin',
         'value': 'o2729020028',
         'path': '/',
         'domain': '.qzone.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'pt4_token',
         'value': 'zashGiBoiurHXMuHzDm8wH6sQlogdqegvqQW5NOZK6w_',
         'path': '/',
         'domain': '.qzone.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'p_skey',
         'value': '9OtnrZhW1WGhuAhfgcMSUN15D-lhtM9CwlJWFDm0O78_',
         'path': '/',
         'domain': '.qzone.qq.com',
         'secure': True,
         'httpOnly': False},
        {'name': 'Loading',
         'value': 'Yes',
         'path': '/',
         'domain': '.qzone.qq.com',
         'secure': False,
         'httpOnly': False,
         'expiry': 1552406400},
        {'name': 'qz_screen',
         'value': '1920x1080',
         'path': '/',
         'domain': '.user.qzone.qq.com',
         'secure': False,
         'httpOnly': False,
         'expiry': 1554987925},
        {'name': '2729020028_todaycount',
         'value': '0',
         'path': '/',
         'domain': 'user.qzone.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': '2729020028_totalcount',
         'value': '458',
         'path': '/',
         'domain': 'user.qzone.qq.com',
         'secure': False,
         'httpOnly': False},
        {'name': 'QZ_FE_WEBP_SUPPORT',
         'value': '0',
         'path': '/',
         'domain': '.qzone.qq.com',
         'secure': False,
         'httpOnly': False,
         'expiry': 1867755930}]
global browser
my_url = 'https://user.qzone.qq.com/2729020028'


def page_to_element(page):
    sel = lxml.html.fromstring(page.page_source)
    return sel


def init():
    browser = webdriver.Firefox()
    browser.get(my_url)
    browser.implicitly_wait(10)


def find_qq_num(page_source):
    qlist_part=re.findall('nameCard_(\d{8,})',page_source)
    return qlist_part


def scroll_by_js():
    browser.execute_script(""" 
                if (document.body.scrollHeight-window.scrollY > 100) { 
                    window.scroll(0, window.scrollY+window.screen.height); 
                }
                else { 
                    document.title = "done"; 
                } 
            """)


def scroll_by_less(browser):
    browser.execute_script(""" 
            if (document.body.scrollHeight-window.scrollY > 1000
            ) { 
                window.scroll(0, window.scrollY+window.screen.height); 
            }
            else { 
                document.title = "done"; 
            } 
        """)


def scroll_to_end():
    chan = ActionChains(browser)
    chan.send_keys(Keys.END).perform()


def scroll_to_home():
    chan = ActionChains(browser)
    chan.send_keys(Keys.HOME).perform()


qq_list = []


def is_overlay():
    over = browser.find_elements_by_xpath('//*[contains(@id,"guide-overlay")]')
    return True


def is_loading():
    browser.find_element_by_css_selector('b-inline.data_is_loading.none')
    browser.find_element_by_xpath('//*[@id="ICFeedsTipMsg"]')


while True:
    scroll_to_end()
    browser.implicitly_wait(10)
    try:
        no_more = browser.find_element_by_css_selector('b-inline.data_no_more')
        if no_more:
            print('the end')
            break
    except:
        continue
