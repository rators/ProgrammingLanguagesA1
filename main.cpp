#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
bool contains(string s, char c){
    for(char find : s){
        if (find == c ) return true;
    }
    return false;
}
long braceBalance(string s){
    long balance = 0;
    for(auto& c : s){
        if (c == '{') {
            balance++;
        }
        else if(c == '}') balance--;
    }
    return balance;
}
vector<string> fileToArray(string fileName){
    vector<string> fileAsString;
    vector<string> withFilter;
    ifstream sample;
    sample.open(fileName);
    string line;
    while(std::getline(sample, line)){
         fileAsString.push_back(line);
    }
    for(int i = 0; i < fileAsString.size(); i++){
        if(fileAsString[i].find("/*") != string::npos){
            for(int j = i + 1; j < fileAsString.size(); j++){
                if(fileAsString[j].find("*/") != string::npos){
                    fileAsString.erase(fileAsString.begin()+i, fileAsString.begin()+j+1);
                }
            }
        }
    }
    return fileAsString;
}
int main() {
    int twoScope = 0;
    vector<int> result;
    vector<string> array = fileToArray("input.txt");
    for(int i = 0; i < array.size(); i++){
        cout << array[i] << endl;
    }
    for(int i = 0; i < array.size(); i++){
        if(!contains(array[i], '{') && !contains(array[i], '}')) {
            long scopeNumber = 0;
            cout << "Line [" << i + 1 << "] scope depth: ";
            for(int j = i-1; j > -1; j--){
                scopeNumber += braceBalance(array[j]);
            }
            cout << scopeNumber << endl;
        }
        else if(contains(array[i], '{') && !contains(array[i], '}')){
            long scopeNumber = 0;
            cout << "Line [" << i + 1 << "] scope depth left : ";
            for(int j = i-1; j > -1; j--){
                scopeNumber += braceBalance(array[j]);
            }
            cout << scopeNumber << ", right : " << scopeNumber + 1 <<  endl;
            if((scopeNumber + 1) == 2) twoScope++;
        }
    }
    cout << "The number of two scopes is : " << twoScope << endl;
    return 0;
}