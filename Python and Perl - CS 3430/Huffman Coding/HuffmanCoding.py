
def make_leaf(symbol, weight):
    return (symbol, weight)

def is_leaf(x):
    return isinstance(x, tuple) and \
            len(x) == 2 and \
            isinstance(x[0], str) and \
            isinstance(x[1], int)

def get_leaf_symbol(leaf):
    return leaf[0]

def get_leaf_freq(leaf):
    return leaf[1]

def get_left_branch(huff_tree):
    return huff_tree[0]

def get_right_branch(huff_tree):
    return huff_tree[1]

def get_symbols(huff_tree):
    if is_leaf(huff_tree):
        return [get_leaf_symbol(huff_tree)]
    else:
        return huff_tree[2]

def get_freq(huff_tree):
    if is_leaf(huff_tree):
        return get_leaf_freq(huff_tree)
    else:
        return huff_tree[3]

def make_huffman_tree(left_branch, right_branch):
    return [left_branch,
            right_branch,
            get_symbols(left_branch) + get_symbols(right_branch),
            get_freq(left_branch) + get_freq(right_branch)]

## leaves
E_1 = make_leaf('E', 1)
F_1 = make_leaf('F', 1)

G_1 = make_leaf('G', 1)
H_1 = make_leaf('H', 1)

C_1 = make_leaf('C', 1)
D_1 = make_leaf('D', 1)

B_3 = make_leaf('B', 3)
A_8 = make_leaf('A', 8)

EF_2 = make_huffman_tree(E_1, F_1)
GH_2 = make_huffman_tree(G_1, make_leaf('H', 1))
EFGH_4 = make_huffman_tree(EF_2, GH_2)

CD_2 = make_huffman_tree(C_1, D_1)
BCD_5 = make_huffman_tree(B_3, CD_2)

BCDEFGH_9 = make_huffman_tree(BCD_5, EFGH_4)

ABCDEFGH_17 = make_huffman_tree(A_8, BCDEFGH_9)

# print ABCDEFGH_17

####################################################################################################
# Jonathan Petersen
# A01236750
# Huffman Coding Assignment
# Encode and Decode Functions

def huffman_encode(symbols, huffman_tree) :

    path = [];

    for character in symbols :

        if character not in huffman_tree[2] :
            print "Could not find character " + character;
            return -1;

        current_tree = huffman_tree;

        while ( is_leaf(current_tree) == False ) :

            if character in get_symbols(current_tree[0]) :
                path.append(0);
                current_tree = current_tree[0];
                continue;

            if character in get_symbols(current_tree[1]) :
                path.append(1);
                current_tree = current_tree[1];
                continue;

            print "Could not find branch while searching for character " + character;
            return -2;

    return path;

def huffman_decode(bits, huffman_tree) :

    message = [];
    current_tree = huffman_tree;

    while ( len(bits) > 0 ) :

        index = bits.pop(0);

        if (index == 0) :
            current_tree = current_tree[0];

        if (index == 1) :
            current_tree = current_tree[1];

        if ( is_leaf(current_tree) ) :

            message.append(get_leaf_symbol(current_tree));
            current_tree = huffman_tree;
            continue;

        # print "Could not follow path. Remaining path is " + index + bits;
        # return -1;

    return message;

print huffman_encode(["A", "B", "B", "A"], ABCDEFGH_17);
print huffman_decode([1, 0, 0, 0, 1, 0, 1, 0], ABCDEFGH_17);

print huffman_decode(huffman_encode(["H", "A", "D", "A", "B", "A", "D"], ABCDEFGH_17), ABCDEFGH_17);
print huffman_encode(huffman_decode([0, 1, 0, 0, 1, 0, 0, 0], ABCDEFGH_17), ABCDEFGH_17);

####################################################################################################
