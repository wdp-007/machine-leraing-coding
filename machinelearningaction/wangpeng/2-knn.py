import os
import numpy as np
import operator

def createDataSet():
    """
    Desc:
        创建数据集和标签
    Args:
        None
    Returns:
        group -- 训练数据集的 features
        labels -- 训练数据集的 labels
    调用方式
    import kNN
    group, labels = kNN.createDataSet()
    """
    group = array([[1.0, 1.1], [1.0, 1.0], [0, 0], [0, 0.1]])
    labels = ['A', 'A', 'B', 'B']
    return group, labels

def k_means(dataset, labels, inX, k):
    distance = (np.sum((dataset - inX) ** 2, axis=1)) ** 0.5
    distance = np.argsort(distance)
    lable_k = {}
    for i in range(k):
        cur_lable = labels[distance[i]]
        if cur_lable in lable_k:
            lable_k[cur_lable] += 1
        else:
            lable_k[cur_lable] = 1
    sorted_lable = sorted(lable_k.items(), key=lambda kv: kv[1], reverse=True)
    #import pdb
    #pdb.set_trace()
    return sorted_lable[0][0]

def auto_normal(dataset):

    min_col = dataset.min(0)
    max_col = dataset.max(0)
    dataset_new = (dataset - min_col)/(max_col - min_col)
    return dataset_new

def get_test1_dataset():
    file_path = "../data/2.KNN/datingTestSet2.txt"
    dataset = []
    labels = []
    with open(file_path, 'r') as f:
        for line in f:
            array = line.strip().split('	')
            dataset.append(array[:-1])
            labels.append(int(array[-1]))
    
    return np.array(dataset).astype(np.float64), np.array(labels).astype(np.int32)

def test1(k):
    dataset, labels = get_test1_dataset()
    dataset = auto_normal(dataset)

    test_num = int(len(dataset)/5)
    train_ds = dataset[test_num:]
    train_lb = labels[test_num:]
    test_ds = dataset[:test_num]
    test_lb = labels[:test_num]

    err_count = 0
    for i in range(test_num):
        y_pre = k_means(train_ds, train_lb, test_ds[i], k)
        if y_pre != test_lb[i]:
            err_count += 1
    print("The error predict count is {}, proportion is {}".format(err_count, err_count/test_num))



def get_test2_dataset():
    train_dir = "../data/2.KNN/trainingDigits"
    file_list = os.listdir(train_dir)
    dataset = []
    labels = []
    for file_ in file_list:
        file_full_path = os.path.join(train_dir, file_)
        data, label = get_single_data(file_full_path, file_)
        labels.append(label)
        dataset.append(data)

    return np.array(dataset).astype(np.int32), np.array(labels).astype(np.int32)

def get_single_data(file_full_path, file_name):
    label = int(file_name.split('_')[0])
    data = []
    with open(file_full_path, 'r') as f:
        for line in f:
            data.extend(list(line.strip()))
    data = np.array([int(i) for i in data])

    return data, label


def test2(k):
    train_dataset, train_labels = get_test2_dataset()
    test_dir = "../data/2.KNN/testDigits"
    test_list = os.listdir(test_dir)
    test_num = len(test_list)
    err_count = 0
    for file_ in test_list:
        file_full_path = os.path.join(test_dir, file_)
        data, label = get_single_data(file_full_path, file_)
        y_pre = k_means(train_dataset, train_labels, data, k)
        #print("predict: {}  label : {}".format(y_pre, label))
        if y_pre != label:
            err_count += 1
    print("The error predict count is {}, proportion is {}".format(err_count, err_count/test_num))


if __name__ == '__main__':
    test1(2)
    test2(2)
    