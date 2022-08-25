#include <iostream>
#include <stack>
using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
    Node(int _d, Node *_l = nullptr, Node *_r = nullptr) :
        key(_d), left(_l), right(_r) {}
};

void inorder(Node* root);
bool insert(Node* &cur, int key);
bool search(Node* cur, int key);
int lower_bound(Node* cur, int key);
int upper_bound(Node* cur, int key);
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
        case 'S':
            if(search(root, key))   cout << "YES" << endl;
            else    cout << "NO" << endl;
            break;
        case 'L': 
            cout << lower_bound(root, key) << endl;
            break;
        case 'U':
            cout << upper_bound(root, key) << endl;
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
    if(key == cur->key) return false;
    Node* &next = (key < cur->key) ? cur->left : cur->right;
    return insert(next, key);
}

bool search(Node* cur, int key) {
    while (cur) {
        if(key == cur->key) return true;
        cur = (key < cur->key) ? cur->left: cur->right;
    }
    return false;
}

/* find node smallest element greater or equal key, if not return -1 */
int lower_bound(Node* cur, int key) {
    if(!cur)    return -1;
    stack <Node*> S;
    while(cur) {
        if(key == cur->key) return key;
        S.push(cur);
        cur = (key < cur->key) ? cur->left: cur->right;
    }
    // key is not in BST, trace back
    while(!S.empty()) {
        cur = S.top();
        S.pop();
        if(cur->key > key)  return cur->key;
    }
    return -1;
}

int upper_bound(Node* cur, int key) {
    if(!cur)    return -1;
        stack <Node*> S;
    while(cur) {
        if(key == cur->key) break;
        S.push(cur);
        cur = (key < cur->key) ? cur->left: cur->right;
    }
    if(cur && cur->right) {
        for(cur = cur->right; cur->left; cur = cur->left);
        return cur->key;
    }
    // trace back
    while(!S.empty()) {
        cur = S.top();
        S.pop();
        if(cur->key > key)  return cur->key;
    }
    return -1;
}

bool remove(Node* &cur, int key) {
    if(!cur)    return false;
    if(key == cur->key) {
        remove_node(cur);
        return true;
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
    cur->key = max_node->key;
    remove_node(max_node);
}

Node *&get_max(Node* &cur) {
    if(!cur->right) return cur;
    return get_max(cur->right);
}