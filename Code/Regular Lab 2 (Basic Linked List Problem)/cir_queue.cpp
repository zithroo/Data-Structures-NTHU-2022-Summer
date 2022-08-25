/* use array to implement circular dequeue
 * # of search operations  will not exceed 50, and i = 1~99, so use array to implement search
 */
#include <iostream>
#include <string>
using namespace std;

enum Command {IH, IT, RH, RT, S, O};

int front = 0, rear = 0;
char *dequeue;
int set[100] = {0};
int capacity;

int get_token(string &cmd);
void insert_head(int parameter);
void insert_tail(int parameter);
void remove_head();
void remove_tail();
void search(int parameter);
void output();

int main() {
    int n;
    cin >> n;
    capacity = n + 1;
    dequeue = new char [capacity];
    
    string cmd;
    int parameter;

    while(n--) {
        cin >> cmd;
        if(cmd == "IH" || cmd == "IT" || cmd == "S")
            cin >> parameter; // parameter: 1~99
        int token = get_token(cmd);
        switch (token)
        {
        case IH:
            insert_head(parameter);
            break;
        case IT:
            insert_tail(parameter);
            break;
        case RH:
            remove_head();
            break;
        case RT:
            remove_tail();
            break;
        case S:
            search(parameter);
            break;
        case O:
            output();
            break;
        default:
            cout << "error cmd" << endl;
            exit(-1);
            break;
        }
    }
    
    return 0;
}

void insert_head(int parameter) {
    dequeue[front] = (char) parameter;
    front = (front == 0) ? capacity-1: front-1; 
    set[parameter]++;
}

void insert_tail(int parameter) {
    rear = (rear + 1) % capacity;
    dequeue[rear] = (char) parameter;
    set[parameter]++;
}

void remove_head() {
    if(front == rear)   return;
    front = (front + 1) % capacity;
    set[dequeue[front]]--;
}

void remove_tail() {
    if(front == rear)   return;
    set[dequeue[rear]]--;
    rear = (rear == 0) ? capacity-1: rear-1;
}
void search(int parameter) {
    if(front == rear) {
        cout << "E" << endl;
        return;
    }
    if(set[parameter])  cout << "Y" << endl;
    else cout << "N" << endl;
}

void output() {
    if(front == rear) {
        cout << "E" << endl;
        return;
    }
    for(int i = front; i != rear; i = (i + 1) % capacity)
        cout << (int) dequeue[(i + 1) % capacity] << " ";
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