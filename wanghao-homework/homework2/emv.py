import os
import cv2
import numpy as np

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
    pyramid = build_laplacian_pyr(frames[0])
    maxLeval = max(len(pyramid), maxLeval)

    video_pyramid = [] # video_pyramid[frame_index] = [frame_pyramid] 每一层都是当前帧对应的金字塔
    for frame in frames:
        single_img_pyramid = build_laplacian_pyr(frame, maxLeval)
        video_pyramid.append()
    
    # pyramid_video[pyr_leval] = all_frames
    for level in maxLeval:
        index_leval_all_frames = []
        for i in range(len(frames)):
            index_leval_all_frames.append(video_pyramid[i][leval])
        pyramid_video.append(np.asarray(index_leval_all_frames))

    return np.asarray(pyramid_video)

# reconstruct video from pyramid frames
def reconstruct_video_from_pyramid(pyramid_video):
    video_frames = []
    video_frames_num = pyramid_video[0].shape[0]
    for frame_index in video_frames_num:
        index_frame_pyrs = [] # index_frame_pyrs[frame_index] = [index_frame_pyramid]
        for pyr_leval in range(len(pyramid_video)):
            index_frame_pyrs.append([pyr_leval][frame_index])
        index_frame = restruct_from_laplac(index_frame_pyrs)
        video_frames.append(index_frame)
    
    return video_frames




# get video all frames
def get_all_frames(video_path):
    if not os.path.exists(video_path):
        return 
    vidcap = cv2.VideoCapture(video_path)
    success,image = vidcap.read()
    frames = []
    while success:
        new_img = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        frames.append(image)
        success,image = vidcap.read()
    
    return frames

def main():


if __name__ == '__main__':


from scipy.signal import butter, lfilter

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


def run():
    import numpy as np
    import matplotlib.pyplot as plt
    from scipy.signal import freqz

    # Sample rate and desired cutoff frequencies (in Hz).
    fs = 5000.0
    lowcut = 500.0
    highcut = 1250.0

    # Plot the frequency response for a few different orders.
    plt.figure(1)
    plt.clf()
    for order in [3, 6, 9]:
        b, a = butter_bandpass(lowcut, highcut, fs, order=order)
        w, h = freqz(b, a, worN=2000)
        plt.plot((fs * 0.5 / np.pi) * w, abs(h), label="order = %d" % order)

    plt.plot([0, 0.5 * fs], [np.sqrt(0.5), np.sqrt(0.5)],
             '--', label='sqrt(0.5)')
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('Gain')
    plt.grid(True)
    plt.legend(loc='best')

    # Filter a noisy signal.
    T = 0.05
    nsamples = T * fs
    t = np.linspace(0, T, nsamples, endpoint=False)
    a = 0.02
    f0 = 600.0
    x = 0.1 * np.sin(2 * np.pi * 1.2 * np.sqrt(t))
    x += 0.01 * np.cos(2 * np.pi * 312 * t + 0.1)
    x += a * np.cos(2 * np.pi * f0 * t + .11)
    x += 0.03 * np.cos(2 * np.pi * 2000 * t)
    plt.figure(2)
    plt.clf()
    plt.plot(t, x, label='Noisy signal')

    y = butter_bandpass_filter(x, lowcut, highcut, fs, order=6)
    plt.plot(t, y, label='Filtered signal (%g Hz)' % f0)
    plt.xlabel('time (seconds)')
    plt.hlines([-a, a], 0, T, linestyles='--')
    plt.grid(True)
    plt.axis('tight')
    plt.legend(loc='upper left')

    plt.show()


run()