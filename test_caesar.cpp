#include <iostream>
using namespace std;

string caesar(string text, int key)
{
    for(int i=0;i<text.length();i++)
 text[i] = char('a' + (text[i]-'a'+key)%26);
    return text;
}
main()
{
    if(caesar("abc",3)=="def")
        cout<<"Cipher Test Passed";
    else
        cout<<"Cipher Test Failed";
}
