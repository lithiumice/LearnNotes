'''
pngquant.py
use pngquant to reduces png file size
Ruoqian, Chen<piao.polar@gmail.com>

----------
2015/4/3
1. del option --quality=50-90, special pic need skip can config in lod ini

  lod ini format:

[PixelFormat]
map_01.png=0

  0 means skip in file

----------
2015/4/2
1. desDir can be the same to srcDir, or another dir
2. lod ini config can be not exist

----------
2015/3/31
create
'''

import os
import os.path
import sys
import ConfigParser
import string

PngquantExe = "pngquant"

thisFilePath = sys.path[0]

print(("this py file in dir : " + thisFilePath))

projectPath = thisFilePath + "/../CMWar_2dx/CMWar_2dx/"
srcResDir = "Resources/"
dstResDir = "Resources/"

lodIniPath = projectPath + srcResDir + "ini/pic.ini"
keepOrgPaths = []
if os.path.exists(lodIniPath):
    config = ConfigParser.SafeConfigParser()
    config.read(lodIniPath)
    section = "PixelFormat"
    options = config.options(section)
    for option in options:
        value = string.atoi(config.get(section, option))
        if not value:
            keepOrgPaths.append(option)

print(keepOrgPaths)

srcResPath = projectPath + srcResDir

pngCount = 0
transCount = 0

# pngquant --force --skip-if-larger --ext .png --quality 50-90 --speed 1

for parent, dirnames, filenames in os.walk(srcResPath):
    print("----- process Dir " + parent)
    dstDir = parent.replace(srcResDir, dstResDir)
    if not os.path.exists(dstDir):
        os.makedirs(dstDir)
    for filename in filenames:
        if os.path.splitext(filename)[1] == '.png':
            pngCount += 1
            srcFilePath = os.path.join(parent, filename)
            dstFilePath = os.path.join(dstDir, filename)
            tmpFilePath = dstFilePath + ".tmp"

            if filename in keepOrgPaths:
                print("----- keep ----- " + filename)
            else:
                print ("----- process ----- " + filename)
                cmd = "\"" + PngquantExe + "\"" + " --force --speed=1 " + srcFilePath + " -o " + tmpFilePath
                os.system(cmd)
                if os.path.exists(tmpFilePath):
                    sizeNew = os.path.getsize(tmpFilePath)
                    sizeOld = os.path.getsize(srcFilePath)
                    if sizeNew < sizeOld:
                        open(dstFilePath, "wb").write(open(tmpFilePath, "rb").read())
                        transCount += 1
                    os.remove(tmpFilePath)
            if not os.path.exists(dstFilePath):
                open(dstFilePath, "wb").write(open(srcFilePath, "rb").read())

print(("Done. Trans Pngs: %d/%d" % (transCount, pngCount)))
