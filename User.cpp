#include<iostream>
#include "Loans.cpp"
#include "Insurance.cpp"
#include "Login.cpp"
using namespace std;

class Exception{
    public:
    string message;
    Exception(string message){
        this->message=message;
    }

    void print(){
        cout<<message<<endl;
    }
};

class Account{

    public:
    int accountNumber;
    double balance;
    Insurance *insurance;
    Loan *loan[3];
    int i=0;

     Account(){
        accountNumber=0;
        balance=0;
        insurance=NULL;
    }

    Account(int accountNumber,double balance)
    {
        this->accountNumber=accountNumber;
        this->balance=balance;
    }


    virtual double credit(double amount)
    {
        return balance+=amount;
    }

    virtual double debit(double amount) 
    {
        return balance-=amount;
    }

    void addInsurance(Insurance *insurance)
    {
        this->insurance=insurance;
    }

    virtual void print()
    {
        cout<<"Account Number : "<<accountNumber<<endl;
        cout<<"Balance : "<<balance<<endl;
    }

    void addLoan(Loan *loan)
    {
        
        int j=i+1;
        try{
            if(j>=3)
            {
                throw Exception("You can't add more than 3 loans");
            }
            else
                this->loan[i++]=loan;
        }
        catch(Exception e)
        {
            e.print();
        }      

    }

    void printLoan()
    {
        for(int j=0;j<i;j++)
        {
            loan[j]->print();
        }
    }

    void printInsurance()
    {
        insurance->print();
    }

};

class SavingAccount:public Account{

    public:
    double interest;
    SavingAccount(int accountNumber,double balance):Account(accountNumber,balance)
    {
        interest=0.08;
    }

    double credit(int accountNumber,double amount)
    {
        
        return balance+=amount;
    }

    double debit(double amount) 
    {
        double remaining=balance-amount;
        try{
            if(remaining<0)
            {
                throw Exception("Insufficient Balance");
            }
            else
                return balance-=amount;
        }
        catch(Exception e)
        {
            e.print();
        }
    }

    void print()
    {
        Account::print();
        cout<<"Interest : "<<interest<<endl;
    }


   
};

class CurrentAccount:public Account{

    public:
    double overdraftLimit;
    CurrentAccount(int accountNumber,double balance):Account(accountNumber,balance)
    {
       overdraftLimit=1000;
    }

    double credit(double amount)
    {
        return balance+=amount;
    }

    double debit(double amount) 
    {
        double remaining=balance-amount;
        try{
            if(remaining<overdraftLimit)
            {
                throw Exception("Insufficient Balance");
            }
            else
                return balance-=amount;
        }
        catch(Exception e)
        {
            e.print();
        }
    }

    void print()
    {
        Account::print();
        cout<<"Overdraft Limit : "<<overdraftLimit<<endl;
        cout<<endl;
    }
};

class Bank{
    public:
    string name;
    Application *application = application->getInstance();

    Bank()
    {
        name="";
    }

    Bank(string name)
    {
        this->name=name;
    }

    virtual void print() 
    {
        cout<<"Bank name : "<<name<<endl; 
    }

    virtual void addAccount(Account *account)
    {
        cout<<"Account added"<<endl;
    }

    virtual void removeAccount(int accountNumber)
    {
        cout<<"Account removed"<<endl;
    }

    virtual int creditAmountThroughAccountTransfer(int accNo,double amount)
    {
        return 0;        
    }




};

class Branch:public Bank{
    public:
    string IFSC,taluk,district,state;
    int pinCode;
    Account *account[100];
     int accountCount=0;

    Branch():Bank()
    {
        IFSC="";
        taluk="";
        district="";
        state="";
        pinCode=0;
    }

    Branch(string name,string IFSC,string taluk,string district,string state,int pinCode):Bank(name)
    {
        this->IFSC=IFSC;
        this->taluk=taluk;
        this->district=district;
        this->state=state;
        this->pinCode=pinCode;
    }

    void print()
    {
        Bank::print();
        cout<<"IFSC : "<<IFSC<<endl;
        cout<<"Taluk : "<<taluk<<endl;
        cout<<"District : "<<district<<endl;
        cout<<"State : "<<state<<endl;
        cout<<"Pin Code : "<<pinCode<<endl;
        for(int i=0;i<accountCount;i++)
        {
            account[i]->print();
        }
    }

    void addAccount(Account *account)
    {
        this->account[accountCount]=account;
        accountCount++;
    }

    void creditAmount(int accNo,double amount)
    {
        int i;
        for( i=0;i<accountCount;i++)
        {
            
            if(account[i]->accountNumber==accNo)
            {
                cout<<"Initial balance of "<<accNo<<" is : "<<account[i]->balance<<endl;
                account[i]->credit(amount);
                cout<<"Updated balance of"<<accNo<<" is : "<<account[i]->balance<<endl;
                return;
            }
            
        }

        try{
        if(i==accountCount)
                throw Exception("Account not found");
            }
            catch(Exception e)
            {
                e.print();
            }

        
    }

