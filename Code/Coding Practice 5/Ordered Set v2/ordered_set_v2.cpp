#include <iostream>
using namespace std;

struct Node
{
    int key;
    int value;
    Node *left;
    Node *right;
    Node(int _d, int _v = 1, Node *_l = nullptr, Node *_r = nullptr) :
        key(_d), value(_v), left(_l), right(_r) {}
};

void inorder(Node* root);
bool insert(Node* &cur, int key);
int search(Node* cur, int key);
Node* lower_bound(Node* cur, int key);
Node* upper_bound(Node* cur, int key);
bool remove(Node* &cur, int key);
Node *&get_max(Node* &cur);
void remove_node(Node* &cur);

int main() {
    int n, size = 0;
    Node* root = nullptr;
    cin >> n;
    while(n--) {
        char cmd;
        int key;
        cin >> cmd >> key;
        Node* ptr;
        switch (cmd)
        {
        case 'I':
            if(insert(root, key))   size++;
            cout << size << endl;
            break;
        case 'R':
            if(remove(root, key))   size--;
            cout << size << endl;
            break;
        case 'C':
            cout << search(root, key) << endl;
            break;
        case 'L': 
            ptr = lower_bound(root, key);
            cout << (ptr ? ptr->key: -1) << endl;
            break;
        case 'U':
            ptr = upper_bound(root, key);
            cout << (ptr ? ptr->key: -1) << endl;
            break;
        default:
            exit(-1);
            break;
        }
    }
    return 0;
}

void inorder(Node* root) {
    if(!root)   return;
    // cout << "( ";
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
    // cout << ") ";
}

bool insert(Node* &cur, int key) {
    if(!cur) {
        cur = new Node(key);
        return true;
    }
    if(key == cur->key) {
        cur->value++;
        return false;
    }
    Node* &next = (key < cur->key) ? cur->left : cur->right;
    return insert(next, key);
}

int search(Node* cur, int key) {
    while (cur) {
        if(key == cur->key) return cur->value;
        cur = (key < cur->key) ? cur->left: cur->right;
    }
    return 0;
}

/* find node smallest element greater or equal key, if not return -1 */
Node* lower_bound(Node* cur, int key) {
    if(!cur)    return nullptr;
    if(key == cur->key) return cur;
    if(key < cur->key) {
        Node* ptr = lower_bound(cur->left, key);
        return ptr ? ptr: cur;
    }
    return lower_bound(cur->right, key);
}

Node* upper_bound(Node* cur, int key) {
    if(!cur)    return nullptr;
    if(key < cur->key) {
        Node* ptr = upper_bound(cur->left, key);
        return ptr ? ptr: cur;
    }
    return upper_bound(cur->right, key);
}

bool remove(Node* &cur, int key) {
    if(!cur)    return false;
    if(key == cur->key) {
        if(cur->value > 1) {
            cur->value--;
            return false;
        }
        else {
            remove_node(cur);
            return true;
        }
    }
    Node* &next = (key < cur->key) ? cur->left : cur->right;
    return remove(next, key);
}

void remove_node(Node* &cur) {
    // CASE 1: cur is leaf node
    if(!cur->left && !cur->right) {
        free(cur);
        cur = nullptr;
        return;
    }
    // CASE 2: cur has one child
    if(cur->left && !cur->right) {
        Node* del = cur;
        cur = cur->left;
        free(del);
        return;
    }
    if (!cur->left && cur->right){
        Node* del = cur;
        cur = cur->right;
        free(del);
        return;
    }
    // CASE 3: cur has two children
    Node* &max_node = get_max(cur->left);
    // swap cur and max_node
    cur->key = max_node->key;
    cur->value = max_node->value;
    remove_node(max_node);
}

Node *&get_max(Node* &cur) {
    if(!cur->right) return cur;
    return get_max(cur->right);
}