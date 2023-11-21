import unittest
from traverse_tree import *

class TestTreeFunctions(unittest.TestCase):

    def set_samples(self):
        # Setting up sample trees to test with
        self.empty_tree = []
        self.simple_tree = [[], 1, []]  
        self.complex_tree = [[[], 2, []], 1, [[], 3, []]
        ]

    def test_is_leaf(self):

        self.assertTrue(is_leaf(self.simple_tree))
        self.assertFalse(is_leaf(self.complex_tree))

    def test_contains_key(self):

        self.assertFalse(contains_key(5, self.empty_tree))
        self.assertTrue(contains_key(1, self.simple_tree))
        self.assertTrue(contains_key(3, self.complex_tree))
        self.assertFalse(contains_key(4, self.complex_tree))

    def test_tree_size(self):

        self.assertEqual(tree_size(self.empty_tree), 0)
        self.assertEqual(tree_size(self.simple_tree), 1)
        self.assertEqual(tree_size(self.complex_tree), 3)

    def test_tree_depth(self):

        self.assertEqual(tree_depth(self.empty_tree), 0)
        self.assertEqual(tree_depth(self.simple_tree), 1)
        self.assertEqual(tree_depth(self.complex_tree), 2)

    def 