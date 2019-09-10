from PIL import Image
import glob, os

img_path = glob.glob("./*.png")
path_save = "./"

for file in img_path:
    file_name, ext = os.path.splitext(file)
    name = os.path.join(path_save, file_name + '_ed.' + ext)
    im = Image.open(file)
    s1, s2 = im.size
    z1, z2 = s1 * 0.5, s2 * 0.5
    im.thumbnail((z1, z2))
    print(im.format, im.size)
    im.save(name, 'PNG')
