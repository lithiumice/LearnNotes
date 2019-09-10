import requests
import lxml.html
from html.parser import unescape
import os
import re

# if not os.path.exists('./szs'):
#     os.mkdir('./szs')
os.chdir(r'C:\Users\LITHIUM\IdeaProjects\Resource\szs')
header={'Referer':'https://www.x23qb.com/book/2385/3335790.html','User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'}
url1='https://www.x23qb.com/book/2385/3335790.html'


def validateTitle(title):
    rstr = r"[\/\\\:\*\?\"\<\>\|]"  # '/ \ : * ? " < > |'
    new_title = re.sub(rstr, "_", title)  # 替换为下划线
    return new_title


def detail(url):
    sc=requests.get(url,headers=header).content.decode('gbk')
    sc=unescape(sc)
    selector=lxml.html.fromstring(sc)
    at=selector.xpath('//*[@id="TextContent"]')
    article=at[0].text_content()
    article=article.replace('chap_tp();','')
    article=article.replace('theme();','')
    article=article.replace('chap_bg();','')
    title=selector.xpath('//*[@id="mlfy_main_text"]/h1')[0].text_content()
    title=validateTitle(title)
    next_page = selector.xpath('//*[@id="readbg"]/p/a/@href')[-1]
    flag = True if selector.xpath('//*[@id="readbg"]/p/a/text()')[-1] == '下一页' else False
    return [title,article,'https://www.x23qb.com'+next_page]

def parse(url):
    title,article,next_page=detail(url)
    print(article)
    print(url)
    with open(title+'.txt','w+',encoding='utf-8') as f:
        f.write(article)
    parse(next_page)

parse(url1)

