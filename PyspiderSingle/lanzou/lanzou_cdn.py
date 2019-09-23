import requests
import re
import json
from ToolFuc.tools import ChromeHeaders2Dict

# login_url = 'https://pc.woozooo.com/account.php'
# login_data = {
#     'action': 'login',
#     'task': 'login',
#     'ref': '/mydisk.php',
#     'formhash': 'eba360ff',
#     'username': '18623452248',
#     'password': '135hualin'
# }
# ua_header = {
#     'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'}
# raw_header = {
#     'origin': 'https://pc.woozooo.com',
#     'referer': 'https://pc.woozooo.com/account.php?action=login&ref=/mydisk.php',
#     'upgrade-insecure-requests': '1',
#     'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36'
# }
#
# login_response = requests.post(login_url, data=login_data, headers=raw_header)
# login_cookies = login_response.headers['Set-Cookie']
# login_header = {
#     'accept': 'application/json, text/javascript, */*; q=0.01',
#     'accept-encoding': 'gzip, deflate, br',
#     'accept-language': 'zh-CN,zh;q=0.9',
#     'content-type': 'application/x-www-form-urlencoded; charset=UTF-8',
#     'cookie': login_cookies,
#     'origin': 'https://pc.woozooo.com',
#     'referer': 'https://pc.woozooo.com/mydisk.php?item=files&action=index&u=18623452248',
#     'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) snap Chromium/71.0.3578.98 Chrome/71.0.3578.98 Safari/537.36',
#     'x-requested-with': 'XMLHttpRequest'
# }
# request_url = 'https://pc.woozooo.com/doupload.php'
#
# file_list_page = 1
# post_data = {
#     'task': '5',
#     'folder_id': '-1',
#     'pg': file_list_page
# }
# file_list = requests.post(request_url, data=post_data, headers=login_header).content.decode()
# file_id_list = re.findall('"id":"(.*?)"', file_list)

