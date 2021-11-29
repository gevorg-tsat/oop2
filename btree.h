//
// Created by Gevorg Tsaturyan on 29.11.2021.
//

#ifndef OOP_LABA2_BTREE_H
#define OOP_LABA2_BTREE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
template<class K, class V> struct Node {
    K key;
    V value;
    Node<K, V> *left;
    Node<K, V> *right;
};
template<class K, class V>
class Tree {
public:
    Tree();
    Tree(const Tree<K,V>& parent);
    ~Tree();
    void clearTree();
    int size() const;
    void toFile(const std::string& path) const;
    void fromFile(const std::string& path);
    bool operator==(const Tree<K,V> &second) const;
    void add(const K& key, const V& value);
    void remove(const K& key) const;
    bool contains(const K& key) const;
    V& getValue(const K& key) const;
    V& operator[](const K& key);
    std::vector<V> getValues() const;
    std::vector<K> getKeys() const;
    void printTree() const;
private:
    Node<K,V>* root;
    int treeSize;
    void add(Node<K,V> **node, const K& key, const V& value);
    Node<K, V>* remove(Node<K, V> *root, const K &key);
    void printTree(Node<K,V> *node) const;
    bool contains(Node<K,V> *node, const K& key) const;
    void clearTree(Node<K,V> *node);
    V& searchValue(Node<K,V> *node, const K& key) const;
    Node<K,V>* findMin(Node<K,V>* node) const;
    void getValues(std::vector<V> &values, Node<K, V> *node) const;
    void getKeys(std::vector<K> &keys, Node<K, V> *node) const;

};

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
int Tree<K, V>::size() const {
    return this->treeSize;
}
template<class K, class V>
void Tree<K, V>::toFile(const std::string &path) const {
    std::vector<K> keys = getKeys();
    std::vector<V> values = getValues();
    std::ofstream f(path);
    if (!f) {
        throw std::runtime_error("Couldn't open file");
    }
    for (int i = 0; i < size(); ++i) {
        f << keys[i] << ":" << values[i] << std::endl;
    }
}
template<class K, class V>
void Tree<K, V>::fromFile(const std::string &path) {
    clearTree();
    std::ifstream f(path);
    if (!f.is_open()) {
        throw std::runtime_error("Couldn't open file");
    }
    for (std::string line; std::getline(f, line); ) {
        K key;
        V value;
        std::string token;
        std::stringstream ss (line);
        std::getline(ss, token, ':');
        std::stringstream converter (token);
        converter >> key;
        converter.clear();
        std::getline(ss, token);
        converter.str(token);
        converter >> value;
        add(key, value);
    }
}
template<class K, class V>
bool Tree<K,V>::operator==(const Tree<K,V> &second) const{
    if (this->size() != second.size()) {
        return false;
    }
    if (this->size() == 0 && second.size() == 0) {
        return true;
    }
    std::vector<K> firstKeys = this->getKeys();
    for (auto key : firstKeys) {
        if (this[key] != second[key]) {
            return false;
        }
    }
    return true;
}
template<class K, class V>
void Tree<K, V>::add(const K &key, const V &value) {
    add(&(this->root),key,value);
}
template<class K, class V>
void Tree<K, V>::add(Node<K, V> **node, const K &key, const V &value) {
    if (*node == nullptr) {
        Node<K, V> *temp = new Node<K, V>;
        temp->key = key;
        temp->value = value;
        temp->left = nullptr;
        temp->right = nullptr;
        *node = temp;
        this->treeSize++;
    } else {
        if (key > (*node)->key) {
            add(&(*node)->right, key, value);
        } else if (key != (*node)->key){
            add(&(*node)->left, key, value);
        }
    }
}
template<class K, class V>
void Tree<K,V>::remove(const K &key) const {
    remove(this->root,key);
}
template<class K, class V>
Node<K, V> * Tree<K,V>::remove(Node<K, V>*root, const K &key) {
    if (root == nullptr) {
        return root;
    }
    else if (key < root->key) {
        root->left = remove(root->left, key);
    }
    else if (key > root->key) {
        root->right = remove(root->right, key);
    }
    else { //found
        // No child
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
            this->treeSize--;
        }
            // One child
        else if (root->left == nullptr) {
            Node<K, V> *temporary = root;
            root = root->right;
            delete temporary;
            this->treeSize--;
        }
        else if (root->right == nullptr) {
            Node<K, V> *temporary = root;
            root = root->left;
            delete temporary;
            this->treeSize--;
        }
            // Two children
        else {
            Node<K, V> *temporary = findMin(root->right);
            root->key = temporary->key;
            root->value = temporary->value;
            root->right = remove(root->right, key);
        }
    }
    return root;
}
template<class K, class V>
bool Tree<K, V>::contains(const K &key) const {
    return contains(this->root);
}
template<class K, class V>
bool Tree<K,V>::contains(Node<K, V> *node, const K &key) const {
    if (node->key == nullptr)
        return false;
    if (node -> key == key)
        return true;
    if (key > node->key)
        return contains(node->right, key);
    return contains(node->left, key);
}
template<class K, class V>
void Tree<K, V>::printTree() const {
    printTree(this->root);
}
template<class K, class V>
void Tree<K, V>::printTree(Node<K, V> *node) const {
    if (node != nullptr) {
        print_in_order(node->left);
        std::cout << "Key: " << node->key << " " << "Value: " << node->value << std::endl;
        printTree(node->right);
    }
}
template<class K, class V>
V &Tree<K, V>::searchValue(Node<K, V> *node, const K &key) const {
    if (node == nullptr) {
        throw std::exception();
    }
    if (key == node->key) {
        return node->value;
    }
    if (key > node->key) {
        return search_node(node->right, key);
    }
    return search_node(node->left, key);
}
template<class K, class V>
V& Tree<K, V>::getValue(const K &key) const {
    if (this->contains(key)) {
        return searchValue(this->root, key);
    }
    throw std::runtime_error("No such key in map");
}
template<class K, class V>
V& Tree<K, V>::operator[](const K& key) {
    return this->getValue(key);
}
template<class K, class V>
void Tree<K, V>::getValues(std::vector<V> &values, Node<K, V> *node) const {
    if (node != nullptr) {
        getValues(values, node->left);
        values.push_back(node->value);
        getValues(values, node->right);
    }
}
template<class K, class V>
std::vector<V> Tree<K, V>::getValues() const {
    std::vector<V> values;
    getValues(values, this->root);
    return values;
}
template<class K, class V>
void Tree<K, V>::getKeys(std::vector<K> &keys, Node<K, V> *node) const {
    if (node != nullptr) {
        get_keys(keys, node->left);
        keys.push_back(node->key);
        get_keys(keys, node->right);
    }
}

template<class K, class V>
std::vector<K> Tree<K, V>::getKeys() const {
    std::vector<K> keys;
    get_keys(keys, this->root);
    return keys;
}
template<class K, class V>
Node<K, V>* Tree<K, V>::findMin(Node<K, V> *node) const{
    while(node->left != nullptr){
        node = node->left;
    }
    return node;
}
#endif //OOP_LABA2_BTREE_H
