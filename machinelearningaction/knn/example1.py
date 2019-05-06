# -*- coding: UTF-8 -*-
import numpy as np

def create_dataset():
    dataset = np.array([[1,101],[5,89],[108,5],[115,8]])
    labels = ['爱情片','爱情片','动作片','动作片']

    return dataset, labels

def classify0(inX, dataset, labels, k):
    x_tmp1 = 