from sklearn.preprocessing import LabelBinarizer
from sklearn.metrics import classification_report
from pyimagesearch.nn.conv.lenet import LeNet
from keras.optimizers import SGD
from keras.optimizers import adam
from keras.datasets import mnist
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn import datasets
from keras.models import Sequential
from keras.applications import Xception
from keras.preprocessing.image import img_to_array
from keras.preprocessing.image import load_img
from keras.layers.core import Dense
from keras.applications import imagenet_utils
from keras.applications.inception_v3 import preprocess_input
from keras.models import load_model
from keras.models import Model
dense=Model.load_weights('denseNet169.h5')
dense=load_model()
dataset=datasets.fetch_mldata("MNIST Original")
data=dataset.data

preprocessor=imagenet_utils.preprocess_input
inputShape=(224,224)
img=load_img('panda_test.jpg',target_size=inputShape)
image=img_to_array(img)
image=np.expand_dims(image,axis=0)
image=preprocessor(image)
(trainX, trainY), (testX, testY) = mnist.load_data()
# (trainX,trainY,testX,testY)=train_test_split()
trainX = trainX.astype("float") / 255.0
testX = testX.astype("float") / 255.0
trainX=np.expand_dims(trainX,1)
testX=np.expand_dims(testX,1)
# trainX = trainX.reshape((trainX.shape[0], 784))
# testX = testX.reshape((testX.shape[0], 784))

lb = LabelBinarizer()
trainY = lb.fit_transform(trainY)
testY = lb.transform(testY)
labelNames = ["0", "1", "2", "3", "4",
              "5", "6", "7", "8", "9"]
lenet_model=LeNet.build(width=28,height=28,depth=1,classes=10)
lenet_model.compile(loss="categorical_crossentropy", optimizer=SGD(lr=0.01,decay=0.01/30), metrics=["accuracy"])
History=lenet_model.fit(trainX,trainY,batch_size=128,epochs=30,verbose=1,validation_data=(testX,testY))

# model = Sequential()
# model.add(Dense(1024, input_shape=(784,), activation="relu"))
# model.add(Dense(512, activation="relu"))
# model.add(Dense(10, activation="softmax"))
#
# print("[INFO] training network...")
# sgd = SGD(lr=0.01, decay=0.0001)
# model.compile(loss="categorical_crossentropy", optimizer=sgd, metrics=["accuracy"])
# H = model.fit(trainX, trainY, validation_data=(testX, testY), epochs=30, batch_size=128)

# model=MiniVGGNet.build(width=28, height=28 ,depth=1 ,classes=10)
# opt=SGD(lr=0.01, decay=0.01 / 40 ,momentum=0.9 ,nesterov=True)
# model.compile(loss='categorical_crossentropy',metrics=['accuracy'],optimizer=opt)
# H=model.fit(trainX,trainY,validation_data=(testX,testY),batch_size=64,epochs=30,verbose=1)

predictions = model.predict(testX, batch_size=64)
report = classification_report(testY.argmax(axis=1), predictions.argmax(axis=1), target_names=labelNames)
print(report)
