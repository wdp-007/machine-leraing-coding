import csv
import numpy as np

train_file = 'train_data.csv'

def SGD(X, Y, w, l, iteration = 1000):
    loss_list = []
    for i in range(iteration):
        pre = np.multiply(X, w)
        loss = pre - Y

        index = np.random(len(X))
        gradient = 2*loss[index]*X[index]
        w_new = w - l * gradient


train_X = []
train_Y = []
with open(train_file) as f:
    reader = csv.reader(f)
    # 读取一行，下面的reader中已经没有该行了
    head_row = next(reader)
    for row in reader:
        # 行号从2开始
        row_len = len(row)
        train_X.append(row[:len-1])
        train_Y.append(row[len-1])
        print(reader.line_num)
print("length of train_X : {}, features num is {}, length of train_Y :{}".format(len(train_X), len(train_x[0]), len(train_Y)))

