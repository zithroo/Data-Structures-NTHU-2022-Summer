#include <iostream>
#include <string>
#include <stack>
#define VAR_NUM 5
using namespace std;

enum Opr {lp, add, sub, mul, divi, rp};
int ISP[5] = {0, 12, 12, 13, 13};
int ICP[5] = {19, 12, 12, 13, 13};
int var[VAR_NUM];

struct node
{
    char data;
    node *left;
    node *right;
    node(char _d, node *_l, node *_r) :
        data(_d), left(_l), right(_r) {}
};

int getToken(char op) {
    switch (op)
    {
    case '(':
        return lp;
    case '+':
        return add;
    case '-':
        return sub;
    case '*':
        return mul;
    case '/':
        return divi;
    case ')':
        return rp;
    default:
        return -1;
        break;
    }
}

node* pop(stack <node*> &tree, stack <char> &opr) {
    char in_stack_opr = opr.top();
    opr.pop();
    node *op1, *op2;
    op2 = tree.top();
    tree.pop();
    op1 = tree.top();
    tree.pop();
    node *temp = new node(in_stack_opr, op1, op2);
    return temp;
}

node* expression_tree(string &infix) {
    if(infix.size() == 0)   return nullptr;
    stack <node*> tree;
    stack <char> opr;
    for(int i = 0; i < infix.size(); i++) {
        int token = getToken(infix[i]);
        if(token == -1) {
            // operand
            node* temp = new node(infix[i], nullptr, nullptr);
            tree.push(temp);
        }
        else {
            // operator
            if(infix[i] == ')') {
                // pop untill we meet '('
                if(opr.empty()) {
                    cout << "input error" << endl;
                    exit(-1);
                }
                while(opr.top() != '(') {
                    tree.push(pop(tree, opr));
                }
                opr.pop(); // pop out '('
            }
            else {
                while(!opr.empty()) {
                    if(ISP[getToken(opr.top())] < ICP[getToken(infix[i])]) break;
                    tree.push(pop(tree, opr));
                }
                opr.push(infix[i]);
            }
        }
    }

    while(!opr.empty()) {
        node *new_node = pop(tree, opr);
        tree.push(new_node);
    }
    return tree.top();
}

long long int bi_operator(long long int left, long long int right, char opr) {
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

long long int eval(node *tree) {
    // post-order traversal
    if (isalpha(tree->data))
        return var[tree->data - 'A']; // use 0 1 2 3 4 to map A B C D E
    
    long long int left = eval(tree->left);
    long long int right = eval(tree->right);
    return bi_operator(left, right, tree->data);
}

int main() {
    string infix;
    int num;
    cin >> infix;
    node *tree = expression_tree(infix);

    cin >> num;
    while(num--) {
        for(int i = 0; i < VAR_NUM; i++)
            cin >> var[i];
        cout << eval(tree) << endl;
    }
    return 0;
}