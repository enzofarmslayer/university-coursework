def is_leaf(tree):
    if isinstance(tree, int): return True
    if not tree[0] and not tree[2]: return True
    else: return False

def traverse(tree, empty_tree_fn, leaf_fn, inner_node_fn):
    if is_leaf(tree):
        if isinstance(tree, int): key = tree
        else: key = tree[1]
        leaf_fn(key) 

    elif tree[1] == []: 
        empty_tree_fn()
    else:
        inner_node_fn(tree[1])
        if tree[0]: traverse(tree[0], empty_tree_fn, leaf_fn, inner_node_fn)
        if tree[2]: traverse(tree[2], empty_tree_fn, leaf_fn, inner_node_fn)

def contains_key(key, tree):
    found = False

    def node_is_empty():
        return False

    def node_is_leaf(val):
        nonlocal found
        if val == key: found = True

    def node_is_inner(val):
        nonlocal found 
        if val == key: found = True

    traverse(tree, node_is_empty, node_is_leaf, node_is_inner)
    return found


ret = contains_key(5, [6, 7, 8])
print(ret)

