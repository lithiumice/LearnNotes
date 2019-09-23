from selenium import webdriver
import time
import json
from bs4 import BeautifulSoup
import lxml.html
from lxml import etree
import sys

reload(sys)
sys.setdefaultencoding('utf-8')
profile = webdriver.FirefoxProfile(r'C:\Users\LITHIUM\AppData\Roaming\Mozilla\Firefox\Profiles\lithium.seleniumTest')
driver = webdriver.Firefox(profile, executable_path='geckodriver.exe')
driver.get('https://category.vip.com/')
time.sleep(2)
next_num = 0
while True:
    for i in range(1, 6):
        temp_height = 20000 * i
        temp_str = "window.scrollBy(0," + str(temp_height) + ")"
        driver.execute_script(temp_str)
        time.sleep(3)
        soup = BeautifulSoup(driver.page_source, 'lxml')
        content_ol = soup.find_all(class_='c-category-goods-link')
        with open('QQ_word.txt', 'a') as f:
            for ol in content_ol:
                # qq_content=ol.xpath('./div[2]/pre/text()')
                # qq_content=qq_content[0] if len(qq_content)>0 else ''
                # qq_name=ol.xpath('./div[4]/div[1]/span/a/text()')
                # qq_name=qq_name[0] if len(qq_name)>0 else ''
                text = ol.string
                f.write(text)
        next_num += 1
driver.quit()
