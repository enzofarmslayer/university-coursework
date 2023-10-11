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


