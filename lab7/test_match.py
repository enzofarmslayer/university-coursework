import unittest
from match import *

class TestMatch(unittest.TestCase):

    def test_empty_pattern(self):
        self.assertTrue(match([], []))
        
    def test_exact_match(self):
        self.assertTrue(match(['a', 'b', 'c'], ['a', 'b', 'c']))
        
    def test_wildcard_match_single(self):
        self.assertTrue(match(['a', 'b', 'c'], ['a', '&', 'c']))
        
    def test_wildcard_match_multiple(self):
        self.assertTrue(match(['a', 'b', 'c'], ['--', 'b', 'c']))
        
    def test_wildcard_no_match(self):
        self.assertFalse(match(['a', 'b', 'd'], ['--', 'b', 'c']))
        
    def test_nested_list_match(self):
        self.assertTrue(match([[['a']], 'b', 'c'], [[['a']], 'b', 'c']))
        
    def test_nested_list_no_match(self):
        self.assertFalse(match([[['c']], 'b', 'c'], [[['a']], 'b', 'c']))

class TestMatchFunctionTypeErrors(unittest.TestCase):
    
    def test_invalid_pattern_type(self):
        with self.assertRaises(TypeError):
            match(['a', 'b', 'c'], 'abc')
            match(['a', 'b', 'c'], 3)
            match(['a', 'b', 'c'], ('a', 'b', 'c'))

    def test_invalid_seq_type(self):
        with self.assertRaises(TypeError):
            match('abc', ['a', 'b', 'c'])
            match(3, ['a', 'b', 'c'])
            match(('a', 'b', 'c'), ['a', 'b', 'c'])
            