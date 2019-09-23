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

# options = webdriver.FirefoxOptions()
# options.add_argument('excludeSwitches', ['enable-automation'])
# chrome_options.add_argument('--headless')
# prefs = {"profile.managed_default_content_settings.images": 2}
browser = webdriver.Firefox()
wait = WebDriverWait(browser, 10)
# browser.maximize_window()


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


def show_all():
    while True:
        try:
            more_btn = browser.find_element_by_xpath('//*[@class="moreBtn goBtn"]')
            more_btn.click()
            break

        except ElementNotVisibleException:
            break

        except Exception:
            next_page()


def init(url='https://wenku.baidu.com/view/7c13233a80eb6294dd886cef.html?rec_flag=default&sxts=1552279542167'):

    browser.get(url)
    browser.execute_script('document.title="crawling"')
    chan = ActionChains(browser)
    chan.send_keys(Keys.CONTROL, Keys.DIVIDE).perform()


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


def scroll_to_end():
    chan = ActionChains(browser)
    chan.send_keys(Keys.END).perform()


def scroll_to_home():
    chan = ActionChains(browser)
    chan.send_keys(Keys.HOME).perform()


def is_end():
    browser.execute_script('''$(window).scroll(function () {
          if ($(window).scrollTop() == $(document).height() - $(window).height()) {
                 return true
           }else{return false}
     }) ''')


def scroll_by_little(browser):
    browser.execute_script(""" 
            var y = window.screenY; 
            var step = 1600;  
            if (y < document.body.scrollHeight) { 
                y += step; 
                window.scroll(0, y); 
            }
            else { 
                window.scroll(0, y); 
                document.title += "scroll-done"; 
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


def get_article():
    contents = ''
    set_list = []

    while True:
        content = ''
        _ = browser.title
        print(set_list)
        if 'done' not in _:
            scroll_by_less(browser)
            pages = []
            page_list = browser.find_elements_by_xpath('//div[contains(@id,"pageNo")]')
            for i in page_list:
                if i.get_attribute('id') not in set_list:
                    set_list.append(i.get_attribute('id'))
                    pages.append(i)
            if not pages:
                continue
            for page in pages:
                content += (unescape(page.text) + '\n')
            content = content.splitlines()
            content = ''.join(content)
            print(content)
            contents += re.sub(r'\n\t\f\r', '', content)
        else:
            break
    return contents


def get_text():
    contents = ''
    page_list = browser.find_elements_by_xpath('//div[contains(@id,"pageNo")]')
    done_list = []
    while True:
        if 'done' not in browser.title:
            scroll_by_less(browser)
            do_list = []
            for i in page_list:
                if i not in done_list:
                    do_list.append(i)

            for page in do_list:
                try:
                    text = page.text
                    if text == '':
                        raise Exception

                    print('crawling ',page.get_attribute('id'))
                    content = (unescape(text) + '\n')
                    content = content.splitlines()
                    content = ''.join(content)
                    print(content)

                    contents += re.sub(r'\n\t\f\r', '', content)
                    done_list.append(page)
                except:
                    break

        else:
            break
    return contents


def get_content():
    content = ''
    page_list = browser.find_elements_by_xpath('//div[contains(@id,"pageNo")]')
    for page in page_list:
        content += (unescape(page.text) + '\n')
        print(page.text)
    content = content.splitlines()
    content = ''.join(content)
    content = re.sub(r'\n\t\f\r', content)
    return content


def get_title():
    tmp = browser.find_element_by_xpath('//*[contains(@id,"doc-tittle")]')
    title = tmp.text
    return title


def remove_chinese(string):
    text = re.sub(r'[^\x00-\xff]', '', string)
    text = re.sub(r'\W{2,}', ',', text)
    return text


def main():
    init()
    get_all()
    title = get_title()
    content = get_content()
    info = {
        'title': title,
        'content': content
    }
    save_to_mongo(info)


def save_to_mongo(result):
    try:
        if col.insert_one(result):
            print('saved success with result', result)
    except:
        traceback.print_exc()


init()
show_all()
scroll_to_end()
scroll_to_home()
title = get_title()
content = get_text()
info = {
    'title': title,
    'english': remove_chinese(content),
    'content': content,
}
save_to_mongo(info)
browser.close()
