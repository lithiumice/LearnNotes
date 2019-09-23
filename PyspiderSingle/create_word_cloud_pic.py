#!python2
#encoding='utf-8'
from wordcloud import WordCloud
import matplotlib.pyplot
import jieba

file_content=open('QQ_word_2.txt','r').read()
word_list=jieba.cut(file_content,cut_all=True)
wl=" ".join(word_list)
wcloud=WordCloud(background_color='black',max_words=2000,font_path='C:/Windows/Fonts/simhei.ttf'
				,height=2500,width=2500,max_font_size=300,random_state=30)
cloud_content=wcloud.generate(wl)
matplotlib.pyplot.imshow(cloud_content)
matplotlib.pyplot.axis('off')
matplotlib.pyplot.show()
wcloud.to_file('wc_Qzone_2.png')
