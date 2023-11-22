#include <iostream>
using namespace std;

class Loan{
    public:
    double loanAmount;
    int tenure;
    double totalPayableAmount;
    Loan()
    {
        loanAmount=0;
        tenure=0;
        totalPayableAmount=0.0;
    }

    Loan(double n,int m)
    {
        loanAmount=n;
        tenure=m;
        totalPayableAmount=0.0;
    }

    virtual void calculateAmount()
    {

    }

   virtual void print()
    {
        cout<<"Loan Amount : "<<loanAmount<<endl;
        cout<<"Tenure : "<<tenure<<endl;
    }
};

class EducationLoan:public Loan{
    public:
    double interest;
    EducationLoan()
    {
        interest=0;
    }

    EducationLoan(double n,int m)
    {
        loanAmount=n;
        tenure=m;
        interest=0.085;
    }

    void calculateAmount()
    {
        Loan::totalPayableAmount=loanAmount+(loanAmount*interest/100);
    }

    void print()
    {
        cout<<"Loan Amount : "<<loanAmount<<endl;
        cout<<"Tenure : "<<tenure<<endl;
        cout<<"Total Payable Amount : "<<totalPayableAmount<<endl;
    }
};

class HomeLoan:public Loan{
    public:
    double interest;
    HomeLoan()
    {
        interest=0;
    }

    HomeLoan(double n,int m)
    {
        loanAmount=n;
        tenure=m;
        interest=0.1;
        totalPayableAmount=0.0;
    }

    void calculateAmount()
    {
        Loan::totalPayableAmount=loanAmount+(loanAmount*interest);
    }

    void print()
    {
        cout<<"Loan Amount : "<<loanAmount<<endl;
        cout<<"Tenure : "<<tenure<<endl;
        cout<<"Total Payable Amount : "<<Loan::totalPayableAmount<<endl;
    }
};

class VehicleLoan:public Loan{
    public:
    double interest;
    VehicleLoan()
    {
        interest=0;
    }

    VehicleLoan(double n,int m)
    {
        loanAmount=n;
        tenure=m;
        interest=0.12;
        totalPayableAmount=0.0;
    }

    void calculateAmount()
    {
        Loan::totalPayableAmount=loanAmount+(loanAmount*interest/100);
    }

    void print()
    {
        cout<<"Loan Amount : "<<loanAmount<<endl;
        cout<<"Tenure : "<<tenure<<endl;
        cout<<"Total Payable Amount : "<<Loan::totalPayableAmount<<endl;
    }
};