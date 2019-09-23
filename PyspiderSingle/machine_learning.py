from keras.layers import Flatten
from keras.layers import Conv2D
from keras.layers import Dense
from keras.layers import MaxPooling2D
from keras import Sequential


model = Sequential()

model.add(Conv2D(20, (5, 5), padding="same", input_shape=(20, 20, 1), activation="relu"))

model.add(MaxPooling2D(pool_size=(2, 2), strides=(2, 2)))

model.add(Conv2D(50, (5, 5), padding="same", activation="relu"))

model.add(MaxPooling2D(pool_size=(2, 2), strides=(2, 2)))

model.add(Flatten())

model.add(Dense(500, activation="relu"))

# Output layer with 32 nodes (one for each possible letter/number we predict)

model.add(Dense(32, activation="softmax"))

# Ask Keras to build the TensorFlow model behind the scenes

model.compile(loss="categorical_crossentropy", optimizer="adam", metrics=["accuracy"])

# Train the neural network

model.fit(X_train, Y_train, validation_data=(X_test, Y_test), batch_size=32, epochs=10, verbose=1)