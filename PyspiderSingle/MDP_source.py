from sklearn.model_selection import train_test_split
import sklearn.metrics

import matplotlib.pyplot as plt
import numpy as np

import gym

env=gym.Env
Q={}
statses=[1,2,3,4,5,6,7,8]
actions=['n','e','s','w']

alpha=0.1
gamma=0.5
epsilon=0.1

for s in statses:
    for a in actions:
        key=f"{s}_{a}"
        Q[key]=0
for epsode in range(100):
    s0=env.reset()
    s1=observation
    a1=epsilon_greedy(Q,s0,epsilon)

    key0=f"{s0,a0}"
    key1=f"{s1,a1}"




def epsilon_greedy(Q,state,epsilon):
    amam=0
    key="%d_%s"%(state,actions[0])
