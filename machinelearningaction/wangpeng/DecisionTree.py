#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
import numpy as np



def cal_info_entropy(dataset, labels):
    label_dict = {}
    total = len(labels)
    for label in labels:
        if label in label_dict:
            label_dict[label] += 1
        else:
            label_dict[label] = 1
    
    result = 0.0
    for key, val in label_dict.items():
        prob = float(val/total)
        result -= (prob * np.log2(prob))
    
    return result

def get_major_lable(labels):
    label_dict = {}
    for label in labels:
        if label in label_dict:
            label_dict[label] += 1
        else:
            label_dict[label] = 1
    sort_label = sorted(label_dict.items(), key=lambda kv: kv[1], reverse=True)
    return sort_label[0][0]

# 将数据集中特征值等于feature_val的数据单独摘出来
def split_dataset(dataset, feature_index, feature_val, labels):
    new_dataset = []
    new_labels = []
    data_num = len(dataset)
    for i in range(data_num):
        if dataset[i][feature_index] == feature_val:
            new_line = dataset[i][:feature_index]
            new_line.extend(dataset[i][feature_index+1:])
            new_dataset.append(new_line)
            new_labels.append(labels[i])
    
    return new_dataset, new_labels

# 根据当前的dataset选择一个最好的特征，使得按照该特征进行分类后信息熵最小（即信息增益最大）
def choose_best_feature(dataset, labels):
    before_info_entropy = cal_info_entropy(dataset, labels)
    features_num = len(dataset[0])
    data_num = len(dataset)
    best_feature_index = -1
    min_info_entropy = before_info_entropy
    for i in range(features_num):
        cur_info_entropy = 0
        index_feature_classes = list(set([data[i] for data in dataset])) 
        for feature_class in index_feature_classes:
            new_dataset, new_labels = split_dataset(dataset, i, feature_class, labels)
            prob = len(new_dataset)/data_num
            info_entropy = cal_info_entropy(new_dataset, new_labels)
            cur_info_entropy += prob * info_entropy

        if cur_info_entropy < min_info_entropy:
            min_info_entropy = cur_info_entropy
            best_feature_index = i

    return best_feature_index


def create_tree(dataset, labels, col_name):
    label_uniq = list(set(labels))
    if len(label_uniq) <= 1:
        return label_uniq[0]
    if len(dataset[0]) <= 1:
        major_label = get_major_lable(labels)
        return major_label

    my_tree = {}
    best_feature_index = choose_best_feature(dataset, labels)
    best_feature = col_name[best_feature_index]
    my_tree[best_feature] = {}

    best_feature_classes = list(set([data[best_feature_index] for data in dataset])) 
    del(col_name[best_feature_index])
    for feature_class in best_feature_classes:
        new_dataset, new_labels = split_dataset(dataset, best_feature_index, feature_class, labels)
        my_tree[best_feature][feature_class] = create_tree(new_dataset, new_labels, col_name)

    return my_tree

def createDataSet():
    """
    Desc:
        创建数据集
    Args:
        无需传入参数
    Returns:
        返回数据集和对应的label标签
    """
    dataSet = [[1, 1],
               [1, 1],
               [1, 0],
               [0, 1],
               [0, 1]]
    col_name = ['no surfacing', 'flippers']
    labels = ['yes', 'yes', 'no', 'no', 'no']
    # 返回
    return dataSet, labels, col_name

def fish_test():
    dataSet, labels, col_name = createDataSet()
    my_tree = create_tree(dataSet, labels, col_name)
    print(my_tree)

if __name__ == "__main__":
    fish_test()
    #ContactLensesTest()