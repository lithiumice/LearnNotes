from PIL import Image
import glob, os


def get_FileSize(picture):
    f1 = os.path.getsize(picture)
    f2 = f1 / float(1024)
    return f2


def small(SIZE):
    SIZE *= 0.9
    return SIZE


a = float(input("图片大小限制kb："))

for infile in glob.glob('*.jpg'):
    file, ext = os.path.splitext(infile)
    im = Image.open(infile)

    b = get_FileSize(infile)
    size = im.size
    size1, size2 = size

    while b > a:
        size1, size2 = small(size1), small(size2)
        size = size1, size2
        im.thumbnail(size, Image.ANTIALIAS)
        im.save(file + '_add.jpg', 'jpeg')
        b = get_FileSize(file + 'add.jpg')
