#include<iostream>
using namespace std;

class Insurance{
    public:
    int insuranceId;
    double premium;
    double amount;
    int months;

    Insurance()
    {
        insuranceId=0;
        premium=0;
        amount=0;
        months=0;
    }

    Insurance(int insuranceId,double premium,double amount,int months)
    {
        this->insuranceId=insuranceId;
        this->premium=premium;
        this->amount=amount;
        this->months=months;
    }

    virtual void print()
    {
        cout<<"Insurance Id : "<<insuranceId<<endl;
        cout<<"Premium : "<<premium<<endl;
        cout<<"Amount : "<<amount<<endl;
        cout<<"Months : "<<months<<endl;
    }

    virtual void calculateAmount()
    {
        double totalAmount=premium*amount*months;
        cout<<"Total Amount : "<<totalAmount<<endl;
    }


};

class LifeInsurance:public Insurance{
    public:

    LifeInsurance():Insurance(){
       
    }

    LifeInsurance(int insuranceId,double premium,double amount,int months):Insurance(insuranceId,premium,amount,months)
    {
    }

    void print()
    {
        Insurance::print();
        
    }

    void calculateAmount()
    {
        double totalAmount=premium*amount*months;
        cout<<"Total Amount : "<<totalAmount<<endl;
    }
};

class VehicleInsurance : public Insurance{
    public:
    int vehicleId;
    string vehicleType,vehicleModel,vehicleColor;


    VehicleInsurance():Insurance(){
        vehicleId=0;
        vehicleType="";
        vehicleModel="";
        vehicleColor="";
    }

    VehicleInsurance(int insuranceId,double premium,double amount,int months,int vehicleId,string vehicleType,string vehicleModel,string vehicleColor)
    :Insurance(insuranceId,premium,amount,months)
    {
        this->vehicleId=vehicleId;
        this->vehicleType=vehicleType;
        this->vehicleModel=vehicleModel;
        this->vehicleColor=vehicleColor;
    }

      void calculateAmount()
    {
        double totalAmount=premium*amount*months;
        cout<<"Total Amount : "<<totalAmount<<endl;
    }

    void print()
    {
        Insurance::print();
        cout<<"Vehicle Id : "<<vehicleId<<endl;
        cout<<"Vehicle Type : "<<vehicleType<<endl;
        cout<<"Vehicle Model : "<<vehicleModel<<endl;
        cout<<"Vehicle Color : "<<vehicleColor<<endl;
        calculateAmount();
    }

  
};

class HomeInsurance:public Insurance{
    public:
    int homeId;
    string homeType;

    HomeInsurance():Insurance(){
        homeId=0;
        homeType="";
    }

    HomeInsurance(int insuranceId,double premium,double amount,int months,int homeId,string homeType):Insurance(insuranceId,premium,amount,months)
    {
        this->homeId=homeId;
        this->homeType=homeType;
    }
    void calculateAmount()
    {
        double totalAmount=premium*amount*months;
        cout<<"Total Amount : "<<totalAmount<<endl;
    }

    void print()
    {
        Insurance::print();
        cout<<"Home Id : "<<homeId<<endl;
        cout<<"Home Type : "<<homeType<<endl;
        calculateAmount();
    }

    
};