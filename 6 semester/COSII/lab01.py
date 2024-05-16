import numpy as np
import matplotlib.pyplot as plt
import math

N = 16

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

def ABS(func):
    return [math.sqrt(element.real ** 2 + element.imag ** 2) for element in func]

def main():

    taskX = np.linspace(0, 2*np.pi, 100)
    taskY = np.sin(taskX) + np.cos(4*taskX)
    plot = plt.figure("Lab1 TASK")
    plot.suptitle('y = sin(x) + cos(4x)')
    plt.plot(taskX, taskY,color='green')

    figure = plt.figure('Lab1', figsize=[16, 10])
    slotsArray = figure.subplots(2, 4)

    x = np.linspace(0, 2*np.pi, N)
    y = (np.sin(x) + np.cos(4*x))

    manualFFT = FFT(y,N,1)
    manualFFT = BIR(manualFFT)

    manualIFFT = FFT(manualFFT,N,-1)/N
    manualIFFT = BIR(manualIFFT)

    libraryFFT = np.fft.fft(y,N)
    libraryIFFT = np.fft.ifft(libraryFFT,N)
    
    slotsArray[0,0].set_title('Прямое БПФ (ручное)')
    slotsArray[0,0].plot(x, ABS(manualFFT), color='green')

    slotsArray[1,0].set_title('Прямое БПФ (библиотека)')
    slotsArray[1,0].plot(x,np.abs(libraryFFT), color='green')

    slotsArray[0,1].set_title('Мнимая часть (ручное)')
    slotsArray[0,1].plot(x,np.imag(manualFFT), color='green')

    slotsArray[1,1].set_title('Мнимая часть (библиотека)')
    slotsArray[1,1].plot(x,np.imag(libraryFFT), color='green')

    slotsArray[0,2].set_title('Действительная часть(ручное)')
    slotsArray[0,2].plot(x,np.real(manualFFT), color='green')

    slotsArray[1,2].set_title('Действительная часть(библиотека)')
    slotsArray[1,2].plot(x,np.real(libraryFFT), color='green')

    slotsArray[0,3].set_title('Обратное БПФ (ручное)')
    slotsArray[0,3].plot(x, manualIFFT, color='green')

    slotsArray[1,3].set_title('Обратное БПФ (библиотека)')
    slotsArray[1,3].plot(x,libraryIFFT, color='green')

    plt.show()


if __name__=="__main__":
    main()
    