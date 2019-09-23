import requests
import json

header={
'origin': 'https://cn.bing.com',
'referer': 'https://cn.bing.com/translator/',
'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'
}
detect_url = 'https://cn.bing.com/tdetect?&IG=C2CADB8C8D8B426A9CEC70A1F4D559D0&IID=translator.5038.1'
cat_url='https://cn.bing.com/ttranslate?&category=&IG=C2CADB8C8D8B426A9CEC70A1F4D559D0&IID=translator.5038.11'
url = 'https://cn.bing.com/ttranslationlookup?&IG=C2CADB8C8D8B426A9CEC70A1F4D559D0&IID=translator.5038.1'
text = input('text(auto detect):')
to_l = input('to what:')
from_l = requests.post(detect_url,data={'text': text},headers=header).content.decode()
data = {'text': text,
        'from': from_l,
        'to': to_l }
if text.count(' ') >= 1:
        answer = requests.post(cat_url, data=data,headers=header).content.decode()
        answer = json.loads(answer)
        out_text = answer['translationResponse']
        print(out_text)
else:
        answer = requests.post(url, data=data, headers=header).content.decode()
        answer = json.loads(answer)
        out_text = answer['translations'][0]['displayTarget']
        print(out_text)