post_file_url = 'https://pc.woozooo.com/fileup.php'
post_cookies = {
    'UM_distinctid': '167c148f761119-0cc301b871f4a8-76123f4b-144000-167c148f76221f',
    'PHPSESSID': 'bj9saraupquc6nesfrci3gn5eaceth9f',
    'phpdisk_info': 'BzRfZVI3UGoEMgBiCllWOAFYUWJdPAJjVGVSMQEzCj1RZ15uUTcANFNYAjEIZFdvB2QDNws2AmADNQZgVzNQZQc7X29SN1BrBGAAYgpgVmgBY1FjXWYCbFRvUjMBNwppUWJeOlE2ADtTYwJbCGNXNQdhAzMLYQJhAzUGZFdjUGYHOw%3D%3D',
    'ylogin': '787642',
    'CNZZDATA1253610886': '371681567-1545134562-https%253A%252F%252Fpc.woozooo.com%252F%7C1553670951'
}
post_file_header = {'accept': '*/*',
                    'accept-encoding': 'gzip, deflate, br',
                    'accept-language': 'zh-CN,zh;q=0.9',
                    'content-length': '12320',
                    'content-type': 'multipart/form-data; boundary=----WebKitFormBoundaryHB9AHAASh8Mf1CG3',
                    'cookie': 'UM_distinctid=167c148f761119-0cc301b871f4a8-76123f4b-144000-167c148f76221f; PHPSESSID=bj9saraupquc6nesfrci3gn5eaceth9f; phpdisk_info=BzRfZVI3UGoEMgBiCllWOAFYUWJdPAJjVGVSMQEzCj1RZ15uUTcANFNYAjEIZFdvB2QDNws2AmADNQZgVzNQZQc7X29SN1BrBGAAYgpgVmgBY1FjXWYCbFRvUjMBNwppUWJeOlE2ADtTYwJbCGNXNQdhAzMLYQJhAzUGZFdjUGYHOw%3D%3D; ylogin=787642; CNZZDATA1253610886=371681567-1545134562-https%253A%252F%252Fpc.woozooo.com%252F%7C1553670951',
                    'origin': 'https://pc.woozooo.com',
                    'referer': 'https://pc.woozooo.com/mydisk.php?item=files&action=index&u=18623452248',
                    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36'}
post_file_formdata = {'task': (None, '1'),
                      'folder_id': (None, '-1'),
                      'id': (None, 'WU_FILE_1'),
                      'size': (None, '11354'),
                      'upload_file': ('readmdict.7z', open(r'D:\data_analysis\py-spider\readmdict.7z', 'rb'),
                                      'application/octet-stream')}
post_result = requests.post(url=post_file_url, cookies=post_cookies, files=post_file_formdata)

file_list_page = 1
post_data = {
    'task': '5',
    'folder_id': '-1',
    'pg': file_list_page
}
file_list = requests.post(request_url, data=post_data, headers=list_header).content.decode()
file_id_list = re.findall('"id":"(.*?)"', file_list)

tmp_js = '''function f_sha(fid){
	var url;
	url ='http'+ isssl +'://pan.lanzou.com/' + fid+'/';
	$('div#f_sha').show(150);
	$('div#f_sha1').text('获取中...');

	$.ajax({
			type : 'post',
			url : '/doupload.php',
			data : { 'task':22,'file_id':fid },
			dataType : 'json',
			success:function(msg){
				if(msg.zt == '1'){
					//success
					if(msg.info.onof ==1){
						//on
						url =msg.info.is_newd +'/' + msg.info.f_id +'<br>密码:'+msg.info.pwd + msg.info.taoc;
						//urls ='http'+ isssl +'://pan.lanzou.com/' + msg.info.f_id;
						url_d = msg.info.is_newd+'/'+msg.info.f_id;
						code_suc(url_d);
						$('div#f_sha1').html(url);
					}else{
						//无密码
						//t.cn
						//tcn(msg.info.f_id);
						url =msg.info.is_newd +'/' + msg.info.f_id + msg.info.taoc;
						//urls ='http'+ isssl +'://pan.lanzou.com/' + msg.info.f_id;
						url_d = msg.info.is_newd+'/'+msg.info.f_id;
						code_suc(url_d);
						$('div#f_sha1').html(url);
					}
					url = msg.info.is_newd + '/' + msg.info.f_id;
				}else{
					w_info('获取失败，请重试');
				}
			},
			error:function(){
				w_info('获取失败，请重试');
			}
	
		});

}'''

f_id = '7726614'
request_header={'accept': 'application/json, text/javascript, */*; q=0.01',
 'accept-encoding': 'gzip, deflate, br',
 'accept-language': 'zh-CN,zh;q=0.9',
 'content-length': '24',
 'content-type': 'application/x-www-form-urlencoded; charset=UTF-8',
 'cookie': 'UM_distinctid=167c148f761119-0cc301b871f4a8-76123f4b-144000-167c148f76221f; PHPSESSID=bj9saraupquc6nesfrci3gn5eaceth9f; phpdisk_info=BzRfZVI3UGoEMgBiCllWOAFYUWJdPAJjVGVSMQEzCj1RZ15uUTcANFNYAjEIZFdvB2QDNws2AmADNQZgVzNQZQc7X29SN1BrBGAAYgpgVmgBY1FjXWYCbFRvUjMBNwppUWJeOlE2ADtTYwJbCGNXNQdhAzMLYQJhAzUGZFdjUGYHOw%3D%3D; ylogin=787642; CNZZDATA1253610886=371681567-1545134562-https%253A%252F%252Fpc.woozooo.com%252F%7C1553676357',
 'origin': 'https://pc.woozooo.com',
 'referer': 'https://pc.woozooo.com/mydisk.php?item=files&action=index&u=18623452248',
 'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
 'x-requested-with': 'XMLHttpRequest'}
request_url = 'https://pc.woozooo.com/doupload.php'
get_file_json = {'task': 22, 'folder_id': f_id}
get_file_json = urlencode(get_file_json)
get_result = requests.post(request_url+'?'+get_file_json, headers=request_header).content.decode()
print(get_result)


def down_url(url):
    detail = requests.get(url, headers=ua_header).content.decode()
    src = re.search('src="(.*?)"', detail).group(1)
    temp = re.search('f=(.*?)&t=(.*?)&k=(.*?)"', src)
    f = temp.group(1)
    t = temp.group(2)
    k = temp.group(3)
    url = 'https://www.lanzous.com/ajaxm.php'
    data = {
        'action': 'down_process',
        'file_id': f,
        't': t,
        'k': k
    }
    down_main = requests.post(url, data=data, headers=ua_header).content.decode()
    down_main = json.loads(down_main)
    down_url = down_main['dom'] + '/file/' + down_main['url']
    print(down_url)
