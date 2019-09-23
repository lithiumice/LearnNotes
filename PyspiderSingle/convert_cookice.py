
def convert_cookice(str):
    str_after = '\'' + str.replace(':', '\':\'').replace('\n', '\'\n\',') + '\','
    print(str_after)
    return str_after


# cookies_list = {}
# str = raw_input()
# while str is not '\n':
#     name = re.search('(.*?):',str)
#     content = re.search(':(.*?)',str)
#     cookies_list[name] = content
#     str = raw_input()
# print cookies_list
