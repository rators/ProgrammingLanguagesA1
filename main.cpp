#include <iostream>
#include <fstream>
#include <vector>
#include <map>
/**
 * Single Line of Code is any line of code that isn't a closing curly brace,
 * and is not just a line of white space. Comments are not lines of code.
 *
 *
 */
using namespace std;
//Contains helper method
bool contains(string s, char c){
    for(char find : s){
        if (find == c ) return true;
    }
    return false;
}
//Brace balancing helper
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
    ifstream fileInput;
    fileInput.open(fileName);
    string line;
    //Create a vector of strings so I don't have to deal with tokens
    while(std::getline(fileInput, line)){
         fileAsString.push_back(line);
    }
    //remove multi line comments
    for(int i = 0; i < fileAsString.size(); i++){
        if(fileAsString[i].find("/*") != string::npos){
            for(int j = i + 1; j < fileAsString.size(); j++){
                if(fileAsString[j].find("*/") != string::npos){
                    fileAsString.erase(fileAsString.begin()+i, fileAsString.begin()+j+1);
                }
            }
        }
    }
    //Remove comments
    for(int i = 0; i < fileAsString.size(); i++){
        if(fileAsString[i].find("//") != string::npos) {
            fileAsString.erase(fileAsString.begin() + i);
            i--;
        }
    }
    //Remove white space
    for(int i = 0; i < fileAsString.size(); i++){
        if(fileAsString[i].find_first_not_of(' ') == std::string::npos){
            fileAsString.erase(fileAsString.begin() + i);
            i--;
        }
    }
    return fileAsString;
}
int main() {
    vector<string> array = fileToArray("input.txt");
    std::map<int,int> scopes;
    int SLOC = 0;
    for(auto& s : array){
        cout << s << endl;
    }
    for(int i = 0; i < array.size(); i++){
        if(!contains(array[i], '{') && !contains(array[i], '}')) {
            SLOC++;
            long scopeNumber = 0;
            for(int j = i-1; j > -1; j--){
                scopeNumber += braceBalance(array[j]);
            }
        }
        else if(contains(array[i], '{') && !contains(array[i], '}')){
            SLOC++;
            int scopeNumber = 0;
            for(int j = i-1; j > -1; j--){
                scopeNumber += braceBalance(array[j]);
            }
            if(scopes.count(scopeNumber + 1)){
                scopes[scopeNumber + 1] += 1;
            }
            else{
                scopes[scopeNumber + 1] = 1;
            }
        }
    }
    cout << "Scope" << " " << "   Level" << endl;
    for(auto& elem : scopes){
        cout << "  " << elem.first  << "        " << elem.second << endl;
    }
    cout << "SLOC count is : " << SLOC << endl;
    return 0;
}