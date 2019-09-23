from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.common.action_chains import ActionChains
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import pymongo, traceback, re
from html.parser import unescape
from selenium.common.exceptions import ElementNotVisibleException
from selenium.common.exceptions import ElementClickInterceptedException


# chrome_options = webdriver.ChromeOptions()
# chrome_options.add_experimental_option('excludeSwitches', ['enable-automation'])
# prefs = {"profile.managed_default_content_settings.images": 2}
browser = webdriver.Chrome()
wait = WebDriverWait(browser, 10)

html=browser.get('https://news.163.com/19/0913/17/EOVI3NAQ0001899O.html').page_source
with open("163.html","w") as f:
    f.write(html)
