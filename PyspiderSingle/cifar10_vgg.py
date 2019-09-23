from sklearn.preprocessing import LabelBinarizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
# from pyimagesearch.preprocessing.imagetoarrayprocessor import ImageToArrayPreprocessor
# from pyimagesearch.preprocessing.preprocessor import SimplePreprocessor
# from pyimagesearch.datasets.datasetloader import SimpleDatasetLoader
from pyimagesearch.nn.conv.minivggnet import MiniVGGNet
from keras.optimizers import SGD
from keras.datasets import cifar10
from keras.optimizers import Adam
# from imutils import paths
import matplotlib.pyplot as plt
import numpy as np
import keras
from keras.myfuction import load_data
from pyimagesearch.myfuction import load_CIFAR10
# ((trainX,trainY),(testX,testY))=cifar10.get_file()
(trainX,trainY),(testX,testY)=load_data()
# trainX, trainY, testX, testY = load_CIFAR10()
# sp = SimplePreprocessor(32, 32)
# iap = ImageToArrayPreprocessor()
trainX = trainX.astype("float") / 255.0
testX = testX.astype("float") / 255.0
# trainX = trainX.reshape((trainX.shape[0], 3072))
# testX = testX.reshape((testX.shape[0], 3072))

lb = LabelBinarizer()
trainY = lb.fit_transform(trainY)
testY = lb.transform(testY)
labelNames = ["airplane", "automobile", "bird", "cat", "deer",
"dog", "frog", "horse", "ship", "truck"]

model=MiniVGGNet.build(width=32, height=32 ,depth=3 ,classes=10)
opt=SGD(lr=0.01, decay=0.01 / 40 ,momentum=0.9 ,nesterov=True)
model.compile(loss='categorical_crossentropy',metrics=['accuracy'],optimizer=opt)
H=model.fit(trainX,trainY,validation_data=(testX,testY),batch_size=64,epochs=30,verbose=1)

predictions=model.predict(testX,batch_size=64)
report=classification_report(testY.argmax(axis=1),predictions.argmax(axis=1),target_names=labelNames)
print(report)
