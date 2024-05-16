import numpy as np
import matplotlib.pyplot as plt
import math

N = 8

def functionY(x):
    return np.cos(2*x)

def functionZ(x):
    return np.sin(5*x)

def linearConvolution(y,z):
    result = [0] * (len(y) + len(z) - 1)
    for i in range(len(y)):
        for j in range(len(z)):
            result[i + j] += y[i] * z[j]

    return result

def circularConvolution(y, z):
    result = [0] * len(y)
    for i in range(len(y)):
        for j in range(len(y)):
            result[i] += y[j] * z[(i - j) % len(y)]

    return result

def FFTConvolution(y,z):
    yFFT = FFT(y,N,1)
    yFFT = BIR(yFFT)
    zFFT = FFT(z,N,1)
    zFFT = BIR(zFFT)
    yzFFT = multiplyFunctions(yFFT,zFFT)   
    yzIFFT = FFT(yzFFT,N,-1)/N
    yzIFFT = BIR(yzIFFT)
    result = yzIFFT
    return result

def multiplyFunctions(f, g):
    result = []
    for i in range(len(f)):
        result.append(f[i] * g[i])
    return result

def correlation(y, z):
    result = [0] * N
    for i in range(N):
        for j in range(N):
            if i + j >= N:
                continue
            result[i] += y[j] * z[i + j]

    return result

def FFT(a, N, dir):
    if N==1:
        return a
    w = 1
    wn = np.exp((dir * -2j * np.pi) / N)
    b = np.zeros(N//2, dtype = np.complex128)
    c = np.zeros(N//2, dtype = np.complex128)
    for j in range (N//2):
        b[j]=a[j]+a[j+N//2]
        c[j]=(a[j]-a[j+N//2])*w
        w = w * wn
    y1 = FFT(b,N//2,dir)
    y2 = FFT(c,N//2,dir)
    return np.concatenate((y1,y2))


def BIR(array):
    length = len(array)
    maxLen = math.ceil(math.log2(length))
    result = [None] * length  
    for i in range(length):
        binView = bin(i)[2:] 
        invertBin = binView.zfill(maxLen)
        invertBin = invertBin[::-1]  
        decimalView = int(invertBin, 2)  
        if decimalView < length:
            result[decimalView] = array[i] 
    return result

def main():
    x = np.linspace(0, 2*np.pi, 100)
    y = functionY(x)
    z = functionZ(x)

    figure = plt.figure('Lab2', figsize=[16, 10])
    figure.set_facecolor('wheat')
    slotsArray = figure.subplots(2, 4)

    slotsArray[0,0].set_title('y = cos(2x)')
    slotsArray[0,0].plot(x, y, color='saddlebrown')

    slotsArray[1,0].set_title('z = sin(5x)')
    slotsArray[1,0].plot(x,z, color = 'saddlebrown')

    slotsArray[0,1].set_title('Circular convolution(Man)')
    x = np.linspace(0, 2 * np.pi, N)
    y = functionY(x)
    z = functionZ(x)
    circularConvolution_ = circularConvolution(y,z)[:8]
    slotsArray[0,1].stem(range(N), circularConvolution_, linefmt='saddlebrown')

    slotsArray[0,2].set_title('FFT convolution(Man)')
    x = np.linspace(0, 2 * np.pi, N)
    y = functionY(x)
    z = functionZ(x)
    FFTConvolution_ = FFTConvolution(y,z)[:8]
    slotsArray[0,2].stem(range(N), FFTConvolution_, linefmt='saddlebrown')

    slotsArray[0,3].set_title('Linear convolution(Man)')
    x = np.linspace(0, 2 * np.pi, N)
    y = functionY(x)
    z = functionZ(x)
    linearConvolution_ = linearConvolution(y,z)[:15]
    slotsArray[0,3].stem(range(2*N-1),linearConvolution_, linefmt='saddlebrown')

    slotsArray[1,1].set_title('Convolution(Lib)')
    x = np.linspace(0, 2 * np.pi, N)
    y = functionY(x)
    z = functionZ(x)
    convolutionLibrary = np.convolve(y, z)[:15]
    slotsArray[1,1].stem(range(2*N-1), convolutionLibrary, linefmt='saddlebrown')

    slotsArray[1,2].set_title('Correlation(Man)')
    x = np.linspace(0, 2 * np.pi, N)
    y = functionY(x)
    z = functionZ(x)
    correlation_ = correlation(y,z)[:8]
    slotsArray[1,2].stem(range(N), correlation_, linefmt='saddlebrown')

    slotsArray[1,3].set_title('Correlation(Lib)')
    x = np.linspace(0, 2 * np.pi, N)
    y = functionY(x)
    z = functionZ(x)
    correlationLibrary = np.correlate(y, z, mode='full')[:N][::-1]
    slotsArray[1,3].stem(range(N), correlationLibrary, linefmt='saddlebrown')

    plt.show()

if __name__=="__main__":
    main()