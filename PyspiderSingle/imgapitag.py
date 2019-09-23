import requests
import hmac
import time
import random
import base64
import hashlib
import json


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
	signindex = hmac.new(secret_key, info, hashlib.sha1).digest()
	sign = signindex + info
	sign = base64.b64encode(sign)

	url = "https://recognition.image.myqcloud.com/v1/detection/imagetag_detect"
	headers = {
			'Host': 'recognition.image.myqcloud.com',
			'content-type':'multipart/form-data',
	        "authorization": sign,
	           }
	files = {'appid': appid,
	         'bucket': bucket,
	         'image': (f'{filename}', open(f'{filename}', 'rb'), f'image/{filetype}')
	         }
	r = requests.post(url, files=files,headers=headers)
	responseinfo = str(r.content,encoding = 'utf-8')
	print(responseinfo)
	img_json=json.loads(responseinfo)
	print(img_json)
	if img_json['code'] is not 0:
		return None
	list=[]
	for each in img_json['tags']:
		list.append(each['tag_name'])
	print(list)
	return list

if __name__ == '__main__':
	s=Img_tencent('test.jpg','jpg')
	for i in s:
		print(i)