#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import re
import random
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

    return list(result)

def word2vector(word_set, word):
    word_vector = np.zeros(len(word_set))
    for i in word:
        if i in word_set:
            word_vector[word_set.index(i)] = 1
    
    return word_vector

# 只针对二分类:positive:0 negtive:1
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
    positive_prob = np.log(positive_num/positive_num_total)
    negtive_prob = np.log(negtive_num/negtive_num_total)
    
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

# 测试一：留言区评论是否合格
def test1():
    dataset, labels = load_data_set()
    word_set = get_all_words(dataset)
    dataset_mat = []
    for data in dataset:
        data_vec = word2vector(word_set, data)
        dataset_mat.append(data_vec)

    negtive_prob_total, positive_prob, negtive_prob = train(dataset_mat, labels, word_set)
    print("negtive_prob_total:{} positive_prob:{} negtive_prob:{}".format(negtive_prob_total, positive_prob, negtive_prob))
    
    test_words = ['love', 'my', 'dalmation']
    test_words = ['stupid', 'garbage']
    test_vec = word2vector(word_set, test_words)
    p1 = sum(negtive_prob * test_vec) + np.log(negtive_prob_total)
    p0 = sum(positive_prob * test_vec) + np.log(1-negtive_prob_total)
    print("p1:{} p0:{}".format(p1, p0))


# 测试二：区分垃圾邮件
def test2():
    spam_dir = "/Users/megvii/wangpeng/gitrepo/machine-leraing-coding/machinelearningaction/data/4.NaiveBayes/email/spam"
    ham_dir = "/Users/megvii/wangpeng/gitrepo/machine-leraing-coding/machinelearningaction/data/4.NaiveBayes/email/ham"
    spam_file_list = os.listdir(spam_dir)
    ham_file_list = os.listdir(ham_dir)
    dataset_ori = []
    labels = []
    for file_ in spam_file_list:
        file_path = os.path.join(spam_dir, file_)
        dataset_ori.append(txt_2_words(file_path))
        labels.append(1)
    for file_ in ham_file_list:
        file_path = os.path.join(ham_dir, file_)
        dataset_ori.append(txt_2_words(file_path))
        labels.append(0)

    word_set = get_all_words(dataset_ori)
    dataset_mat = []
    for data in dataset_ori:
        data_vec = word2vector(word_set, data)
        dataset_mat.append(data_vec)
    
    test_index = random.sample(range(1, 50), 10)
    test_data = []
    test_labels = []
    train_data = []
    train_labels = []
    for i in range(len(dataset_mat)):
        if i in test_index:
            test_data.append(dataset_mat[i])
            test_labels.append(labels[i])
        else:
            train_data.append(dataset_mat[i])
            train_labels.append(labels[i])

    negtive_prob_total, positive_prob, negtive_prob = train(train_data, train_labels, word_set)
    err_count = 0
    for i in range(len(test_data)):
        p1 = sum(test_data[i] * negtive_prob) + np.log(negtive_prob_total)
        p0 = sum(test_data[i] * positive_prob) + np.log(1-negtive_prob_total)
        y_pre = 1 if p1 > p0 else 0
        if y_pre != test_labels[i]:
            err_count += 1
    print("err count is {}".format(err_count))



def txt_2_words(txt_path):
    try:
        with open(txt_path) as f:
            content = f.read()
    except:
        with open(txt_path, encoding='Windows 1252') as f:
            content = f.read()
    word_list = re.split(r'\W+', content)
    return [word.lower() for word in word_list if len(word) > 2]


if __name__ == "__main__":
    #test1()
    test2()