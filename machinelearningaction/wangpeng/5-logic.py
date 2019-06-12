#!/usr/bin/python
# -*- coding:utf-8 -*-

import os
import numpy as np

def sigmod(inX):

    return 1.0/(1+np.exp(-inX))

def gradesc(dataset, lables, itera_time=500, alpha=0.001):
    dataset_mat = np.asmatrix(dataset)
    lables_mat = np.transpose(np.asmatrix(lables))
    m,n = dataset_mat.shape[:2]
    weights = np.ones((n, 1))
    for i in range(itera_time):
        y_pre = sigmod(np.dot(dataset_mat, weights)) # m*n  *  n*1
        loss = y_pre - lables_mat  # m*1  - m*1
        #grad = np.dot(np.transpose(dataset_mat), loss)  # n*m  *  m*1
        grad = np.dot(np.transpose(dataset_mat), loss) / m
        weights -= alpha * grad

    return weights

def plot_best_fit(weights, data_file):
    """
    可视化
    :param weights: 
    :return: 
    """
    import matplotlib.pyplot as plt
    data_mat, label_mat = load_dataset1(data_file)
    data_arr = np.array(data_mat)
    n = np.shape(data_mat)[0]
    x_cord1 = []
    y_cord1 = []
    x_cord2 = []
    y_cord2 = []
    for i in range(n):
        if int(label_mat[i]) == 1:
            x_cord1.append(data_arr[i, 1])
            y_cord1.append(data_arr[i, 2])
        else:
            x_cord2.append(data_arr[i, 1])
            y_cord2.append(data_arr[i, 2])
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(x_cord1, y_cord1, s=30, color='k', marker='^')
    ax.scatter(x_cord2, y_cord2, s=30, color='red', marker='s')
    x = np.arange(-3.0, 3.0, 0.1)
    y = (-weights[0] - weights[1] * x) / weights[2]
    """
    y的由来，卧槽，是不是没看懂？
    首先理论上是这个样子的。
    dataMat.append([1.0, float(lineArr[0]), float(lineArr[1])])
    w0*x0+w1*x1+w2*x2=f(x)
    x0最开始就设置为1叻， x2就是我们画图的y值，而f(x)被我们磨合误差给算到w0,w1,w2身上去了
    所以： w0+w1*x+w2*y=0 => y = (-w0-w1*x)/w2   
    """
    ax.plot(x, y)
    plt.xlabel('x1')
    plt.ylabel('y1')
    plt.show()


def load_dataset1(data_file):
    dataset = []
    labels = []
    
    with open(data_file, 'r') as f:
        for line in f:
            tmp = []
            tmp.append(1.0)
            array = line.split("	")
            tmp.extend(array[:-1])
            dataset.append(tmp)
            labels.append(array[-1])
    dataset = np.asarray(dataset)
    labels = np.asarray(labels)
    return dataset.astype(np.float64), labels.astype(np.float64)

def test1():
    data_file = "data/5.Logistic/TestSet.txt"
    dataset, labels = load_dataset1(data_file)
    weights = gradesc(dataset, labels)
    plot_best_fit(weights, data_file)

def test2():
    data_file = "data/5.Logistic/HorseColicTraining.txt"
    dataset, labels = load_dataset1(data_file)
    weights = gradesc(dataset, labels)

    test_file = "data/5.Logistic/HorseColicTest.txt"
    test_dataset, test_labels = load_dataset1(test_file)
    test_dataset_mat = np.asmatrix(test_dataset)
    test_lables_mat = np.transpose(np.asmatrix(test_labels))
    y_pre = sigmod(np.dot(test_dataset_mat, weights))
    y_pre[y_pre > 0.5] = 1.0
    y_pre[y_pre <= 0.5] = 0.0
    err_count = np.sum(y_pre - test_lables_mat)
    error_rate = err_count / test_dataset_mat.shape[0]
    print("err count is {}, total count is {}".format(err_count, test_dataset_mat.shape[0]))
    print('the error rate is {}'.format(error_rate))



if __name__ == "__main__":
    test1()
    #test2()