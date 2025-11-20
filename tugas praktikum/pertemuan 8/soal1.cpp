#include <iostream>
#define MAX_SIZE 100

using namespace std;

int stack[MAX_SIZE];
int top = -1;

void push(int value) {
    if (top >= MAX_SIZE - 1) {
        cout << " Stack Overflow ";
        return;
    }
    stack[++top] = value;
}
int pop(){
    if (top == -1) {
        cout << " Stack Underflow ";
        return -1;
    }
    return stack[top--];
}

int peek() {
    if(top == -1){
        cout << " Stack is Empty";
        return -1;

    }
    return stack[top];
}
bool isEmpty(){
    return top == -1;
}

void display() {
    if (top == -1) {
        cout << " Stack is Empty ";
        return;
    }
    cout << " Stack elements: ";
    for (int i = top; i >= 0; i--) {
        cout << stack[i] << " ";
    }
    cout << endl;
}

int main(){
    push(5);
    push(10);
    push(15);

    cout << "Top element is: " << peek() << endl;
    display();

    cout << "Popped element is: " << pop() << endl;
    display();

    push(20);
    display();

    return 0;
}