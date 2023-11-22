#include<iostream>
#include<time.h>
#include<fstream>
#include "User.cpp"
using namespace std;

bool accNumberNotUnique(int accNo)
{
    int accNoInFile;
    string passwordInFile;

    ifstream in("login.txt");

        while(!in.eof())
        {
            in>>accNoInFile;
            in>>passwordInFile;
            if(accNo==accNoInFile)
            {
                return true;
            }
        }

        return false;
}

int main()
{

    return 0;
}
