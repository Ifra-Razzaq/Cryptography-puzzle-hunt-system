#include <iostream>
using namespace std;
int mod(int a, int m) 
{
    return (a % m + m) % m;
}
string affineEncrypt(string text, int a, int b) 
{
    for(int i = 0; i < text.length(); i++) 
    {
        char c = text[i];
        text[i] = char('a' + mod(a * (c - 'a') + b, 26));
    }
    return text;
}
main() 
{
    string input = "hello";
    int a = 5, b = 8;
    string result = affineEncrypt(input, a, b);
    if(result == "rclla")
        cout << "Affine Test Passed";
    else
        cout << "Affine Test Failed";
}
