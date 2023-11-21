import unittest
from search import search
from books import db

class TestSearchFunction(unittest.TestCase):

    def test_search_match(self):

        double_match_pattern = [['författare', ['&', 'zelle']], ['titel', 
            ['--', 'python', '--']], ['år', '&']]
        
        result = search(double_match_pattern, db)
        self.assertEqual(len(result), 2)

        single_match_pattern = [['författare', ['--', 'brookshear']], ['titel', 
            ['--', 'overview', '--']], ['år', '&']]
        
        result = search(single_match_pattern, db)
        self.assertEqual(len(result), 1)
    
    def test_search_no_match(self):

        no_match_pattern1 = [['författare', ['&', 'nonexistent']], ['titel', 
            ['--', 'python', '--']], ['år', '&']]
        
        result = search(no_match_pattern1, db)
        self.assertEqual(len(result), 0)  
    
        no_field_pattern2 = [['publisher', ['&', 'nonexistent']]]
        result = search(no_field_pattern2, db)
        self.assertEqual(len(result), 0)

    def test_search_empty_pattern(self):

        empty_pattern = []
        result = search(empty_pattern, db)
        self.assertEqual(len(result), 0)

    def test_search_unspecified_pattern(self):

        empty_pattern = ['--']
        result = search(empty_pattern, db)
        self.assertEqual(len(result), len(db))

    def test_search_invalid_type(self):
        
        with self.assertRaises(TypeError):
            int_pattern = 3
            search(int_pattern, db)

            string_pattern = "hej"
            search(string_pattern, db)

            tuple_pattern = (['författare', ['&', 'zelle']], ['titel', 
                ['--', 'python', '--']], ['år', '&'])
            search(tuple_pattern, db)


class TestSearchFunction(unittest.TestCase):

    def test_search_match(self):

        double_match_pattern = [['författare', ['&', 'zelle']], ['titel', 
            ['--', 'python', '--']], ['år', '&']]
        
        result = search(double_match_pattern, db)
        self.assertEqual(len(result), 2)

        single_match_pattern = [['författare', ['--', 'brookshear']], ['titel', 
            ['--', 'overview', '--']], ['år', '&']]
        
        result = search(single_match_pattern, db)
        self.assertEqual(len(result), 1)
    
    def test_search_no_match(self):

        no_match_pattern1 = [['författare', ['&', 'nonexistent']], ['titel', 
            ['--', 'python', '--']], ['år', '&']]
        
        result = search(no_match_pattern1, db)
        self.assertEqual(len(result), 0)  
    
        no_field_pattern2 = [['publisher', ['&', 'nonexistent']]]
        result = search(no_field_pattern2, db)
        self.assertEqual(len(result), 0)

    def test_search_empty_pattern(self):

        empty_pattern = []
        result = search(empty_pattern, db)
        self.assertEqual(len(result), 0)

    def test_search_unspecified_pattern(self):

        empty_pattern = ['--']
        result = search(empty_pattern, db)
        self.assertEqual(len(result), len(db))


    def test_search_invalid_type(self):
        
        with self.assertRaises(TypeError):
            int_pattern = 3
            search(int_pattern, db)

            string_pattern = "hej"
            search(string_pattern, db)

            tuple_pattern = (['författare', ['&', 'zelle']], ['titel', 
                ['--', 'python', '--']], ['år', '&'])
            search(tuple_pattern, db)