    int creditAmountThroughAccountTransfer(int accNo,double amount)
    {
        int i;
        for( i=0;i<accountCount;i++)
        {
            
            if(account[i]->accountNumber==accNo)
            {
               cout<<"Initial balance of "<<accNo<<" is : "<<account[i]->balance<<endl;
                account[i]->credit(amount);
                cout<<"Updated balance of"<<accNo<<" is : "<<account[i]->balance<<endl;
                return 1;
            }
            
        }
        return 0;

        
    }

    void DebitAmount(int accNo,double amount)
    {
        int i;
        for( i=0;i<accountCount;i++)
        {
            if(account[i]->accountNumber==accNo)
            {
                cout<<"Initial balance of "<<accNo<<" is : "<<account[i]->balance<<endl;
                account[i]->debit(amount);
                cout<<"Updated balance of "<<accNo<<" is : "<<account[i]->balance<<endl<<endl;
                return;
            }
        }

        try{
        if(i==accountCount)
                throw Exception("Account not found");
            }
            catch(Exception e)
            {
                e.print();
            }

        
    }

    void displayAccount(int accNo)
    {
        int i;
        for( i=0;i<accountCount;i++)
        {
            if(account[i]->accountNumber==accNo)
            {
                account[i]->print();
                return;
            }
        }

        try{
        if(i==accountCount)
                throw Exception("Account not found");
            }
            catch(Exception e)
            {
                e.print();
            }

    }

    void addLoan(Loan *loan,int accNo)
    {
        int i;
        for( i=0;i<accountCount;i++)
        {
            if(account[i]->accountNumber==accNo)
            {
                account[i]->addLoan(loan);
                break;
            }
        }

        try{
        if(i==accountCount)
                throw Exception("Account not found");
            }
            catch(Exception e)
            {
                e.print();
            }
    }

    void addInsurance(Insurance *insurance,int accNo)
    {
        int i;
        for( i=0;i<accountCount;i++)
        {
            if(account[i]->accountNumber==accNo)
            {
               
                account[i]->addInsurance(insurance);
               break;
            }
            
        }

        try{
        if(i==accountCount)
                throw Exception("Account not found");
            }
            catch(Exception e)
            {
                e.print();
            }
    }


    void removeAccount(int accNo)
    {
         int i;
        for( i=0;i<accountCount;i++)
        {
            if(account[i]->accountNumber==accNo)
            {
                 cout<<"Account with account Number "<<accNo<<" removed successfully\n";
                 accountCount--;
                account[i]=NULL;
                 while(i<accountCount)
                {
                    account[i]=account[i+1];
                    i++;
                }
                break;
            }
            
        }

        try{
        if(i==accountCount)
                throw Exception("Account not found");
            }
            catch(Exception e)
            {
                e.print();
            }
    }

    void printLoan(int accNo)
    {
        int i;
        for( i=0;i<accountCount;i++)
        {
            if(account[i]->accountNumber==accNo)
            {
               account[i]->printLoan();
               break;
            }
        }

        try{
        if(i==accountCount)
                throw Exception("Account not found");
            }
            catch(Exception e)
            {
                e.print();
            }
    }

    void printInsurance(int accountNumber)
    {
        int i;
        for( i=0;i<accountCount;i++)
        {
            if(account[i]->accountNumber==accountNumber)
            {
               account[i]->printInsurance();
            }
        }

        try{
        if(i==accountCount)
                throw Exception("Account not found");
            }
            catch(Exception e)
            {
                e.print();
            }
    }

    
};

class User{


    public:
    string name,email;
    int age;
    Account *account[10];
    int accountCount=0;

    User()
    {
        name="";
        email="";
        age=0;
    }

    User(string name,string email,int age)
    {
        this->name=name;
        this->email=email;
        this->age=age;
    }


    void print()
    {
        cout<<"Name : "<<name<<endl;
        cout<<"Email : "<<email<<endl;
        cout<<"Age : "<<age<<endl;
        for(int i=0;i<accountCount;i++)
        {
            account[i]->print();
        }
        cout<<endl;
        cout<<endl;
    }


    bool login(Application *application,int accNo)
    {
        
        if(application->login(accNo))
        {
            cout<<"Login Successful"<<endl;
            return 1;
        }
        else
        {
            cout<<"Login Failed"<<endl;
            
            return 0;
        }

    }

    
    void createAccount(Account *account)
    {
        this->account[accountCount]= account;
        accountCount++;
    }

    static void displayAllUser(User *user[],int count)
    {
        for(int i=0;i<count;i++)
        {
            user[i]->print();
        }
    }
};
