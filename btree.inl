//
// Created by Gevorg Tsaturyan on 29.11.2021.
//
#include "btree.h"
template<class K, class V>
V& Tree<K, V>::operator[](const K& key) const{
    return this->getValue(key);
}
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
    this->root = nullptr;
    this->treeSize=0;
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
void Tree<K, V>::add(const K &key, const V &value) {
    if (this->root == nullptr) {
        Node<K, V> *temp = new Node<K, V>(key, value);
        this->root = temp;
        this->treeSize++;
    }
    else
    if (this->root->add(key,value))
        this->treeSize++;
}
template<class K, class V>
void Tree<K, V>::remove(const K &key) {
    if (contains(key)) {
        this->root = remove(this->root, key);
    } else {
        return;
    }
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
        //0 ch
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
            this->treeSize--;
        }
            //1
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
            //2
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
    return this->root->contains(key);
}
template<class K, class V>
void Tree<K, V>::printTree() const {
    this->root->printTree();
}
template<class K, class V>
V& Tree<K, V>::getValue(const K &key) const {
    if (this->contains(key)) {
        return this->root->searchValue(key);
    }
    throw std::runtime_error("No such key in treemap");
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
        getKeys(keys, node->left);
        keys.push_back(node->key);
        getKeys(keys, node->right);
    }
}

template<class K, class V>
std::vector<K> Tree<K, V>::getKeys() const {
    std::vector<K> keys;
    getKeys(keys, this->root);
    return keys;
}
template<class K, class V>
Node<K, V>* Tree<K, V>::findMin(Node<K, V> *node) const{
    while(node->left != nullptr){
        node = node->left;
    }
    return node;
}