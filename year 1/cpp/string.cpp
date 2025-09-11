#include <iostream>
#include <string>
using namespace std;
int main(){
    string greeting = "Feralick is going to be a successful youtube channel.";
    cout << greeting << endl;
    cout << "The length of the txt string is: " << greeting.length() << endl;
    cout << "The length of the txt string is: " << greeting.size() << endl;
    for (int i = 0; i < greeting.length()-1; i++){
        cout << greeting[i];
    }

    string fullName;
    cout << "Type your full name: ";
    getline (cin, fullName);
    cout << "Your name is: " << fullName;
    return 0;
}