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
    Node(const K& key, const V& value) {
        this->key = key;
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }
    bool add(const K& key, const V& value) {

            if (key > this->key) {
                if (this->right == nullptr) {
                    Node<K, V> *temp = new Node<K, V>(key, value);
                    this -> right = temp;
                    return true;
                }
                else
                    return this->right->add( key, value);
            } else if (key != this->key){
                if (this->left == nullptr) {
                    Node<K, V> *temp = new Node<K, V>(key, value);
                    this->left = temp;
                    return true;
                }
                else
                    return this->left->add( key, value);
            }
            else return false;

    }
    bool remove(const K& key) {
        if (key < this->key) {
            return this->left->remove(key);
        }
        else if (key > this->key) {
            return this->right->remove(key);
        }
        else { //found
            // No child
            if (this->left == nullptr && this->right == nullptr) {
                delete this;
                //this = nullptr;
                return true;
            }
                //1
            else if (this->left == nullptr) {
                Node<K, V> *temporary = this;
                this = this->right;
                delete temporary;
                this->treeSize--;
            }
            else if (this->right == nullptr) {
                Node<K, V> *temporary = this;
                this = this->left;
                delete temporary;
                this->treeSize--;
            }
                //2
            else {
                Node<K, V> *temporary = findMin(this->right);
                this->key = temporary->key;
                this->value = temporary->value;
                return this->right.remove(key);
            }
        }
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
    void printTree(Node<K,V> *node) const;
    bool contains(Node<K,V> *node, const K& key) const;
    void clearTree(Node<K,V> *node);
    V& searchValue(Node<K,V> *node, const K& key) const;
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
