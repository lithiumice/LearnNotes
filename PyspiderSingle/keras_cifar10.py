from sklearn.preprocessing import LabelBinarizer
from sklearn.metrics import classification_report
from keras.models import Sequential
from keras.layers.core import Dense
from keras.optimizers import SGD
from keras.datasets import cifar10
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
from six.moves import cPickle as pickle
import os
import platform


def load_pickle(f):
    version = platform.python_version_tuple()  # 取python版本号
    if version[0] == '2':
        return pickle.load(f)  # pickle.load, 反序列化为python的数据类型
    elif version[0] == '3':
        return pickle.load(f, encoding='latin1')
    raise ValueError("invalid python version: {}".format(version))


def load_CIFAR_batch(filename):
    """ load single batch of cifar """
    with open(filename, 'rb') as f:
        datadict = load_pickle(f)  # dict类型
        X = datadict['data']  # X, ndarray, 像素值
        Y = datadict['labels']  # Y, list, 标签, 分类

        # reshape, 一维数组转为矩阵10000行3列。每个entries是32x32
        # transpose，转置
        # astype，复制，同时指定类型
        X = X.reshape(10000, 3, 32, 32).transpose(0, 2, 3, 1).astype("float")
        Y = np.array(Y)
        return X, Y


def load_CIFAR10(ROOT='cifar-10-batches-py'):
    """ load all of cifar """
    xs = []  # list
    ys = []

    # 训练集batch 1～5
    for b in range(1, 6):
        f = os.path.join(ROOT, 'data_batch_%d' % (b,))
        X, Y = load_CIFAR_batch(f)
        xs.append(X)  # 在list尾部添加对象X, x = [..., [X]]
        ys.append(Y)
    Xtr = np.concatenate(xs)  # [ndarray, ndarray] 合并为一个ndarray
    Ytr = np.concatenate(ys)
    del X, Y

    Xte, Yte = load_CIFAR_batch(os.path.join(ROOT, 'test_batch'))
    return Xtr, Ytr, Xte, Yte


# def get_input():
#     filenames = tf.train.match_filenames_once(DATA_DIR+'/data_batch_*')
#     filename_queue = tf.train.string_input_producer(filenames)
#
#     image_bytes = IMAGE_SIZE * IMAGE_SIZE * IMAGE_DEPTH
#     record_bytes = image_bytes + LABEL_BYTES
#     #使用FixedLengthRecordReader读取样本，每次读取一个
#     reader = tf.FixedLengthRecordReader(record_bytes=record_bytes)
#     #获取样本的值
#     _,value = reader.read(filename_queue)
#     #读出来的样本为二进制的字符串格式，转化为uint8的格式
#     raw_value = tf.decode_raw(value,tf.uint8)
#     #划分label和image
#     labels = tf.cast(tf.strided_slice(raw_value,[0],[1]),tf.int32)
#     #由于image是按照(depth,height,width)的格式存储的，因此读出来后还要将其转化为(height,width,depth)的格式
#     images = tf.reshape(
#         tf.strided_slice(raw_value,[LABEL_BYTES],[LABEL_BYTES+image_bytes]),
#         [IMAGE_DEPTH,IMAGE_SIZE,IMAGE_SIZE]
#     )
#     images = tf.transpose(images,[1,2,0])
#     images = tf.cast(images,tf.float32)
#     #数据类型：label是int32，image是范围为0-1的float32
#
#     #标准化处理：减去平均值并除以方差，使得样本均值为0，方差为1
#     standard_images = tf.image.per_image_standardization(images)
#
#     #官方bug，得加上
#     standard_images.set_shape([RESIZE_SIZE,RESIZE_SIZE,3])
#     labels.set_shape([1])
#
#     return standard_images,labels

print("[INFO] loading CIFAR-10 data...")
# trainX, trainY, testX, testY = load_CIFAR10()
((trainX, trainY), (testX, testY)) = cifar10.load_data()
trainX = trainX.astype("float") / 255.0
testX = testX.astype("float") / 255.0
trainX = trainX.reshape((trainX.shape[0], 3072))
testX = testX.reshape((testX.shape[0], 3072))

lb = LabelBinarizer()
trainY = lb.fit_transform(trainY)
testY = lb.transform(testY)
# initialize the label names for the CIFAR-10 dataset
labelNames = ["airplane", "automobile", "bird", "cat", "deer",
"dog", "frog", "horse", "ship", "truck"]

model = Sequential()
model.add(Dense(1024, input_shape=(3072,), activation="relu"))
model.add(Dense(512, activation="relu"))
model.add(Dense(10, activation="softmax"))

print("[INFO] training network...")
sgd = SGD(0.01)
model.compile(loss="categorical_crossentropy", optimizer=sgd,
metrics=["accuracy"])
H = model.fit(trainX, trainY, validation_data=(testX, testY),
epochs=100, batch_size=32)

print("[INFO] evaluating network...")
predictions = model.predict(testX, batch_size=32)
print(classification_report(testY.argmax(axis=1),
                            predictions.argmax(axis=1), target_names=labelNames))

plt.style.use("ggplot")
plt.figure()
plt.plot(np.arange(0, 100), H.history["loss"], label="train_loss")
plt.plot(np.arange(0, 100), H.history["val_loss"], label="val_loss")
plt.plot(np.arange(0, 100), H.history["acc"], label="train_acc")
plt.plot(np.arange(0, 100), H.history["val_acc"], label="val_acc")
plt.title("Training Loss and Accuracy")
plt.xlabel("Epoch #")
plt.ylabel("Loss/Accuracy")
plt.legend()
plt.savefig('cifar10_final.png')