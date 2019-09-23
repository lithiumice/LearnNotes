import os


def clea_null(dir_name):
    os.chdir('./{}'.format(dir_name))
    cwd = os.getcwd()
    files = os.listdir(cwd)
    try:
        for filel in files:
            if os.path.getsize(filel) == 0:
                os.remove(filel)
    except:
        pass


