import os
import cv2
import numpy as np
import skimage
import scipy.fftpack as fftpack
from scipy.signal import butter, lfilter

# build pyramid for single img: [frame_number,w,h,c]
def build_laplacian_pyr(img, maxLeval, min_w=4):
    img = img.astype(np.float64)
    pyramid = []
    leval = 1
    laplac_img = np.copy(img)
    while(leval < maxLeval):
        if laplac_img.shape[0] <= min_w or laplac_img.shape[1] <= min_w:
            break
        img_downsample = cv2.pyrDown(laplac_img)
        img_upsample = cv2.pyrUp(img_downsample)
        diff = laplac_img - img_upsample
        pyramid.append(diff)
        laplac_img = img_downsample
        leval += 1
    
    pyramid.append(laplac_img)
    return pyramid

# reconstruct img from pyramid
def restruct_from_laplac(pyramid):
    if len(pyramid) <= 0:
        return
    if len(pyramid) <= 1:
        return pyramid[0]
    
    leval = len(pyramid) - 1
    img_tmp = pyramid[leval]
    leval -= 1
    while(leval > -1):
        img_upsample = cv2.pyrUp(img_tmp)
        img_tmp = img_upsample + pyramid[leval]
        leval -= 1

    return img_tmp

# build video level pyramid
def build_video_pyramid(frames, maxLeval=4):
    pyramid_video = []
    pyramid = build_laplacian_pyr(frames[0], maxLeval)
    maxLeval = max(len(pyramid), maxLeval)

    video_pyramid = [] # video_pyramid[frame_index] = [frame_pyramid] 每一层都是当前帧对应的金字塔
    for frame in frames:
        single_img_pyramid = build_laplacian_pyr(frame, maxLeval)
        video_pyramid.append(single_img_pyramid)
    
    # pyramid_video[pyr_leval] = all_frames
    for leval in range(maxLeval):
        index_leval_all_frames = []
        for i in range(len(frames)):
            index_leval_all_frames.append(video_pyramid[i][leval])
        pyramid_video.append(np.asarray(index_leval_all_frames))

    return pyramid_video

# reconstruct video from pyramid frames
def reconstruct_video_from_pyramid(pyramid_video):
    video_frames = []
    video_frames_num = pyramid_video[0].shape[0]
    for frame_index in range(video_frames_num):
        index_frame_pyrs = [] # index_frame_pyrs[frame_index] = [index_frame_pyramid]
        for pyr_leval in range(len(pyramid_video)):
            index_frame_pyrs.append(pyramid_video[pyr_leval][frame_index])
        index_frame = restruct_from_laplac(index_frame_pyrs)
        video_frames.append(index_frame)
    
    return video_frames


# band filter
def butter_bandpass(lowcut, highcut, fs, order=5):
    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    b, a = butter(order, [low, high], btype='band')
    return b, a

def butter_bandpass_filter(data, lowcut, highcut, fs, order=5):
    b, a = butter_bandpass(lowcut, highcut, fs, order=order)
    y = lfilter(b, a, data)
    return y

def video_butter_bandpass(video_pyr, fps):
    lowcut = 0.83/2
    highcut = 1.0/2
    filtered_video_pyr = []
    for layer_frames in video_pyr:
        filtered_layer = butter_bandpass_filter(layer_frames, lowcut, highcut, fps)
        filtered_video_pyr.append(filtered_layer)
    return filtered_video_pyr

# temporal ideal filter
def temporal_ideal_filter(tensor,low,high,fps,axis=0):
   
    fft=fftpack.fft(tensor,axis=axis)
    frequencies = fftpack.fftfreq(tensor.shape[0], d=1.0 / fps)
    bound_low = (np.abs(frequencies - low)).argmin()
    bound_high = (np.abs(frequencies - high)).argmin()
    if (bound_low==bound_high) and (bound_high<len(fft)-1):
        bound_high+=1
    fft[:bound_low] = 0
    fft[bound_high:-bound_high] = 0
    fft[-bound_low:] = 0
    iff=fftpack.ifft(fft, axis=axis)
    
    return np.abs(iff)

