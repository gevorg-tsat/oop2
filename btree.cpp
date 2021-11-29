//
// Created by Gevorg Tsaturyan on 29.11.2021.
//

#include "btree.h"

template<class K, class V>
Tree<K,V>::Tree() {
    this->treeSize = 0;
    this->root = nullptr;
}
template<class K, class V>
Tree<K, V>::Tree(const Tree<K, V> &parent) {
    std::vector<K> keys = parent.getKeys();
    this->root = nullptr;
    this->treeSize = 0;
    for (auto key : keys) {
        this->add(key, parent[key]);
    }
}
template<class K, class V>
Tree<K,V>::~Tree(){
    this->clearTree();
}
template<class K, class V>
void Tree<K, V>::clearTree() {
    clearTree(this->root);
}
template<class K, class V>
void Tree<K, V>::clearTree(Node<K, V> *node) {
    if (node!= nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}
template<class K, class V>
bool Tree<K,V>::operator==(const Tree<K, V> &first, const Tree<K, V> &second) const{
    if (first.size() != second.size()) {
        return false;
    }
    if (first.size() == 0 && first.size() == 0) {
        return true;
    }
    std::vector<K> first_keys = first.get_keys();
    for (auto key : first_keys) {
        if (first[key] != second[key]) {
            return false;
        }
    }
    return true;
}