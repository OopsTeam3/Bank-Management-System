#include<iostream>
#include<time.h>
#include<fstream>
#include "User.cpp"
using namespace std;


Application* Application:: application=0;



void BranchList()
{
    cout<<"Please enter the branch where your account is in\n";
    cout<<"1. Hubli"<<endl;
    cout<<"2. Dharwad"<<endl;
    cout<<"3. Manglore"<<endl;
    cout<<"4. Banglore"<<endl;
    cout<<"5. Mysore"<<endl;
}

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
    Application *application=Application::getInstance();
     Branch branch[5];
     branch[0]=Branch("SBI","SBI0000","Hubli","Karnataka","India",580031);
      branch[1]=Branch("SBI","SBI0001","Dharwad","Karnataka","India",580041);
      branch[2]=Branch("SBI","SBI0002","Manglore","Karnataka","India",560031);
      branch[3]=Branch("SBI","SBI0003","Banglore","Karnataka","India",510021);
      branch[4]=Branch("SBI","SBI0004","Mysore","Karnataka","India",560031);

    
    User *user[100];
    int count=0;
     int choice;
    do
    {
        cout<<"\nEnter your choice\n";
        cout<<"1. Add account\n";
        cout<<"2. Remove account\n";
        cout<<"3. Print account\n";
        cout<<"4. Credit amount\n";
        cout<<"5. Debit amount\n";
        cout<<"6. Add Loan\n";
        cout<<"7. Add Insurance\n";
        cout<<"8. Display loan details\n";
        cout<<"9. Display Insurance details\n";
        cout<<"10. Transfer into another account\n";
        cout<<"11. Display all accounts of an user\n";
        cout<<"12. Display all accounts of a single branch\n";
        cout<<"13. Display all accounts of all branches\n";
        cout<<"14. Exit\n";
        cin>>choice;

        int accNo;
        if(choice!=1 && choice!=14 && choice!=11 && choice!=12 && choice!=13)
        
        {
            cout<<"Enter Account Number : ";
            cin>>accNo;
            if(!application->login(accNo))
            {
                cout<<"Do you want to create account ?"<<endl;
                cout<<"1.Yes"<<endl;
                cout<<"2.No"<<endl;
                int choice1;
                cin>>choice1;
                if(choice1==1)
                {
                    choice=1;
                }
                else
                {
                    cout<<"Exiting"<<endl;
                    exit(0);
                }
            }
        }
        int branchChoice;
        if(choice!=14 && choice!=11 && choice!=13)
        {
            

        BRANCH:       
                        BranchList();
                        cin>>branchChoice;
                        try
                        {
                            if(branchChoice>5 || branchChoice<1)
                                throw Exception("Invalid Branch");
                        }
                        catch(Exception e)
                        {
                            e.print();
                            goto BRANCH;
                        } 
        }

    switch(choice)
    {
         
        
        
        case 1: 
        {
            int accountType;
            Account *account;
            cout<<"1. Saving Account"<<endl;
            cout<<"2. Current Account"<<endl;
            cin>>accountType;
            
  GENERATE: accNo=100000000+rand()%900000000;

            //Check if account number generated is unique

            if(accNumberNotUnique(accNo))
                goto GENERATE;
            cout<<"Your Account Number is "<<accNo<<endl;
                    application->createAccount(accNo);
            if(accountType==1)
                {
            
                    
                    double balance,interest;
        RETRY:      cout<<"Enter balance : ";
                    try
                    {
                        cin>>balance;
                        if(balance<0)
                            throw Exception("Balance cannot be negative");
                    }
                    catch(Exception e)
                    {
                        e.print();
                        goto RETRY;
                    }

                    account = new SavingAccount(accNo,balance); 
                    
                    branch[branchChoice-1].addAccount(account);                        
                }
                    else
                    {
                        cout<<"Your Account Number is "<<accNo<<endl;
                        double balance;
        RETRY2:         cout<<"Enter balance : ";
                        try
                        {
                            cin>>balance;
                            if(balance<0)
                                throw Exception("Balance cannot be negative");
                        }
                        catch(Exception e)
                        {
                            e.print();
                            goto RETRY2;
                        }
                        account = new CurrentAccount(accNo,balance);                        
       

                        branch[branchChoice-1].addAccount(account); 
                    }

        SWITCH:     cout<<"Are you an existing customer?\n";
                    cout<<"1.Yes\n";
                    cout<<"2.No\n";
                    int choice1;
                    cin>>choice1;
                    cout<<"Enter your email\n";
                    string email;
                    cin>>email;

                    switch(choice1)
                    {
                        
                        case 1:
                        {
                            int flag=0;
                            for(int i=0;i<count;i++)
                            {
                                if(user[i]->email==email)
                                {
                                    flag=1;
                                    user[i]->createAccount(account);
                                    break;
                                }
                            }
                            if(flag==0)
                            {
                                cout<<"No entries found\n";
                                cout<<"Do you want to create account?\n";
                                cout<<"1.Yes\n";
                                cout<<"2.No\n";
                                cin>>choice1;
                                if(choice1==1)
                                goto SWITCH;
                            }
                        }
                        break;

                        case 2:
                        {
                            int flag=0;
                            for(int i=0;i<count;i++)
                            {
                                if(user[i]->email==email)
                                {
                                    cout<<"You are already an user\n";
                                    user[i]->createAccount(account);
                                    flag++;
                                    break;
                                }
                            }
                            if(!flag)
                            {
                                cout<<"Enter your name\n";
                                string name;
                                cin>>name;
                                cout<<"Enter your age\n";
                                int age;
                                try{
                                cin>>age;
                                if(age<18)
                                    throw Exception("Age cannot be less than 18");
                                }
                                catch(Exception e)
                                {
                                    e.print();
                                    goto SWITCH;
                                }
                                User *newUser=new User(name,email,age);
                                user[count]=newUser;
                                count++;
                                user[count-1]->createAccount(account);
                            }
                        }
                    }

                    break;
               


        }
        
        case 2:
        {
            branch[branchChoice-1].removeAccount(accNo);
            
        }
            break;

        case 3:
        {
            branch[branchChoice-1].displayAccount(accNo);
           
            break;
        }

        case 4: 
        {
            cout<<"Enter the amount to be credited\n";
            double amount;
            cin>>amount;
            branch[branchChoice-1].creditAmount(accNo,amount);
            

            break;
        }

        case 5:
        {
            cout<<"Enter the amount to be Debited\n";
            double amount;
            cin>>amount;
            branch[branchChoice-1].DebitAmount(accNo,amount);
            
            break;
        }

        case 6:
        {
            int loanType;
            cout<<"Enter loan type\n";
            cout<<"1. Home Loan\n";
            cout<<"2. Vehicle Loan\n";
            cout<<"3. Education Loan\n";
            cin>>loanType;
            double loanAmount;
            int tenure;
            cout<<"Enter loan amount : ";
            cin>>loanAmount;
            cout<<"Enter loan tenure : ";
            cin>>tenure;
            Loan *loan;

            
            if(loanType==1)
            {
                loan= new HomeLoan(loanAmount,tenure);
                
            }

            else if(loanType==2)
            {
                loan= new VehicleLoan(loanAmount,tenure);
            }

            else
            {
                loan= new EducationLoan(loanAmount,tenure);
            }

                branch[branchChoice-1].addLoan(loan,accNo);
                loan->calculateAmount();

                
            break;
        
        }

        case 7:
        {
            int InsuranceType;
            cout<<"Enter Insrance type\n";
            cout<<"1. Life Insurance\n";
            cout<<"2. Vehicle Insurance\n";
            cout<<"3. Home Loan\n";
            cin>>InsuranceType;
            double premium,amount;
            int months,id;
            cout<<"Enter premium : ";
            cin>>premium;
            cout<<"Enter amount : ";
            cin>>amount;
            cout<<"Enter months : ";
            cin>>months;
            id=rand()%1000;

            Insurance *insurance;

            if(InsuranceType==1)
            {
                
                insurance= new LifeInsurance(id,premium,amount,months);
            }

            else if(InsuranceType==2)
            {
                int vId;
                string vehicleType,vehicleModel,vehicleColor;
                cout<<"Enter vehicle id : ";
                cin>>vId;
                cout<<"Enter vehicle type : ";
                cin>>vehicleType;
                cout<<"Enter vehicle model : ";
                cin>>vehicleModel;
                cout<<"Enter vehicle color : ";
                cin>>vehicleColor;
                insurance= new VehicleInsurance(id,premium,amount,months,vId,vehicleType,vehicleModel,vehicleColor);
            }

            else
            {
                int hId;
                string homeType;
                cout<<"Enter home id : ";
                cin>>hId;
                cout<<"Enter home type : ";
                cin>>homeType;
                insurance= new HomeInsurance(id,premium,amount,months,hId,homeType);
            }
            
                branch[branchChoice-1].addInsurance(insurance,accNo);
                cout<<"Premium amount will be cut from your account\n";
                branch[branchChoice-1].DebitAmount(accNo,premium);
               
            break; 
        }

        case 8:
        {
            branch[branchChoice-1].printLoan(accNo);
           

            break;
        }

        case 9:
        {
            branch[branchChoice-1].printInsurance(accNo);
            
            break;
        }

        case 10:
        {

            cout<<"Enter the account number to send money\n";
            int accNo1;
            cin>>accNo1;
            cout<<"Enter the amount to be sent\n";
            double amount;
            cin>>amount;
            branch[branchChoice-1].DebitAmount(accNo,amount);
            int flag=0,i;
            for( i=0;i<5;i++)
            {
                   flag+= branch[i].creditAmountThroughAccountTransfer(accNo1,amount);
                //    if(flag)
                //     break;
                
            }

            try{
                if(!flag)
                throw Exception("No Account found\n");
            }

            catch(Exception e)
            {
                e.print();
            }
        }
        break;

        case 11: 
        {
            cout<<"Enter the email\n";
            string email;
            cin>>email;
            for(int i=0;i<count;i++)
            {
                if(user[i]->email==email)
                {
                    user[i]->print();
                    break;
                }
            }
        }
        break;

        case 12:branch[branchChoice-1].print();
        break;

        case 13:
        {
            for(int i=0;i<5;i++)
            {
                branch[i].print();
                cout<<endl;
                cout<<endl;
            }
        }
        break;
        default:cout<<"Invalid option\n";

        
    
    }

    }while(choice!=14);

  
        return 0;

        
}