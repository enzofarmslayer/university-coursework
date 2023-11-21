
def is_leaf(tree):
    if isinstance(tree, int): return True
    if not tree[0] and not tree[2]: return True
    else: return False

def traverse(tree, empty_tree_fn, leaf_fn, inner_node_fn, depth = 1):
    if tree == []: 
        empty_tree_fn()
    elif is_leaf(tree):
        if isinstance(tree, int): key = tree
        else: key = tree[1]
        leaf_fn(key, depth) 
    else:
        depth += 1
        inner_node_fn(tree[1])
        if tree[0]: traverse(tree[0], empty_tree_fn, leaf_fn, inner_node_fn, depth)
        if tree[2]: traverse(tree[2], empty_tree_fn, leaf_fn, inner_node_fn, depth)

def contains_key(key, tree):
    found = False

    def node_is_empty():
        return False

    def node_is_leaf(val, d):
        nonlocal found
        if val == key: found = True

    def node_is_inner(val):
        nonlocal found 
        if val == key: found = True

    traverse(tree, node_is_empty, node_is_leaf, node_is_inner)
    return found


def tree_size(tree):
    size = 0

    def node_is_empty():
        return False

    def node_is_leaf(val, d):
        nonlocal size
        size += 1

    def node_is_inner(val):
        nonlocal size
        size += 1        

    traverse(tree, node_is_empty, node_is_leaf, node_is_inner)
    return size


def tree_depth(tree):
    depth = 0

    def node_is_empty():
        pass
    
    def node_is_leaf(val, d):
        nonlocal depth
        depth = d

    def node_is_inner(val):
        pass

    traverse(tree, node_is_empty, node_is_leaf, node_is_inner)
    return depth

# ret = contains_key(2, [[], 1, 5])
# print(ret)
