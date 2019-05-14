#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import numpy as np

"""
贝叶斯公式
p(xy)=p(x|y)p(y)=p(y|x)p(x)
p(x|y)=p(y|x)p(x)/p(y)
"""

def get_all_words(dataset):
    result = set()
    for line in dataset:
        result = result | set(line)

    return result

def word2vector(word_set, word):
    word_vector = np.zeros(len(word_set))
    for i in word:
        if i in word_set:
            word_vector[word_set.index(i)] = 1
    
    return word_vector

# 只针对二分类
def train(dataset_mat, labels, word_set):
    total_num = len(labels)
    negtive_prob_total = float(sum(labels)/total_num)

    positive_num = np.ones(len(word_set))
    negtive_num = np.ones(len(word_set))
    positive_num_total = 2.0
    negtive_num_total = 2.0
    for i in range(total_num):
        if labels[i] == 0:
            positive_num += dataset_mat[i]
            positive_num_total += sum(dataset_mat[i])
        else:
            negtive_num += dataset_mat[i]
            negtive_num_total += sum(dataset_mat[i]) 
    positive_prob = positive_num/positive_num_total
    negtive_prob = negtive_num/negtive_num_total
    
    return negtive_prob_total, positive_prob, negtive_prob


def load_data_set():
    """
    创建数据集,都是假的 fake data set 
    :return: 单词列表posting_list, 所属类别class_vec
    """
    posting_list = [
        ['my', 'dog', 'has', 'flea', 'problems', 'help', 'please'],
        ['maybe', 'not', 'take', 'him', 'to', 'dog', 'park', 'stupid'],
        ['my', 'dalmation', 'is', 'so', 'cute', 'I', 'love', 'him'],
        ['stop', 'posting', 'stupid', 'worthless', 'gar e'],
        ['mr', 'licks', 'ate', 'my', 'steak', 'how', 'to', 'stop', 'him'],
        ['quit', 'buying', 'worthless', 'dog', 'food', 'stupid']]
    class_vec = [0, 1, 0, 1, 0, 1]  # 1 is 侮辱性的文字, 0 is not
    return posting_list, class_vec

def test1():
    dataset, labels = load_data_set()
    word_set = get_all_words(dataset)
    dataset_mat = []
    for data in dataset:
        data_vec = word2vector(word_set, data)
        dataset_mat.append(data_vec)

    


if __name__ == "__main__":
    #fish_test()
    lense_test()