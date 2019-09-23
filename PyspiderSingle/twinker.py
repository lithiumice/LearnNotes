from tkinter import *  # 导入 Tkinter 库
import tkinter.messagebox
root = Tk()  # 创建窗口对象的背景色
li = ['C', 'python', 'php', 'html', 'SQL', 'java']
movie = ['CSS', 'jQuery', 'Bootstrap']
listb = Listbox(root)  # 创建两个列表组件
listb2 = Listbox(root)
for item in li:  # 第一个小部件插入数据
    listb.insert(0, item)

for item in movie:  # 第二个小部件插入数据
    listb2.insert(0, item)


cw=10,50,240,210

w=Canvas.create_arc(cw,start=0,extent=150,fill='blue')
img=PhotoImage('glass.jpg')
image=Canvas.create_image(50,50,anchor=NE,image=img)
cv = Canvas(root,bg = 'white')
cv.create_rectangle(10,10,110,110)
cv.pack()
listb.pack()  # 将小部件放置到主窗口中
listb2.pack()
root.mainloop()