#include <iostream>
#include "btree.h"
#include <assert.h>
int main() {
    Tree<int, int> tree;
    assert(tree.size()==0);
    std::cout << "Creating test passed" << std::endl;
    tree.add(2,3);
    tree.add(2,3);
    assert(tree.contains(2));
    assert(tree.size()==1);
    assert(tree[2] == 3);
    std::cout << "Adding and containing test passed" << std::endl;
    tree.toFile("done.txt");
    Tree<int,int> tree2;
    tree2.fromFile("done.txt");
    assert(tree==tree2);
    std::cout << "File test passed" << std::endl;
    tree.clearTree();
    assert(!(tree.contains(2)));
    Tree<int,int> tree1;
    assert(tree == tree1);
    std::cout << "Clearing test passed" << std::endl;
    tree.add(3,4);
    tree.remove(3);
    assert(!(tree.contains(3)));
    assert(tree == tree1);
    tree.add(5,6);
    Tree<int,int> tree3(tree);
    assert(tree3==tree);

    return 0;
}
