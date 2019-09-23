from sklearn.preprocessing import LabelBinarizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from minivggnet import MiniVGGNet
from keras.optimizers import SGD
from keras.datasets import cifar10
from keras.optimizers import Adam
# from imutils import paths
import matplotlib.pyplot as plt
import numpy as np
from keras.datasets.cifar import load_batch
from keras import backend as K
import os


def cifar10_load_data():
    path = 'cifar10'
    num_train_samples = 50000

    x_train = np.empty((num_train_samples, 3, 32, 32), dtype='uint8')
    y_train = np.empty((num_train_samples,), dtype='uint8')

    for i in range(1, 6):
        fpath = os.path.join(path, 'data_batch_' + str(i))
        (x_train[(i - 1) * 10000: i * 10000, :, :, :],
         y_train[(i - 1) * 10000: i * 10000]) = load_batch(fpath)

    fpath = os.path.join(path, 'test_batch')
    x_test, y_test = load_batch(fpath)

    y_train = np.reshape(y_train, (len(y_train), 1))
    y_test = np.reshape(y_test, (len(y_test), 1))

    if K.image_data_format() == 'channels_last':
        x_train = x_train.transpose(0, 2, 3, 1)
        x_test = x_test.transpose(0, 2, 3, 1)

    return (x_train, y_train), (x_test, y_test)



(trainX, trainY), (testX, testY) = cifar10_load_data()
trainX = trainX.astype("float") / 255.0
testX = testX.astype("float") / 255.0

lb = LabelBinarizer()
trainY = lb.fit_transform(trainY)
testY = lb.transform(testY)
labelNames = ["airplane", "automobile", "bird", "cat", "deer",
              "dog", "frog", "horse", "ship", "truck"]

model = MiniVGGNet.build(width=32, height=32, depth=3, classes=10)
opt = SGD(lr=0.01, decay=0.01 / 30, momentum=0.9, nesterov=True)
model.compile(loss='categorical_crossentropy', metrics=['accuracy'], optimizer=opt)
H = model.fit(trainX, trainY, validation_data=(testX, testY), batch_size=64, epochs=30, verbose=1)
predictions=model.predict(testY,batch_size=64)
report=classification_report(testY.argmax(axis=1),predictions.argmax(axis=1),target_names=labelNames)
print(report)
model.save('cifar_vgg.hdf5')
