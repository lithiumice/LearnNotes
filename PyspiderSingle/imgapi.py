import requests
import hmac
import time
import random
import base64
import hashlib
import re


def Img_tencent(filename,filetype):
	appid = '1258572470'
	secret_id = 'AKIDRlwx64VsZ7TegXublvyvunVVDj4Q9iaK'
	secret_key = b'nx0sdFhy9Bg09C6qRtC7rQq7Yv7AYmpk'
	bucket = 'BUCKET'

	expired = time.time() + 2592000
	current = time.time()
	rdm = ''.join(random.choice("0123456789") for i in range(10))

	info = "a=" + appid + "&b=" + bucket + "&k=" + secret_id + "&e=" + str(expired) + "&t=" + str(current) + "&r=" + str(rdm) + "&f="
	info = info.encode("utf-8")

	signindex = hmac.new(secret_key, info, hashlib.sha1).digest()  # HMAC-SHA1加密
	sign = signindex + info
	sign = base64.b64encode(sign)
	url = "http://recognition.image.myqcloud.com/ocr/general"
	headers = {
			'Host': 'recognition.image.myqcloud.com',
	        "Authorization": sign
	           }
	files = {'appid': appid,
	         'bucket': bucket,
	         'image': (f'{filename}', open(f'{filename}', 'rb'), f'image/{filetype}')
	         }
	r = requests.post(url, files=files,headers=headers)
	responseinfo = str(r.content,encoding = 'utf-8')
	r_index = r'"itemstring":"(.*?)"'
	result = re.findall(r_index, responseinfo)
	return result

if __name__ == '__main__':
	s=Img_tencent('test.jpg','jpeg')
	for i in s:
		print(i)