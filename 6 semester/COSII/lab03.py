import numpy as np
from PIL import Image
from numpy import pi
from scipy import signal
import matplotlib.pyplot as plt
import math

N =128

def hamming_window(n):
    return 0.54 - 0.46 * np.cos(2 * pi * np.arange(n) / n)

def lowPassFilter(num, freq):
    taps = np.sinc(2 * freq * (np.arange(num) - (num - 1) / 2)) * hamming_window(num) 
    taps /= np.sum(taps)
    return taps

def main():

    x = np.linspace(0, 2*np.pi, N)
    y = np.sin(x) + np.cos(4*x)

    noise =np.cos(100*x)

    y_noise = y + noise

    srez_freq = 0.039

    h = lowPassFilter(N,srez_freq)

    figure = plt.figure('Lab3', figsize=[16, 10])
    figure.set_facecolor('wheat')
    slotsArray = figure.subplots(2, 3)

    slotsArray[0,0].set_title('Исходный график')
    slotsArray[0,0].plot(x, y, color='saddlebrown')

    slotsArray[0,1].set_title('Шум')
    slotsArray[0,1].plot(x, noise, color='saddlebrown')

    slotsArray[0,2].set_title('Исходный график с шумом')
    slotsArray[0,2].plot(x, y_noise, color='saddlebrown')

    slotsArray[1,0].set_title('График после использования фильтра')
    y_filtered = np.convolve(y_noise, lowPassFilter(N,srez_freq), mode='same')
    slotsArray[1,0].plot(x, y_filtered, color='saddlebrown')

    slotsArray[1,1].set_title('Импульсная характеристика фильтра')
    slotsArray[1,1].plot(x, h, color='saddlebrown')

    filter_fft = np.fft.fft(h)
    filter_magnitude = np.abs(filter_fft)
    filter_frequency = np.fft.fftfreq(N)
    filter_frequency_normalized = np.fft.fftshift(filter_frequency)

    x1 = x = np.linspace(0, srez_freq*2.0, N)
    slotsArray[1,2].set_title('АЧХ фильтра')
    y_filtered = np.convolve(y_noise, lowPassFilter(N,srez_freq), mode='same')
    slotsArray[1,2].plot(filter_frequency_normalized, np.fft.fftshift(filter_magnitude), color='saddlebrown')

    plt.show()

if __name__=="__main__":
    main()



