
def is_leaf(tree):
    """ Check if the tree structure contains just one leaf
    """

    if isinstance(tree, int):
        return True
    if not tree[0] and not tree[2]:
        return True
    else:
        return False


def traverse(tree, empty_tree_fn, leaf_fn, inner_node_fn):
    """ Go through given binary tree and execute given function
        corrosponding to the each node
    """

    if tree == []:
        return empty_tree_fn()
    elif is_leaf(tree):
        if isinstance(tree, int):
            key = tree
        else:
            key = tree[1]
        return leaf_fn(key)
    else:
        lval, rval = 0, 0
        if tree[0]:
            lval = traverse(tree[0], empty_tree_fn, leaf_fn, inner_node_fn)
        if tree[2]:
            rval = traverse(tree[2], empty_tree_fn, leaf_fn, inner_node_fn)
        return inner_node_fn(lval, tree[1], rval)


def contains_key(key, tree):
    """ Check if a value (key) is present in the binary tree
    """

    def node_is_empty():
        return False

    def node_is_leaf(val):
        if val == key:
            return True
        else:
            return False

    def node_is_inner(lval, mval, rval):
        if mval == key:
            return True
        elif lval or rval:
            return True
        else:
            return False

    return traverse(tree, node_is_empty, node_is_leaf, node_is_inner)


def tree_size(tree):
    """ Calculate the total number of nodes in a given binary tree
    """

    def node_is_empty():
        return 0

    def node_is_leaf(val):
        return 1

    def node_is_inner(lval, mval, rval):
        return lval + rval + 1

    return traverse(tree, node_is_empty, node_is_leaf, node_is_inner)


def tree_depth(tree):
    """Find the maximum depth of the given binary tree
    """

    def node_is_empty():
        return 0

    def node_is_leaf(val):
        return 1

    def node_is_inner(lval, mval, rval):
        return max(lval, rval) + 1

    return traverse(tree, node_is_empty, node_is_leaf, node_is_inner)
