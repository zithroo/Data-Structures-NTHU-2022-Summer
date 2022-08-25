#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct node
{
    char data;
    node *left;
    node *right;
    int value;
    node() {}
    node(char _d, node *_l, node *_r) :
        data(_d), left(_l), right(_r) {}
};

node* pop(stack <node*> &tree, char opr) {
    node *op1, *op2;
    op1 = tree.top();
    tree.pop();
    op2 = tree.top();
    tree.pop();
    node *temp = new node(opr, op1, op2);
    return temp;
}

node* expression_tree(string &postfix) {
    if(postfix.size() == 0)   return nullptr;
    stack <node*> tree;
    for(int i = postfix.length()-1; i >= 0; i--) {
        if(isdigit(postfix[i])) {
            node* temp = new node(postfix[i], nullptr, nullptr);
            tree.push(temp);
        }
        else {
            tree.push(pop(tree, postfix[i]));
        }
    }
    return tree.top();
}

int bi_operator(int left, int right, char opr) {
    switch (opr)
    {
    case '+':
        return left + right;
        break;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/': 
        return left / right;
    default:
        return 1;
        break;
    }
}

int eval(node *tree) {
    if (isdigit(tree->data)) {
        tree->value = tree->data - '0';
        return tree->value;
    }
    int left = eval(tree->left);
    int right = eval(tree->right);
    tree->value = bi_operator(left, right, tree->data);
    return tree->value;
}

bool rightRotation(node *&root) {
    node* left = root->left;
    if(left->right == nullptr)
        return false;
    root->left = left->right;
    left->right = root;
    root = left;
    // update value
    node* right = root->right;
    right->value = bi_operator(right->left->value, right->right->value, right->data);
    root->value = bi_operator(root->left->value, root->right->value, root->data);
    return true;
}

bool leftRotation(node *&root) {
    node* right = root->right;
    if(right->left == nullptr)
        return false;
    root->right = right->left;
    right->left = root;
    root = right;
    // update value
    node* left = root->left;
    left->value = bi_operator(left->left->value, left->right->value, left->data);
    root->value = bi_operator(root->left->value, root->right->value, root->data);
    return true;
}

int main() {
    string postfix;
    int num, min_eval;
    cin >> num;
    cin >> postfix;
    node *tree = expression_tree(postfix);
    min_eval = eval(tree);

    while(rightRotation(tree)) {
        if(tree->value < min_eval)
            min_eval = tree->value;
    }

    while(leftRotation(tree)) {
        if(tree->value < min_eval)
            min_eval = tree->value;
    }
    cout << min_eval << endl;

    return 0;
}