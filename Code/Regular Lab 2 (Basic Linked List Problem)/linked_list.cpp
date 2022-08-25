#include <iostream>
#include <string>
using namespace std;

enum Command {IH, IT, RH, RT, S, O};

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

class List
{
private:
    Node *head, *tail;
    bool is_empty();
    Node* newNode(int data);
public:
    List() {
        head = tail = nullptr;
    }
    ~List() {
        Node *iter = head;
        while(iter) {
            Node *temp = iter;
            iter = iter->next;
            delete temp;
        }
    }
    void insert_head(int data);
    void insert_tail(int data); 
    void remove_head(); 
    void remove_tail(); 
    void search(int data); 
    void output();
    void print_node();
};

int get_token(string &cmd);

int main() {
    
    int n;
    cin >> n;
    string cmd;
    int parameter;
    List list;
    while(n--) {
        cin >> cmd;
        if(cmd == "IH" || cmd == "IT" || cmd == "S")
            cin >> parameter;
        int token = get_token(cmd);
        switch (token)
        {
        case IH:
            list.insert_head(parameter);
            break;
        case IT:
            list.insert_tail(parameter);
            break;
        case RH:
            list.remove_head();
            break;
        case RT:
            list.remove_tail();
            break;
        case S:
            list.search(parameter);
            break;
        case O:
            list.output();
            break;
        default:
            cout << "error cmd" << endl;
            exit(-1);
            break;
        }
        // list.print_node();
    }
    
    return 0;
}
/* if head == nullptr then return true */
bool List::is_empty() {
    return !head;
}
/* init a new node, two ptr are set nullptr */
Node* List::newNode(int data) {
    Node *node = new Node;
    node->data = data;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}
/* IH ii : Insert head. Insert a new node with integer ii to the head of the linked list. */
void List::insert_head(int data) {
    Node *node = newNode(data);
    if(is_empty()) {
        head = tail = node;
        return;
    }
    node->next = head;
    head->prev = node;
    head = node;
}
/* IT ii : Insert tail. Insert a new node with integer ii to the tail of the linked list. */
void List::insert_tail(int data) {
    Node *node = newNode(data);
    if(is_empty()) {
        head = tail = node;
        return;
    }
    tail->next = node;
    node->prev = tail;
    tail = node;
}
/* RH : Remove head. Remove the node at the head of the linked list. (If the linked list is empty, don't do anything.) */
void List::remove_head() {
    if(is_empty())  return; // don't do anything
    Node *del = head;
    if(head == tail) {
        head = tail = nullptr;
        delete del;
        return;
    }
    head->next->prev = nullptr;
    head = head->next;
    delete del;
}
/* RT : Remove tail. Remove the node at the tail of the linked list. (If the linked list is empty, don't do anything.) */
void List::remove_tail() {
    if(is_empty())  return; // don't do anything
    Node *del = tail;
    if(head == tail) {
        head = tail = nullptr;
        delete del;
        return;
    }
    tail->prev->next = nullptr;
    tail = tail->prev;
    delete del;
}
/* S ii : Search. Traverse the linked list and find if there exists a node with integer ii. If yes, print a line "Y". Otherwise, print a line "N". (If the linked list is empty, print a line "E".) */
void List::search(int data) {
    if(is_empty()) {
        cout << "E" << endl;
        return;
    }
    for(Node *iter = head; iter; iter = iter->next) {
        if(iter->data == data) {
            cout << "Y" << endl;
            return;
        }
    }
    cout << "N" << endl;
}
/* O : Output. Traverse the linked list from head to tail. Print the integers saved in the nodes sequentially. (If the linked list is empty, print a line "E".) */
void List::output() {
    if(is_empty()) {
        cout << "E" << endl;
        return;
    }
    for(Node *iter = head; iter; iter = iter->next)
        cout << iter->data << " ";
    cout << endl;
}
/* print head and tail data */
void List::print_node() {
    if(head)
        cout << "head: " << head->data << " ";
    else 
        cout << "head: nullptr. ";
    if(tail)
        cout << "tail: " << tail->data;
    else
        cout << "tail: nullptr. ";
    cout << endl; 
}

int get_token(string &cmd) {
    if(cmd == "IH") return IH;
    if(cmd == "IT") return IT;
    if(cmd == "RH") return RH;
    if(cmd == "RT") return RT;
    if(cmd == "S") return S;
    if(cmd == "O") return O;
    return -1; 
}