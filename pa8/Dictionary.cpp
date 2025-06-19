/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA8
 * Dictionary.cpp
 * Dictionary ADT 
***/

#include <iostream>
#include <string>
#include "Dictionary.h"

#define RED 1
#define BLACK 0

using namespace std;

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = left = right = nullptr;
    color = RED;
}

Dictionary::Dictionary() {
    nil = new Node("", 0);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("", 0);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
    postOrderDelete(root);
    delete nil;
}

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key;
        if (R->color == RED) {
            s += " (RED)";
        }
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || R->key == k) {
        return R;
    }
    if (k < R->key) {
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    while (R->left != nil) {
        R = R->left;
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    while (R->right != nil) {
        R = R->right;
    }
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) {
        return findMin(N->right);
    }
    Node* y = N->parent;
    while (y != nil && N == y->right) {
        N = y;
        y = y->parent;
    }
    return y;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {
        return findMax(N->left);
    }
    Node* y = N->parent;
    while (y != nil && N == y->left) {
        N = y;
        y = y->parent;
    }
    return y;
}

void Dictionary::LeftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Dictionary::RightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_DeleteFixUp(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_Delete(Node* z) {
    Node* y = z;
    Node* x;
    int y_original_color = y->color;

    if (z->left == nil) {
        x = z->right;
        RB_Transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        RB_Transplant(z, z->left);
    } else {
        y = findMin(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;

    if (y_original_color == BLACK) {
        RB_DeleteFixUp(x);
    }
}

int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return (search(root, k) != nil);
}

valType& Dictionary::getValue(keyType k) const {
    Node* N = search(root, k);
    if (N == nil) {
        throw std::logic_error("Dictionary: getValue(): key not found");
    }
    return N->val;
}

bool Dictionary::hasCurrent() const {
    return (current != nil);
}

keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* z = new Node(k, v);
    Node* y = nil;
    Node* x = root;
    while (x != nil) {
        y = x;
        if (k == x->key) {
            x->val = v;
            delete z;
            return;
        } else if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nil) {
        root = z;
    } else if (k < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = z->right = nil;
    z->color = RED;
    num_pairs++;
    RB_InsertFixUp(z);
}

void Dictionary::remove(keyType k) {
    Node* z = search(root, k);
    if (z == nil) {
        throw std::logic_error("Dictionary: remove(): key not found");
    }
    if (z == current) {
        current = nil;
    }
    RB_Delete(z);
    num_pairs--;
}

void Dictionary::begin() {
    if (root != nil) {
        current = findMin(root);
    }
}

void Dictionary::end() {
    if (root != nil) {
        current = findMax(root);
    }
}

void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}

std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    return (to_string() == D.to_string());
}

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        clear();
        preOrderCopy(D.root, D.nil);
    }
    return *this;
}

