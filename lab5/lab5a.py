import cv2
from cvlib import rgblist_to_cvimg

def cvimg_to_list(img):
    """
    Konverterar en cv-lista med arrayer av bgr värden
    till en enkel python lista med bgr värden.
    
    Input: cv-img lista

    Output: Enkel python lista med bgr värden i form av tuples
    """    
    
    bgr_list = []
    
    for array in img:
        for pixel in array:
            b,g,r = pixel
            bgr_list.append((b,g,r)) 

    return bgr_list

   
def test_cvimg_to_list():
    img = cv2.imread("Labbar\WIN_20230925_16_50_32_Pro.jpg")
    list_img = cvimg_to_list(img)
        
    converted_img = rgblist_to_cvimg(list_img, img.shape[0], img.shape[1]) 
    cv2.imshow("converted", converted_img)
    cv2.waitKey(0)

import numpy as np

def unsharp_mask(N):
    """
    Räknar ut negativ gausisk blur för pixlar runt origo i en NxN array
    där origo tilldelas ett positivt värde, 
    
    Input:
    N: storleken på NxN array 

    Output:
    returnerar en NxN array med gausisk blur värden. 
    """
    s = 4.5
    
    def calculate_value(x, y):
        if x == N//2 and y == N//2:
            return 1.5
        else:
            return (-1 / (2 * np.pi * s**2)) * np.exp(-(x**2 + y**2) / (2 * s**2))
    
    rader = [[calculate_value(x, y) for y in range(N)] for x in range(N)]
    return rader

#Test för unsharp_mask
def test1_unsharp_mask(N):
    print(unsharp_mask(N))

def test2_unsharp_mask():
    # Ladda in bilden med OpenCV
    img = cv2.imread('plane.jpg')

    # Generera unsharp mask kernel
    N = 11
    kernel = np.array(unsharp_mask(N))

    # Applicera kernel på bilden
    filtered_img = cv2.filter2D(img, -1, kernel)

    # Visa den skarpade bilden
    cv2.imshow("filtered", filtered_img)
    cv2.waitKey(0)

test2_unsharp_mask()
