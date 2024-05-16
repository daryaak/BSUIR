import numpy as np
import matplotlib.pyplot as plt

def dwt53(array):
    
    array = np.copy(array)
    n = array.size

    detailSize = n // 2
    approxSize = n - detailSize

    for i in range(detailSize):

        prediction = (array[i * 2] + array[min((i * 2) + 2, (approxSize - 1) * 2)]) / 2
        array[(i * 2) + 1] -= prediction
    
    for i in range(approxSize):

        update = (array[max((i * 2) - 1, 1)] + array[min((i * 2) + 1, ((detailSize - 1) * 2) + 1)]) / 4
        array[i * 2] += update

    return array

def idwt53(array):

    array = np.copy(array)
    n = array.size

    detailSize = n // 2
    approxSize = n - detailSize
    
    for i in range(approxSize):

        update = (array[max((i * 2) - 1, 1)] + array[min((i * 2) + 1, ((detailSize - 1) * 2) + 1)]) / 4
        array[i * 2] -= update

    for i in range(detailSize):

        predict = (array[i * 2] + array[min((i * 2) + 2, (approxSize - 1) * 2)]) / 2
        array[(i * 2) + 1] += predict
    
    return array

def myInsert(destination, values):

    for i in range(len(values)):
        destination = np.insert(destination, 2*i+1, values[i])

    return destination

def main():

    N = 64
    x = np.linspace(0, 2*np.pi, N)
    y = np.sin(x)+np.cos(4*x)

    figure = plt.figure('Lab4', figsize=[16, 10])
    figure.set_facecolor('wheat')

    plt.subplot(3, 3, 1)
    plt.title('Исходный сигнал:')
    plt.plot(y,color='indigo')

    step1 = dwt53(y)
    size1 = N//2
    plt.subplot(3, 3, 2)
    plt.title('H0:')
    plt.stem(range(size1),step1[1::2],linefmt='saddlebrown')

    step2 = dwt53(step1[0::2])
    size2 = size1//2
    plt.subplot(3, 3, 3)
    plt.title('H1:')
    plt.stem(range(size2),step2[1::2],linefmt='saddlebrown')

    step3 = dwt53(step2[0::2])
    size3 = size2//2
    plt.subplot(3, 3, 4)
    plt.title('H2:')
    plt.stem(range(size3),step3[1::2],linefmt='saddlebrown')    

    step4 = dwt53(step3[0::2])
    size4 = size3//2
    plt.subplot(3, 3, 5)
    plt.title('H3:')
    plt.stem(range(size4),step4[1::2],linefmt='saddlebrown')

    step5 = dwt53(step4[0::2])
    size5 = size4//2
    plt.subplot(3, 3, 6)
    plt.title('H4:')
    plt.stem(range(size5),step5[1::2],linefmt='saddlebrown')

    step6 = dwt53(step5[0::2])
    size6 = size5//2
    plt.subplot(3, 3, 7)
    plt.title('H5:')
    plt.stem(range(size6),step6[1::2],linefmt='saddlebrown')    

    plt.subplot(3, 3, 8)
    plt.title('L:')
    plt.stem(range(size6),step6[0::2],linefmt='darkolivegreen')      

    step6Reverse = idwt53(step6)

    step6Reverse = myInsert(step6Reverse,step5[1::2])
    step5Reverse = idwt53(step6Reverse)

    step5Reverse = myInsert(step5Reverse,step4[1::2])
    step4Reverse = idwt53(step5Reverse)

    step4Reverse = myInsert(step4Reverse,step3[1::2])
    step3Reverse = idwt53(step4Reverse)

    step3Reverse = myInsert(step3Reverse ,step2[1::2])
    step2Reverse = idwt53(step3Reverse)

    step2Reverse = myInsert(step2Reverse,step1[1::2])
    yReconstructed = idwt53(step2Reverse)

    plt.subplot(3, 3, 9)
    plt.title('Восстановленный сигнал:')
    plt.plot(yReconstructed,color='darkslateblue')
    
    plt.tight_layout()
    plt.show()

if __name__=="__main__":
    main()