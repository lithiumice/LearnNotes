# encoding=utf-8
from tkinter import *
from tkinter.filedialog import *
from PIL import Image as Img

info = {'path': []}


def make_app():
    app = Tk()
    Label(app, text='Compress Picture', font=('Hack', 20, 'bold')).pack()
    Listbox(app, name='lbox', bg='#f2f2f2').pack(fill=BOTH, expand=True)
    Button(app, text='Open', command=ui_getdata).pack()
    scale_obj = Scale(app, from_=0, to=100, orient = HORIZONTAL)
    scale_obj.pack()
    Button(app, text='compress', command=compress).pack()
    app.geometry('300x400')
    return app


def ui_getdata():
    f_name = askopenfilenames()
    lbox = app.children['lbox']
    info['path'] = f_name
    if info['path']:
        for name in f_name:
            lbox.insert(END, name.split('/')[-1])


def compress():
    for f_path in info['path']:
        output = './'
        name = f_path.split('/')[-1]
        image = Img.open(f_path)
        image.save(output + 'C_' + name, quality=0.3)


app = make_app()

mainloop()
