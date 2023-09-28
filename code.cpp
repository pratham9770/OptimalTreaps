#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

struct TreapNode {
    int key;
    int priority;
    int searchCount;
    TreapNode* left;
    TreapNode* right;

    TreapNode(int k) : key(k), priority(1), searchCount(1), left(nullptr), right(nullptr) {}
};

class Treap {
private:
    TreapNode* root;

    TreapNode* rightRotate(TreapNode* y) {
        TreapNode* x = y->left;
        TreapNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        return x;
    }

    TreapNode* leftRotate(TreapNode* x) {
        TreapNode* y = x->right;
        TreapNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        return y;
    }

    TreapNode* insert(TreapNode* root, int key) {
        if (!root)
            return new TreapNode(key);

        if (key == root->key) {
            root->searchCount++;
            root->priority++; // Increase priority on search
        } else if (key < root->key) {
            root->left = insert(root->left, key);
            if (root->left->priority > root->priority)
                root = rightRotate(root);
        } else {
            root->right = insert(root->right, key);
            if (root->right->priority > root->priority)
                root = leftRotate(root);
        }

        return root;
    }

    TreapNode* deleteNode(TreapNode* root, int key) {
        if (!root)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (root->searchCount > 1) {
                root->searchCount--;
            } else {
                if (!root->left) {
                    TreapNode* temp = root->right;
                    delete root;
                    return temp;
                } else if (!root->right) {
                    TreapNode* temp = root->left;
                    delete root;
                    return temp;
                }

                if (root->left->priority > root->right->priority) {
                    root = rightRotate(root);
                    root->right = deleteNode(root->right, key);
                } else {
                    root = leftRotate(root);
                    root->left = deleteNode(root->left, key);
                }
            }
        }

        return root;
    }

public:
    Treap() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    bool search(int key) {
        TreapNode* current = root;
        while (current) {
            if (key == current->key) {
                current->searchCount++;
                current->priority++; // Increase priority on search
                return true;
            } else if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    // Function to display the Treap with tree-like structure
    void displayTree(TreapNode* root, std::string prefix = "", bool isLeft = true) {
        if (!root) {
            return;
        }

        std::cout << (isLeft ? "L-- " : "R-- ");
        std::cout << "Key: " << root->key << " Priority: " << root->priority << " Search Count: " << root->searchCount << std::endl;

        displayTree(root->left, prefix + (isLeft ? "    " : "|   "), true);
        displayTree(root->right, prefix + (isLeft ? "|   " : "    "), false);
    }

    TreapNode* getRoot() {
        return root;
    }
};

int main() {
    srand(time(nullptr));
    Treap treap;

    int keys[] = {5, 2, 8, 1, 3, 7, 9, 4, 6};

    for (int key : keys) {
        treap.insert(key);
        std::cout << "Inserted: " << key << std::endl;
    }

    std::cout << "Displaying the entire Treap:" << std::endl;
    treap.displayTree(treap.getRoot());

    for (int key : keys) {
        if (treap.search(key))
            std::cout << key << " found in Treap" << std::endl;
        else
            std::cout << key << " not found in Treap" << std::endl;
    }

    treap.remove(3);
    std::cout << "Removed: 3" << std::endl;

    if (treap.search(3))
        std::cout << "3 found in Treap" << std::endl;
    else
        std::cout << "3 not found in Treap" << std::endl;

    return 0;
}
