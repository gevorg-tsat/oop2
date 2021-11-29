//
// Created by Gevorg Tsaturyan on 29.11.2021.
//

#ifndef OOP_LABA2_BTREE_H
#define OOP_LABA2_BTREE_H
#include <iostream>
#include <vector>
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
    bool operator==(const Tree<K,V> &first, const Tree<K,V> &second) const;
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


#endif //OOP_LABA2_BTREE_H
