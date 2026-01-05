#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;
void clearscreen()
{
    cout<<endl<<"Press any key to continue "<<endl;
    getch();
    system("cls");
}
void header(HANDLE h)
{
    SetConsoleTextAttribute(h,11);
    cout << "*********************************************************************" << endl;
    cout << "*                                                                   *" << endl;
    cout << "*                  CRYPTOGRAPHY PUZZLE HUNT SYSTEM                  *" << endl;
    cout << "*                                                                   *" << endl;
    cout << "*********************************************************************" << endl;
    SetConsoleTextAttribute(h,15);
}
int mod(int a, int m) // algorithm to find modulus
{
    int x = (a % m + m) % m; // It will always return positive mod
    return x;
}
void showFrequencies(string text) // cryptanalysis tool
{
    int freq[26] = {0};
    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i]; // check each character of the passed parameter
        if (isalpha(c))
            freq[toupper(c) - 'A']++;
    }
    int maxIndex = 0;
    for (int i = 1; i < 26; i++)
    {
        if (freq[i] > freq[maxIndex])
            maxIndex = i;
    }
    cout << "Hint: The most common letter is "
         << char('A' + maxIndex) << endl;
}
// file managemnet
void saveRecord(int rollNo, int level, float score, float penalty)
{
    fstream file;
    file.open("PuzzleRecords.txt", ios::app);
    file << "Roll: " << rollNo << " "
         << "  Level: " << level << " "
         << "  Score: " << score << " "
         << "  Penalty: " << penalty << endl;
    file.close();
}
void loadRecords()
{
    fstream file;
    file.open("PuzzleRecords.txt", ios::in);
    if (!file)
    {
        return;
    }
    string line;
    while (!file.eof())
        file >> line;
    file.close();
}
bool requestHint() // hint function
{
    char choice;
    cout << "Do you want a hint?" << endl
         << "Enter (Y/N): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
        return true;
    else
        return false;
}
void caesarPuzzle(int level, string words[], int total, // caesar cipher puzzle
                  float &score, float &penalty,HANDLE h)
{
    int key = rand() % (level * 3 + 5) + 1; // randomly generated key for different levels
    string text = words[rand() % total];    // choose random word
    cout << endl;
    cout << "Encrypted: ";
    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];
        cout << char('a' + (c - 'a' + key) % 26); // encrypted word
    }
    string user;
    bool c = false;
    for (int i = 0; i < 3; i++)
    {
        if (i == 3)
            cout << endl
                 << "Last chance " << endl;
        cout << endl
             << "Hint: Caesar Key = " << key << endl;
        cout << endl
             << "Your Answer: ";
        cin >> user;
        if (user == text)
        {
            score = score + 1;
            SetConsoleTextAttribute(h,11);
            cout<<endl<<"CORRECT ANSWER"<<endl;
            SetConsoleTextAttribute(h,15);
            c = true;
            break;
        }
        else
        {
             SetConsoleTextAttribute(h,12);
            cout << "Wrong!" << endl;
             SetConsoleTextAttribute(h,15);
            if (i <= 2)
            {
                cout << "Try Again ";
            }
        }
    }
    if (!c)
        cout << "The correct answer is: " << text;
}
void affinePuzzle(string words[], int total, // affine cipher puzzle
                  float &score, float &penalty,HANDLE h)
{
    int a = 5, b = rand() % 10;
    string text = words[rand() % total]; // choose random word
    cout << endl;
    cout << "Encrypted: ";
    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];
        cout << char('a' + mod(a * (c - 'a') + b, 26)); // encrypted text
    }
    string user;
    bool r = false;
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << endl;
        if (i == 3)
            cout << endl
                 << "Your Last Chance " << endl;
        showFrequencies(text); // function which will tell most common letter for hint
        cout<<endl<<"The key is: "<<b<<endl;
        cout << endl
             << "Your Answer: ";
        cin >> user;
        if (user == text)
        {
              SetConsoleTextAttribute(h,11);
            cout<<endl<<"CORRECT ANSWER"<<endl;
            SetConsoleTextAttribute(h,15);
            score = score + 1;
            r = true;
            break;
        }
        else
        {
             SetConsoleTextAttribute(h,12);
            cout << endl<<"Wrong!" << endl;
             SetConsoleTextAttribute(h,15);
            if (i <= 2)
                cout << "Try Again: ";
        }
    }
    if (!r)
        cout <<endl<< "The correct answer is: " << text;
}
void modularPuzzle(float &score, float &penalty,HANDLE h) // modular arithmetic
{
    int a = rand() % 500 + 1, x = rand() % 100 + 1, m = rand() % 50 + 5;
    int b = mod(a * x, m);
    cout << "Solve: " << a << "x is congruent to  " << b << " (mod " << m << ")\n";
    cout << "x = ";
    int user;
    cin >> user;
    if (mod(a * user, m) == b)
    {
          SetConsoleTextAttribute(h,11);
            cout<<endl<<"CORRECT ANSWER"<<endl;
            SetConsoleTextAttribute(h,15);
        score = score + 1;
        return;
    }
    if (requestHint())
    {
        penalty = penalty + 0.5;
        int hintArr[4] = {x, x - 7, x + 8, x - 11};
        random_shuffle(hintArr, hintArr + 4); // generate different options location
        cout << endl
             << "Hint Options: " << endl;
        for (int i = 0; i < 4; i++)
        {
            cout << hintArr[i] << " ";
        }
        cout << endl
             << "Try Again: ";
        cin >> user;
        if (mod(a * user, m) == b)
        {
            score = score + 0.5;
            return;
        }
    }
     SetConsoleTextAttribute(h,12);
    cout << "Wrong!" << endl;
     SetConsoleTextAttribute(h,15);
    cout << "The correct option is: " << x;
    cout << endl;
}
void primePuzzle(float &score, float &penalty,HANDLE h) // prime numbers puzzle
{
    int n = rand() % 50 + 50;
    bool prime[200];
    // using the concept of sieve of erastothenes
    for (int i = 0; i <= n; i++)
    {
        prime[i] = true; // at first consider all are primes
    }
    prime[0] = false; // as 0 and 1 are not prime
    prime[1] = false; // setting a base case
    for (int p = 2; p * p <= n; p++)
    {
        if (prime[p])
        {
            for (int i = p * p; i <= n; i += p)
            {
                prime[i] = false;
            }
        }
    }
    int count = 0;
    for (int i = 2; i <= n; i++)
    {
        if (prime[i])
        {
            count++;
        }
    }
    cout << "How many primes between 1 and " << n << "? ";
    int user;
    cin >> user;
    if (user == count)
    {
          SetConsoleTextAttribute(h,11);
            cout<<endl<<"CORRECT ANSWER"<<endl;
            SetConsoleTextAttribute(h,15);
        score = score + 1;
        return;
    }
    if (requestHint())
    {
        penalty = penalty + 0.5;
        cout << "Hint: Eliminate multiples of prime numbers (Sieve of erastothenes method)."<<endl;
        cout << "Try Again: ";
        cin >> user;
        if (user == count)
        {
            SetConsoleTextAttribute(h,11);
            cout<<endl<<"CORRECT ANSWER"<<endl;
            SetConsoleTextAttribute(h,15);
            score = score + 0.5;
            return;
        }
    }
    else
    {
        cout << "Try Again: ";
         cin >> user;
    }
             SetConsoleTextAttribute(h,12);
    cout << "Wrong!";
       SetConsoleTextAttribute(h,15); 
    cout << endl;
}
// menu options
int levelSelect(HANDLE h)
{
    header(h);
    SetConsoleTextAttribute(h,6);
    system("cls");
    int option;
    cout << endl
         << "------------------------------------" << endl;
    cout << "|           LEVEL SELECTOR         |" << endl;
    cout << "------------------------------------" << endl;
    cout << "------------------------------------" << endl;
    cout << "|                                  |" << endl;
    cout << "|                                  |" << endl;
    cout << "|          1.EASY LEVEL            |" << endl;
    cout << "|          2.MEDIUM LEVEL          |" << endl;
    cout << "|          3.DIFFICULT LEVEL       |" << endl;
    cout << "|                                  |" << endl;
    cout << "|                                  |" << endl;
    cout << "------------------------------------" << endl;
    cout << endl;
        SetConsoleTextAttribute(h,15);
    cout << "Choose any level (1,2,3): ";
    cin >> option;
    if (option != 1 && option != 2 && option != 3)
    {
        Sleep(80);
        system("cls");
        cout << endl
             << "CHOOSE THE CORRECT OPTION!!" << endl;
        cout << "PRESS ANY KEY TO CONTINUE..." << endl;
        getch();
        return levelSelect(h);
    }
    else
    {
        return option;
    }
}
void playLevel(int level, string words[], int total, float &score, float &penalty,HANDLE h)
{
    for (int i = 0; i < 10; i++)
    {
         int r = rand() % 100; 
        int type = 0;
        if (level == 1) // Easy more caeser cipher
        {    
            if (r < 40)
                type = 0;
            else if (r < 70)
                type = 1;
            else if (r < 90)
                type = 2;
            else
                type = 3;
        }
        else if (level == 2) // Medium
        {
            if (r < 20)
                type = 0;
            else if (r < 60)
                type = 1;
            else if (r < 90)
                type = 2;
            else
                type = 3;
        }
        else if (level == 3) // Hard more affine cipher
        {
            if (r < 40)
                type = 1; // Affine
            else if (r < 70)
                type = 2; // Modular
            else
                type = 3; // Prime
        }
        if (type == 0)
        {
            clearscreen();
            header(h);
            caesarPuzzle(level, words, total, score, penalty,h);
            cout << endl;
        }
        else if (type == 1)
        {
            clearscreen();
            header(h);
            affinePuzzle(words, total, score, penalty,h);
            cout << endl;
        }
        else if (type == 2)
        {
             clearscreen();
            header(h);
            modularPuzzle(score, penalty,h);
            cout << endl;
        }
        else
        {
            clearscreen();
            header(h);
            primePuzzle(score, penalty,h);
            cout << endl;
        }
    }
}
int main()
{
    system("cls");
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    string words[25] = {"journalist", "microscope", "telephone", "restaurant", "airplane",
                        "bicycle", "computer", "notebook", "elevator", "headphones",
                        "television", "umbrella", "backpack", "sandwich", "kitchen",
                        "laptop", "photograph", "apartment", "television", "hospital",
                        "telescope", "furniture", "library", "vacuum", "microwave"};
    int rollNumber, level;
    float score = 0, penalty = 0;
    loadRecords();
    header(h);
    cout << "Enter Roll Number: ";
    cin >> rollNumber;
    srand(time(0) + rollNumber); // unique puzzle for each student
    level = levelSelect(h);
    system("cls");
    header(h);
    playLevel(level, words, 25, score, penalty,h);
    cout << endl;
    clearscreen();
    header(h);
    cout << "Final Score: " << score << "/10" << endl;
    cout << "Marks Deducted By Hints: " << penalty << endl;
    saveRecord(rollNumber, level, score, penalty);
}
