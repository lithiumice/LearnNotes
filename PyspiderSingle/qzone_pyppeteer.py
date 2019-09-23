import time
import re
import pyppeteer
import asyncio
from pyppeteer import launch
import pymongo, traceback
from html.parser import unescape

global browser
global page


async def init():
    my_url = 'https://user.qzone.qq.com/2729020028'

    browser = await launch(headless=False)
    page=await browser.newPage()
    await page.setViewport(viewport={'width':1280,'height':800})
    await page.setJavaScriptEnabled(enabled=True)
    await page.goto(my_url)

    print(await page.cookies())
    print(await page.content())
    print(await page.title())
    print(await page.evaluate('''hello world'''))

def run(fuc):
    asyncio.get_event_loop().run_until_complete(fuc)

async def scroll_by_js():
    global page
    page.evalute(""" 
                if (document.body.scrollHeight-window.scrollY > 100) { 
                    window.scroll(0, window.scrollY+window.screen.height); 
                }
                else { 
                    document.title = "done"; 
                } 
            """)


async def is_end():
    browser.execute_script('''$(window).scroll(function () {
          if ($(window).scrollTop() == $(document).height() - $(window).height()) {
                 true
           }else{ false}
     }) ''')


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



qq_list=[]


def is_overlay():
    over=browser.find_elements_by_xpath('//*[contains(@id,"guide-overlay")]')
    return True

def is_loading():
    browser.find_element_by_css_selector('b-inline.data_is_loading.none')
    browser.find_element_by_xpath('//*[@id="ICFeedsTipMsg"]')

while True:
    browser.implicitly_wait(10)
    try:
        no_more=browser.find_element_by_css_selector('b-inline.data_no_more')
        if no_more:
            print('the end')
            break
    except:
        continue
