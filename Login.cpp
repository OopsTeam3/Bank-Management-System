#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Login{
    public:
    int accNo;
    string password;

    Login(){
        accNo=0;
        password="";
    }

    Login(int accNo,string password){
        this->accNo=accNo;
        this->password=password;
    }


    bool login()
    {
        int accNoInFile;
        string passwordInFile;

        ifstream in("login.txt");

        while(!in.eof())
        {
            in>>accNoInFile;
            in>>passwordInFile;
            if(accNo==accNoInFile && password==passwordInFile)
            {
                return true;
            }
        }

        return false;

 }

    void createAccount(int accNo)
    {
        ofstream out("login.txt",ios::app);
        cout<<"Create a new Password : ";
        cin>>password;
        out<<accNo<<endl<<password<<endl;
    }

};


class Application
{

    static Application *application; 
    
    Application()
    {}
    public:
   static Application *getInstance() {
      if (!application)
      application = new Application;
      return application;
   }

    bool login(int accNo)
    {
        string passwrd;
        cout<<"Enter Password : ";
        cin>>passwrd;
        Login login(accNo,passwrd);
        return login.login();
    }

    void createAccount(int accNo)
    {
        Login login;
        login.createAccount(accNo);
    }
};

