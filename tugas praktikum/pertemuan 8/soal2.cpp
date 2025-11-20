#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
    string inputSentence;
    cout << "Enter a sentence: ";
    getline(cin, inputSentence);
    
    stack<char> charStack;

    for(char c : inputSentence){
        charStack.push(c);
    }
    while(!charStack.empty()){
        cout << charStack.top();
        charStack.pop();
    }
    return 0;
}
