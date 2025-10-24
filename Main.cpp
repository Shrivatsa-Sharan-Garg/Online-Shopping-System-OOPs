#include<iostream>
using namespace std;

class Product{
public:
    int id;
    string name;
    float price;
    int quantity;

    virtual void input(){
        cout<<"Enter Product ID:";
        cin>>id;
        cin.ignore();

        cout<<"Enter Product Name:";
        getline(cin,name);

        cout<<"Enter Price:";
        cin>>price;

        cout<<"Enter Quantity:";
        cin>>quantity;
        cin.ignore();
    }

    virtual void display(){
        cout<<"ID:"<<id<<"\nName:"<<name<<"\nPrice:"<<price<<"\nQuantity:"<<quantity<<"\n";
    }
};

class Electronics:public Product{
public:
    string brand;

    virtual void input(){
        Product::input();

        cout<<"Enter Brand:";
        getline(cin,brand);
    }

    virtual void display(){
        Product::display();

        cout<<"Brand:"<<brand<<"\n";
    }
};

class Laptop:public Electronics{
public:
    int ram,storage;

    void input(){
        Electronics::input();

        cout<<"Enter RAM(GB):";
        cin>>ram;

        cout<<"Enter Storage(GB):";
        cin>>storage;
        cin.ignore();
    }

    void display(){
        Electronics::display();

        cout<<"RAM:"<<ram<<"GB\nStorage:"<<storage<<"GB\n";
    }
};

class Mobile:public Electronics{
public:
    string os;

    void input(){
        Electronics::input();

        cout<<"Enter OS:";
        getline(cin,os);
    }

    void display(){
        Electronics::display();

        cout<<"OS:"<<os<<"\n";
    }
};

class Food:public Product{
public:
    string subType;
    string expiry;

    void input(){
        Product::input();

        cout<<"Enter Type(Fruit/Vegetable/Packaged):";
        getline(cin,subType);

        cout<<"Enter Expiry Date:";
        getline(cin,expiry);
    }

    void display(){
        Product::display();

        cout<<"Type:"<<subType<<"\nExpiry:"<<expiry<<"\n";
    }
};

class Clothing:public Product{
public:
    string size,color;

    void input(){
        Product::input();

        cout<<"Enter Size:";
        getline(cin,size);

        cout<<"Enter Color:";
        getline(cin,color);
    }

    void display(){
        Product::display();
        cout<<"Size:"<<size<<"\nColor:"<<color<<"\n";
    }
};

int main(){
    Product* products[100];
    int n=0;
    int choice;

    do{
        cout<<"\n---Customer Menu---\n";
        cout<<"1.View Products\n2.Add Laptop\n3.Add Mobile\n4.Add Food\n5.Add Clothing\n6.Exit\nEnter choice:";
        cin>>choice;
        cin.ignore();

        if(choice==1){
            cout<<"\n";
            for(int i=0;i<n;i++){
                products[i]->display();
                cout<<"\n";
            }
        }
        else if(choice==2){
            Laptop* l=new Laptop();
            l->input();
            products[n++]=l;
        }
        else if(choice==3){
            Mobile* m=new Mobile();
            m->input();
            products[n++]=m;
        }
        else if(choice==4){
            Food* f=new Food();
            f->input();
            products[n++]=f;
        }
        else if(choice==5){
            Clothing* c=new Clothing();
            c->input();
            products[n++]=c;
        }
        else if(choice==6){
            cout<<"Exiting...\n";
        }
        else{
            cout<<"Invalid choice!\n";
        }

    }while(choice!=6);

    for(int i=0;i<n;i++){
        delete products[i];
    }

    return 0;
}
