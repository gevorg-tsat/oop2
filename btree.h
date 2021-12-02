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

    Node(const K &key, const V &value) {
        this->key = key;
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }

    bool add(const K &key, const V &value) {

        if (key > this->key) {
            if (this->right == nullptr) {
                Node<K, V> *temp = new Node<K, V>(key, value);
                this->right = temp;
                return true;
            } else
                return this->right->add(key, value);
        } else if (key != this->key) {
            if (this->left == nullptr) {
                Node<K, V> *temp = new Node<K, V>(key, value);
                this->left = temp;
                return true;
            } else
                return this->left->add(key, value);
        } else return false;

    }

    bool contains(const K &key) const {
        if (this == nullptr)
            return false;
        if (this->key == key)
            return true;
        if (key > this->key)
            return this->right->contains(key);
        return this->left->contains(key);
    }

    void printTree() const {
        if (this != nullptr) {
            this->left->printTree();
            std::cout << "Key: " << this->key << " " << "Value: " << this->value << std::endl;
            this->right->printTree();
        }
    }
    V& searchValue(const K &key) {
        if (this == nullptr) {
            throw std::exception();
        }
        if (key == this->key) {
            return this->value;
        }
        if (key > this->key) {
            return this->right->searchValue(key);
        }
        return this->left->searchValue( key);
    }
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
    void add(const K& key, const V& value);
    void remove(const K& key);
    bool contains(const K& key) const;
    V& getValue(const K& key) const;
    V& operator[](const K& key) const;
    std::vector<V> getValues() const;
    std::vector<K> getKeys() const;
    void printTree() const;
private:
    Node<K,V>* root;
    int treeSize;
    Node<K, V>* remove(Node<K, V> *root, const K &key);
    void clearTree(Node<K,V> *node);
    Node<K,V>* findMin(Node<K,V>* node) const;
    void getValues(std::vector<V> &values, Node<K, V> *node) const;
    void getKeys(std::vector<K> &keys, Node<K, V> *node) const;
};
template<class K, class V>
bool operator==(const Tree<K,V> &first, const Tree<K,V> &second) {
    if (first.size() != second.size()) {
        return false;
    }
    if (first.size() == 0 && second.size() == 0) {
        return true;
    }
    std::vector<K> firstKeys = first.getKeys();
    for (auto key : firstKeys) {
        if (first[key] != second[key]) {
            return false;
        }
    }
    return true;
}

#include "btree.inl"
#endif //OOP_LABA2_BTREE_H
