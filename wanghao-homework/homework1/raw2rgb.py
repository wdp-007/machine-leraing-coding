from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import cv2
from skimage.io import imread
from scipy.ndimage.filters import convolve
from scipy.interpolate import RectBivariateSpline, interp2d
from skimage.color import rgb2gray, rgb2grey


# 对图片进行归一化
def linear_img(img_data, max_pixel=15000, min_pixel=2050):
    img = (img_data - min_pixel) / (max_pixel - min_pixel)
    img[img>1] = 1
    img[img<0] = 0

    return img

# 掩模图像
def masks_CFA_Bayer(shape, pattern='RGGB'):

    pattern = pattern.upper()

    channels = dict((channel, np.zeros(shape)) for channel in 'RGB')
    for channel, (y, x) in zip(pattern, [(0, 0), (0, 1), (1, 0), (1, 1)]):
        channels[channel][y::2, x::2] = 1

    return tuple(channels[c] for c in 'RGB')

# 去马赛克，初步完成从raw到rgb
def demosaicing(masks, imgIn):
    r, g, b = [imgIn * mask for mask in masks]

    # 借鉴github中的实现：https://github.com/colour-science/colour-demosaicing/blob/develop/colour_demosaicing/bayer/demosaicing/bilinear.py
    H_G = np.asarray(
        [[0, 1, 0],
         [1, 4, 1],
         [0, 1, 0]]) / 4  # yapf: disable

    H_RB = np.asarray(
        [[1, 2, 1],
         [2, 4, 2],
         [1, 2, 1]]) / 4  # yapf: disable

    R = convolve(r, H_RB)
    G = convolve(g, H_G)
    B = convolve(b, H_RB)

    return [R, G, B]

# 白平衡:灰世界假设
def white_bl_gray(img_rgb):
    R, G, B = img_rgb
    r_mean = np.mean(R)
    g_mean = np.mean(G)
    b_mean = np.mean(B)

    R = g_mean/r_mean * R
    G = G
    B = g_mean/b_mean * B

    return [R, G, B]

# 白平衡:白世界假设
def white_bl_white(img_rgb):
    R, G, B = img_rgb
    r_max = np.max(R)
    g_max = np.max(G)
    b_max = np.max(B)

    R = g_max/r_max * R
    G = G
    B = g_max/b_max * B

    return [R, G, B]

# 去燥：中值滤波
def denoising(img_rgb):
    R, G, B = img_rgb
    kernal = np.asarray(
        [[1, 1, 1],
         [1, 4, 1],
         [1, 1, 1]]) / 9
    R = convolve(R, kernal)
    G = convolve(G, kernal)
    B = convolve(B, kernal)

    return (R, G, B)

# 亮度修正
def color_reproduc(img_rgb, v = 3):
    img_max = np.max(img_rgb)
    img = img_rgb * v/img_max
    img[img>1] = 1

    return img

# gamma校正
def gamma_scale(img_rgb):
    isDark = img_rgb<0.0031308
    isBright = np.logical_not(isDark)

    img_out = np.zeros(img_rgb.shape)
    img_out[isDark] = img_rgb[isDark] * 12.92
    img_out[isBright] = ((img_rgb[isBright]) ** (1/2.4)) * (1 + 0.055)
    img_out[img_out>1] = 1

    return img_out

# 保存压缩图片
def save_and_compress(img_data, img_name):
    img = (img_data * 255/np.max(img_data)).astype(np.uint8)
    img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
    cv2.imwrite('{}.jpg'.format(img_name),img, [cv2.IMWRITE_JPEG_QUALITY, 95] )

def main():
    img_data = imread('./banana_slug.tiff')
    img_data = img_data.astype(np.float64)
    img_data = linear_img(img_data, 15000, 2047)
    masks = masks_CFA_Bayer(img_data.shape)
    rgb_list = demosaicing(masks, img_data)
    wb_gray = white_bl_gray(rgb_list)
    wb_white = white_bl_white(rgb_list)
    img_graywb = denoising(wb_gray)
    img_whitewb = denoising(wb_white)
    rgb_graywb = np.stack(img_graywb, axis=2)
    rgb_whitewb = np.stack(img_whitewb, axis=2)
    rgb_graywb = color_reproduc(rgb_graywb)
    rgb_whitewb = color_reproduc(rgb_whitewb)
    rgb_graywb = gamma_scale(rgb_graywb)
    rgb_whitewb = gamma_scale(rgb_whitewb)
    save_and_compress(rgb_graywb, 'result_graywb')
    save_and_compress(rgb_whitewb, 'result_whitewb')



if __name__ == "__main__":
    main()