def video_ideal_filter(video_pyr, fps):
    lowcut = 0.83/2
    highcut = 1.0/2
    filtered_video_pyr = []
    for layer_frames in video_pyr:
        filtered_layer = temporal_ideal_filter(layer_frames, lowcut, highcut, fps)
        filtered_video_pyr.append(filtered_layer)
    return filtered_video_pyr

# amplify color signal: only amplify the last lsyer of pyramid  
def amplify_color_signal(origin_pyr, filtered_pyr, alpha):
    max_leval = len(origin_pyr) - 1
    origin_pyr[max_leval] += filtered_pyr[max_leval] * alpha

    return origin_pyr

# 对图片进行归一化
def linear_img(img_data):
    if img_data.shape == 2:
        img_data = (img_data - np.min(img_data)) / (np.max(img_data) - np.min(img_data))
    elif img_data.shape == 3:
        for i in range(3):
            img_data[:, :, i] = (img_data[:, :, i] - np.min(img_data[:, :, i])) / (np.max(img_data[:, :, i]) - np.min(img_data[:, :, i]))

    img_data[img_data>1] = 1
    img_data[img_data<0] = 0

    return img_data

def save_frames_to_video(video_frames, fps, video_path):
     #fourcc = cv2.VideoWriter_fourcc('a','v','c','1')
     fourcc = cv2.VideoWriter_fourcc(*'XVID')
     size = (video_frames[0].shape[1], video_frames[0].shape[0])
     out = cv2.VideoWriter(video_path, fourcc, fps, size)
     i = 1
     for frame in video_frames:
         rgb_img = skimage.color.yiq2rgb(frame)
         rgb_img = (255*linear_img(rgb_img)).astype(np.uint8)
         bgr_img = cv2.cvtColor(rgb_img, cv2.COLOR_RGB2BGR)
         out.write(bgr_img)
     out.release()


# get video all frames
def get_all_frames(video_path):
    if not os.path.exists(video_path):
        return 
    vidcap = cv2.VideoCapture(video_path)
    fps = vidcap.get(cv2.CAP_PROP_FPS)
    success,image = vidcap.read()
    frames = []
    while success:
        new_img = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        yiq_img = skimage.color.rgb2yiq(new_img).astype(np.float64)
        frames.append(yiq_img)
        success,image = vidcap.read()
    
    return frames, fps

def main():
    video_path = "./data/face.mp4"

    # get all frames from video
    frames, fps = get_all_frames(video_path)
    # build video level pyramid
    video_pyr = build_video_pyramid(frames, maxLeval=4)
    # 1、band filter
    band_filtered_video_pyr = video_butter_bandpass(video_pyr, fps)
    # amplify color signal
    alpha = 100
    ampl_video_pyr = amplify_color_signal(video_pyr, band_filtered_video_pyr, alpha)
    # reconstruct video from pyramid frames
    new_video_frames = reconstruct_video_from_pyramid(ampl_video_pyr)
    # save video to disk
    new_video_path = "./band_face.mp4"
    save_frames_to_video(new_video_frames, fps, new_video_path)

    # 2、temporal ideal filter
    ideal_filtered_video_pyr = video_ideal_filter(video_pyr, fps)
    # amplify color signal
    alpha = 30
    ampl_video_pyr = amplify_color_signal(video_pyr, ideal_filtered_video_pyr, alpha)
    # reconstruct video from pyramid frames
    new_video_frames = reconstruct_video_from_pyramid(ampl_video_pyr)
    # save video to disk
    new_video_path = "./ideal_face2.mp4"
    save_frames_to_video(new_video_frames, fps, new_video_path)


if __name__ == '__main__':
    main()
