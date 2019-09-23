from keras import datasets
from sklearn import datasets
from sklearn.datasets import make_blobs

from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.ensemble import BaggingClassifier
from sklearn.ensemble import GradientBoostingClassifier

from sklearn.tree import DecisionTreeClassifier
from sklearn.datasets import make_gaussian_quantiles
from sklearn.utils.tests.test_bench import test_total_seconds
from sklearn.model_selection import train_test_split
import sklearn.metrics

import matplotlib.pyplot as plt
import numpy as np

x,y=datasets.make_classification(n_samples=1000,n_features=100,n_redundant=0,random_state=1)
trainX,testX,trainY,testY=train_test_split(x,y,test_size=0.2,random_state=55)
clf=AdaBoostClassifier(n_estimators=100)
clf.fit(trainX,trainY)
pre=clf.predict(testX)

clf_2=GradientBoostingClassifier(n_estimators=100)
clf_2.fit(trainX,trainY)
pre_2=clf_2.predict(testX)
print (sklearn.metrics.accuracy_score(testY,pre_2))
print (sklearn.metrics.f1_score(testY,pre_2))

clf_3=BaggingClassifier(n_estimators=100)
clf_3.fit(trainX,trainY)
pre_3=clf_3.predict(testX)
print (sklearn.metrics.accuracy_score(testY,pre_3))
print (sklearn.metrics.f1_score(testY,pre_3))

print (sklearn.metrics.accuracy_score(testY,pre))
print (sklearn.metrics.f1_score(testY,pre))
f_pos,t_pos,thresh=sklearn.metrics.roc_curve(testY,pre)
auc_area=sklearn.metrics.auc(f_pos,t_pos)
plt.plot(f_pos,t_pos,'darkorange',lw=2,label='AUC=%.2f'%auc_area)
plt.legend(loc='lower right')
plt.plot([0,1],[0,1],color='navy',linestyle='-')
plt.title('ROC')
plt.ylabel('True Pos Rate')
plt.xlabel('False Pos Rate')
plt.show()

