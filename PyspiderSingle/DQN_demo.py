from keras.models import Sequential
from keras.layers.core import Dense
from keras.optimizers import SGD
from keras.utils.vis_utils import plot_model
from keras import backend as K
import matplotlib.pyplot as plt
import numpy as np
from collections import deque
import gym
import random


class DQNagent:
    def __init__(self, state_size, action_size):
        self.state_size = state_size
        self.epsilon = 0.1
        self.action_size = action_size
        self.lr = 0.01
        self.gamma = 0.1
        self.model = self._build_model()
        self.memory = deque(maxlen=2000)

    def remember(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))

    def reply(self, batch_size):
        minibatch = random.sample(self.memory, batch_size)
        for state, action, reward, next_state, done in minibatch:
            target = reward
            if not done:
                target = (reward + self.gamma * np.amax(self.model.predict(next_state)[0]))
            target_f = self.model.predict(state)
            target_f[0][action] = target
            self.model.fit(state, target_f, epochs=1, verbose=0)

    def _build_model(self):
        model = Sequential()
        model.add(Dense(24, input_dim=self.state_size, activation='relu'))
        model.add(Dense(24, activation='relu'))
        model.add(Dense(self.action_size, activation='linear'))
        model.compile(loss='mse', optimizer=SGD(lr=self.lr))
        return model

    def act(self, state):
        if np.random.rand() <= self.epsilon:
            return random.randrange(self.action_size)
        act_value = self.model.predict(state)
        return np.argmax(act_value[0])

    # def plot_model(self):
    #     plot_model(self.model, to_file='dqn-mlp-v0.png', show_shapes=True)


env = gym.make('CartPole-v0')
state_size = env.observation_space.shape[0]
action_size = env.action_space.n
batch_size = 32
agent = DQNagent(state_size, action_size)
for e in range(1000):
    print('e:%d'%e)
    state = env.reset()
    state = np.reshape(state, [1, state_size])
    for time in range(500):
        env.render()
        print('t:%d'%time)
        action = agent.act(state)
        next_state, reward, done, _ = env.step(action)
        reward = reward if not done else -10
        next_state = np.reshape(next_state, [1, state_size])
        agent.remember(state, action, reward, next_state, done)
        state = next_state
        if len(agent.memory) > batch_size:
            agent.reply(batch_size)
