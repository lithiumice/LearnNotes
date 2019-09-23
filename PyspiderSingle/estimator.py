import tensorflow as tf
import tensorflow.feature_column as fc

import os
import sys

import matplotlib.pyplot as plt

tf.enable_eager_execution()
models_path = os.path.join(os.getcwd(), 'models')

sys.path.append(models_path)
from official.wide_deep import census_dataset
from official.wide_deep import census_main

census_dataset.download("/tmp/census_data/")
# export PYTHONPATH=${PYTHONPATH}:"$(pwd)/models"
# running from python you need to set the `os.environ` or the subprocess will not see the directory.

if "PYTHONPATH" in os.environ:
    os.environ['PYTHONPATH'] += os.pathsep + models_path
else:
    os.environ['PYTHONPATH'] = models_path

import pandas

train_df = pandas.read_csv(train_file, header=None, names=census_dataset._CSV_COLUMNS)
test_df = pandas.read_csv(test_file, header=None, names=census_dataset._CSV_COLUMNS)

train_df.head()
