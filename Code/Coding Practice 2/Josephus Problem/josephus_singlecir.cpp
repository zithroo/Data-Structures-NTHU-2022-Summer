#include <iostream>
#define COUNT 2
using namespace std;

struct node
{
    int id;
    node* next;
};

class cirlist
{
private:
    
public:
    node* head, *tail;
    cirlist();
    ~cirlist();
    bool empty();
    node *new_node(int id);
    void insert_head(int id);
    void print_list();
    void del_node(node* prev);
    node* jump(node* cur, int count);
};

cirlist::cirlist()
{
    head = tail = nullptr;
}

cirlist::~cirlist()
{
    node* it = head;
    while(it != tail) {
        node* del = it;
        it = it->next;
        delete del;
    }
    delete tail;
    head = tail = nullptr;
}

bool cirlist::empty()
{
    return (head == nullptr);
}

node* cirlist::new_node(int id)
{
    node* ptr = new node;
    if(!ptr) {
        cout << "memory access error" << endl;
        exit(-1);
    }
    ptr->id = id;
    ptr->next = nullptr;
    return ptr;
}

void cirlist:: insert_head(int id) 
{
    node* ptr = new_node(id);
    if(!head) {
        head = tail = ptr;
        ptr->next = head;
        return;
    }
    ptr->next = head;
    head = ptr;
    tail->next = ptr;
    return;
}

void cirlist:: print_list()
{
    cout << "head: " << head->id << " tail: " << tail->id << endl;
    for(node* it = head; it != tail; it = it->next)
        cout << it->id << " -> ";
    cout << tail->id << endl;
}

void cirlist:: del_node(node *prev)
{
    if(head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }
    node *del = prev->next;
    if(head == del)
        head = del->next;
    if(tail == del)
        tail = prev;
    prev->next = del->next;
    delete del;
}

node* cirlist::jump(node* cur, int count) {
    /* return prev */
    count = count-2;
    while(count--)
        cur = cur->next;
    return cur;
}

int main() {
    int n;
    cirlist josephus;
    for(cin >> n; n > 0; n--)
        josephus.insert_head(n);

    node* cur = josephus.head;
    node* prev;
    
    while(!josephus.empty()) {
        // josephus.print_list();
        prev = josephus.jump(cur, COUNT);
        cout << prev->next->id << " ";
        cur = prev->next->next;
        josephus.del_node(prev);
    }
    cout << endl;
    return 0;
}