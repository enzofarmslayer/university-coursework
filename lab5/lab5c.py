from Uppgift5B1 import pixel_constraint
from Uppgift5B2 import generator_from_image
from Uppgift5B4 import combine_images 
from Uppgift5B4 import gradient_condition

def test_pixel_constraint():
    
    # Set up an example constraint for HSV values within the range 0-100
    test_check_pixel = pixel_constraint(0, 100, 0, 100, 0, 100)

    # Basecase
    assert test_check_pixel((50, 50, 50)) == 1\
        , print("Test Failed: Pixel inside constraint not regcognized") 

    # Edgecases within constraint
    assert test_check_pixel((100, 100, 100)) == 1\
        , print("Test Failed: Pixel within upper bounds in constraint not regcognized")
    assert test_check_pixel((0, 0, 0)) == 1\
        , print("Test Failed: Pixel within lower bounds in constraint not regcognized")

    # Edgecases outside constraint
    assert test_check_pixel((101, 50, 50)) == 0\
        , print("Test Failed: Pixel outside upper hue constraint not regcognized")
    assert test_check_pixel((50, -1, 50)) == 0\
        , print("Test Failed: Pixel outside lower saturation constraint not recognized") 
    
    print("pixel_constraint passed all test cases")

    # Test to check if invalid data-types for input are raising correct exceptions
    try:
        test_check_pixel("string_input")
        print("Test Failed: string input")
    except TypeError:
        print("Correctly caught TypeError in pixel_constaint")
    except Exception:
        print("Did not catch right exception")
        
    # Test to check if incorrect length of input raises the correct exception
    try:
        test_check_pixel((50, 50))
        print("Test Failed: ValueError was not raised for input of incorrect length")
    except ValueError:
        print("Correctly caught ValueError in pixel_constraint")
    except Exception:
        print("Did not catch right exception")
    
def test_generator_from_image():
    
    # Setting up an example generator using a made up picture of 3 pixels
    test_generator = generator_from_image([(255, 0, 0), (0, 255, 0), (0, 0, 255)]) 

    # Test that the generator produces the correct RGB pixel for given index
    assert test_generator(0) == (255, 0, 0)\
        , print("Test Failed: Generated wrong pixel for index 0")
    assert test_generator(1) == (0, 255, 0)\
        , print("Test Failed: Generated wrong pixel for index 1")
    assert test_generator(2) == (0, 0, 255)\
        , print("Test Failed: Generated wrong pixel for index 2")
    
    print("generator_from_image passed all test cases")

    # Tests to see if given an index oustide of the picture's range raises correct exception
    try:
        test_generator(3)
        print("Did not catch an exception")
    except IndexError:
        print("Correctly caught IndexError in generator_from_image")
    except Exception:
        print("Did not catch right exception")

def test_combine_images():
    
    # Setting up two pixel generators from two made up images with 3 pixels each 
    generator1 = generator_from_image([(200, 100, 150), (10, 20, 30), (10, 20, 30)])
    generator2 = generator_from_image([(50, 150, 250), (30, 40, 50), (30, 40, 50)])
    # Example gradient image that goes from white to black
    gradient_image = [(255, 255, 255), (127,127,127), (0, 0, 0)] 
    
    # The expected result after combining the images
    expected_result = [(200, 100, 150), (20,30,40), (30, 40, 50)]

    # Test if the combined image matches the expected result
    test_result = combine_images(gradient_image, gradient_condition, generator1, generator2)
    assert test_result == expected_result, f"Test Failed: Expected {expected_result}, but got {test_result}"
    
    print("test_combine_images passed all test cases")

    # Testing with faulty input functions to ensure correct exceptions are raised
    faulty_gradient_image1 = [(255, 255, 255), ("127",127,127), (0, 0, 0)]
    try:
        combine_images(faulty_gradient_image1, gradient_condition, generator1, generator2)
        print("Did not catch an exception")
    except TypeError:
        print("Correctly caught TypeError in combine_images.")
    except Exception:
        print("Did not catch right exception")
    
    faulty_gradient_image2 = [(255, 255, 255), (127,127,127), (0, 0, 0), (0, 0, 0)]
    try:
        combine_images(faulty_gradient_image2, gradient_condition, generator1, generator2)
        print("Did not catch an exception")
    except IndexError:
        print("Correctly caught IndexError in combine_images.")
    except Exception:
        print("Did not catch right exception")
      
    faulty_gradient_image3 = [(255, 255, 255), (127,127,127), (0, 0, 0, 0)]
    try:
        combine_images(faulty_gradient_image3, gradient_condition, generator1, generator2)
        print("Did not catch an exception")
    except ValueError:
        print("Correctly caught ValueError in combine_images.")
    except Exception:
        print("Did not catch right exception")
   
    faulty_generator = generator_from_image([(0,0,0)])
    try:
        combine_images(gradient_image, gradient_condition, generator1, faulty_generator)
        print("Did not catch an exception")
    except IndexError:
        print("Correctly caught IndexError in combine_images.")
    except Exception:
        print("Did not catch right exception")

def test_error_message():
    
    test_check_pixel = pixel_constraint(0, 100, 0, 100, 0, 100)
    #test_check_pixel("string_input") #TypeError1
    
    test_generator = generator_from_image([(255, 0, 0), (0, 255, 0), (0, 0, 255)]) 
    #test_generator(3) #IndexError

    generator1 = generator_from_image([(200, 100, 150), (10, 20, 30), (10, 20, 30)])
    generator2 = generator_from_image([(50, 150, 250), (30, 40, 50), (30, 40, 50)])
    faulty_gradient_image4 = [(255, 255, 255), (127,127,127), (0, 0, 0, 0)]
    #combine_images(faulty_gradient_image4, gradient_condition, generator1, generator2) #valueError

test_pixel_constraint()
test_generator_from_image()
test_combine_images()
test_error_message()
