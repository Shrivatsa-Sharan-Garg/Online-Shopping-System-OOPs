#include<iostream>
#include<vector>
#include<stdexcept>
using namespace std;

template<class T>
class ProductList{
public:
    vector<T> items;

    void add(T p){
        items.push_back(p);
    }

    void displayAll(){
        for(int i=0;i<items.size();i++){
            items[i]->display();
            cout<<"\n";
        }
    }
};

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
        if(name=="")
            throw runtime_error("Name cannot be empty!");

        cout<<"Enter Price:";
        cin>>price;
        if(price<0)
            throw runtime_error("Price cannot be negative!");

        cout<<"Enter Quantity:";
        cin>>quantity;
        if(quantity<0)
            throw runtime_error("Quantity cannot be negative!");

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
        if(brand=="")
            throw runtime_error("Brand cannot be empty!");
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
        if(ram<=0)
            throw runtime_error("Invalid RAM!");

        cout<<"Enter Storage(GB):";
        cin>>storage;
        if(storage<=0)
            throw runtime_error("Invalid Storage!");

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
        if(os=="")
            throw runtime_error("OS cannot be empty!");
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

        if(subType=="" || expiry=="")
            throw runtime_error("Food type or expiry cannot be empty!");
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

        if(size=="" || color=="")
            throw runtime_error("Size or color cannot be empty!");
    }

    void display(){
        Product::display();
        cout<<"Size:"<<size<<"\nColor:"<<color<<"\n";
    }
};

int main(){
    ProductList<Product*> products;
    int choice;

    try{
        do{
            cout<<"\n---Customer Menu---\n";
            cout<<"1.View Products\n2.Add Laptop\n3.Add Mobile\n4.Add Food\n5.Add Clothing\n6.Exit\nEnter choice:";
            cin>>choice;
            cin.ignore();

            if(choice==1){
                cout<<"\n";
                products.displayAll();
            }
            else if(choice==2){
                Laptop* l=new Laptop();
                l->input();
                products.add(l);
            }
            else if(choice==3){
                Mobile* m=new Mobile();
                m->input();
                products.add(m);
            }
            else if(choice==4){
                Food* f=new Food();
                f->input();
                products.add(f);
            }
            else if(choice==5){
                Clothing* c=new Clothing();
                c->input();
                products.add(c);
            }
            else if(choice==6){
                cout<<"Exiting...\n";
            }
            else{
                throw runtime_error("Invalid menu choice!");
            }

        }while(choice!=6);
    }
    catch(exception &e){
        cout<<"\nError: "<<e.what()<<"\n";
    }

    return 0;
}
