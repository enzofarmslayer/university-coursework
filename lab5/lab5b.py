import cv2
import numpy
from cvlib import greyscale_list_to_cvimg
from Uppgift5A1 import cvimg_to_list

def pixel_constraint(hlow, hhigh, slow, shigh, vlow, vhigh):
    
    """
    Creates a function to limit HSV values and creates a
    function that checks if a pixel is within the specified limitations.

    Parameters:
    Highest and lowest limitation for each hsv value (int)

    Returns:
    A function that checks if a pixel is within the specified limitations.
    """
    
    def check_pixel(pixel):
        
        """
        Checks if a pixel is within the specified limitations.

        Parameters:
        A tuple representing the hsv values of a pixel.

        Returns:
        1 - If the pixel is within the limitations.
        0 - If the pixel is outside the limitations.
        """
        if not isinstance(pixel, tuple):
            raise TypeError
        if len(pixel) != 3:
            raise ValueError
        if not (isinstance(rgb, int) for rgb in pixel):
            raise TypeError

        h, s, v = pixel
        
        if hlow <= h <= hhigh and \
            slow <= s <= shigh and vlow <= v <= vhigh:
            return 1
        else:
            return 0
    
    return check_pixel

def test_pixelconstaint():
    is_black = pixel_constraint(0, 255, 0, 255, 0, 10)
    print(is_black((231, 82, 4)))    # Resultat: 1
    print(is_black((231, 72, 199)))  # Resultat: 0

    hsv_plane = cv2.cvtColor(cv2.imread("Labbar\plane.jpg"), cv2.COLOR_BGR2HSV)
    plane_list = cvimg_to_list(hsv_plane)

    is_sky = pixel_constraint(100, 200, 50, 200, 100, 255)
    sky_pixels = list(map(lambda x: x * 255, map(is_sky, plane_list)))

    cv2.imshow('sky', greyscale_list_to_cvimg(sky_pixels, hsv_plane.shape[0], hsv_plane.shape[1]))
    cv2.waitKey(0)

