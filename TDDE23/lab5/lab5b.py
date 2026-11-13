import cv2
import numpy
rom cvlib import *
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

def generator_from_image(image_list):
    """
    Creates a function that, given an index, returns the bgr value
    in the pixel that the index refers to.

    Input:
    Python list with bgr values for an image

    Output:
    A function that takes an index and returns the bgr value for the specific
    pixel at the index
    """

    def generator(index):
        if 0 > index or index >= len(image_list):
            raise IndexError
        return image_list[index]

    return generator

def test_generator_from_image():
    
    orig_img = cv2.imread("Labbar\plane.jpg")
    orig_list = cvimg_to_list(orig_img)

    generator = generator_from_image(orig_list)

    new_list = [generator(i) for i in range(len(orig_list))]

    cv2.imshow('original', orig_img)
    cv2.imshow('new', rgblist_to_cvimg(new_list, orig_img.shape[0], orig_img.shape[1]))
    cv2.waitKey(0)

def combine_images(hsvlist, condition, generator1, generator2):
    
    """
    Combine two images based on a condition

    Parameters:
    - hsvlist: List of hsv pixel values.
    - condition: Function to determine which generator function to use per pixel.
    - generator1: Generates pixel values for image.
    - generator2: -||-

    Returns:
    - List of bgr pixel values for the combined image.
    """
    result_list = []
    try:
        for i in range(len(hsvlist)):
            if condition(hsvlist[i]) == 1:
                result_list.append(generator1(i))
            elif condition(hsvlist[i]) == 0:
                result_list.append(generator2(i))
            else:
                result_list.append(tuple(int(generator1(i)[rgb] * condition(hsvlist[i])
                                    + generator2(i)[rgb] * (1-condition(hsvlist[i])))
                                    for rgb in range(3)))
    except ValueError:
             raise ValueError
    except IndexError:
             raise IndexError
    
    return result_list
    # try:
    #     return [
    #     tuple(
    #         int(generator1(i)[rgb] * condition(hsvlist[i])
    #         + generator2(i)[rgb] * (1-condition(hsvlist[i])))
    #     for rgb in range(3))
    #     for i in range(len(hsvlist))
    #     ]
    # except IndexError:
    #         raise IndexError
    # except ValueError:
    #         raise ValueError

def test1_combine_images():
    # Läs in en bild
    plane_img = cv2.imread("Labbar/plane.jpg")

    # Skapa ett filter som identifierar himlen
    condition = pixel_constraint(100, 150, 50, 200, 100, 255)

    # Omvandla originalbilden till en lista med HSV-färger
    hsv_list = cvimg_to_list(cv2.cvtColor(plane_img, cv2.COLOR_BGR2HSV))
    plane_img_list = cvimg_to_list(plane_img)

    # Skapa en generator som gör en stjärnhimmel
    def generator1(index):
        val = random.random() * 255 if random.random() > 0.99 else 0
        return (val, val, val)

    # Skapa en generator för den inlästa bilden
    generator2 = generator_from_image(plane_img_list)

    # Kombinera de två bilderna till en, alltså använd himmelsfiltret som mask
    result = combine_images(hsv_list, condition, generator1, generator2)

    # Omvandla resultatet till en riktig bild och visa upp den
    new_img = rgblist_to_cvimg(result, plane_img.shape[0], plane_img.shape[1])
    cv2.imshow('Final image', new_img)
    cv2.waitKey(0)

def gradient_condition(pixel):
    try:
        return sum(pixel) / 3.0 / 255.0
    except TypeError:
        raise TypeError
    
def test2_combine_images():
    # Läs in bilderna
    flower_img = cv2.imread("Labbar/flowers.jpg")
    plane_img = cv2.imread("Labbar/plane.jpg")
    gradient_img = cv2.imread("Labbar/gradient.jpg")

    # Omvandla bilderna till listor
    flower_list = cvimg_to_list(flower_img)
    plane_list = cvimg_to_list(plane_img)
    gradient_list = cvimg_to_list(gradient_img)

    generator_plane = generator_from_image(plane_list)
    generator_flower = generator_from_image(flower_list)

    # Kombinera bilderna med gradient_condition
    combined_result = combine_images(gradient_list, gradient_condition, generator_flower, generator_plane)

    # Omvandla resultatet till en riktig bild och visa upp den
    combined_img = rgblist_to_cvimg(combined_result, plane_img.shape[0], plane_img.shape[1])
    cv2.imshow('Combined image', combined_img)
    cv2.waitKey(0)


