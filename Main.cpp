#include <iostream>
#include <vector>
#include <string>

using namespace std;

/////////////////////
// Product classes //
/////////////////////

class Product
{
public:
    int id;
    string name;
    double price;
    int stock;

    Product()
    :id(0),name(""),price(0.0),stock(0)
    {
    }

    Product(int i,string n,double p,int s)
    :id(i),name(n),price(p),stock(s)
    {
    }

    virtual void input()
    {
        cout<<"Enter Product ID:";cin>>id;cin.ignore();
        cout<<"Enter Product Name:";getline(cin,name);
        cout<<"Enter Price:";cin>>price;cin.ignore();
        cout<<"Enter Stock:";cin>>stock;cin.ignore();
    }

    virtual void display()
    {
        cout<<"ID:"<<id<<"\nName:"<<name<<"\nPrice:"<<price<<"Rs\nStock:"<<stock<<"\n";
    }

    virtual string getCategory()
    {
        return "Product";
    }

    virtual ~Product()
    {
    }
};

class Electronics:public Product
{
public:
    string brand;

    Electronics()
    :Product(),brand("")
    {
    }

    Electronics(int i,string n,double p,int s,string b)
    :Product(i,n,p,s),brand(b)
    {
    }

    void input() override
    {
        Product::input();
        cout<<"Enter Brand:";getline(cin,brand);
    }

    void display() override
    {
        Product::display();
        cout<<"Category:Electronics\nBrand:"<<brand<<"\n";
    }

    string getCategory() override
    {
        return "Electronics";
    }
};

class Laptop:public Electronics
{
public:
    int ram;
    int storage;

    Laptop()
    :Electronics(),ram(0),storage(0)
    {
    }

    Laptop(int i,string n,double p,int s,string b,int r,int st)
    :Electronics(i,n,p,s,b),ram(r),storage(st)
    {
    }

    void input() override
    {
        Electronics::input();
        cout<<"Enter RAM(GB):";cin>>ram;cin.ignore();
        cout<<"Enter Storage(GB):";cin>>storage;cin.ignore();
    }

    void display() override
    {
        Electronics::display();
        cout<<"Type:Laptop\nRAM:"<<ram<<"GB\nStorage:"<<storage<<"GB\n";
    }

    string getCategory() override
    {
        return "Laptop";
    }
};

class Mobile:public Electronics
{
public:
    string os;

    Mobile()
    :Electronics(),os("")
    {
    }

    Mobile(int i,string n,double p,int s,string b,string o)
    :Electronics(i,n,p,s,b),os(o)
    {
    }

    void input() override
    {
        Electronics::input();
        cout<<"Enter OS:";getline(cin,os);
    }

    void display() override
    {
        Electronics::display();
        cout<<"Type:Mobile\nOS:"<<os<<"\n";
    }

    string getCategory() override
    {
        return "Mobile";
    }
};

class Food:public Product
{
public:
    string type;
    string expiry;

    Food()
    :Product(),type(""),expiry("")
    {
    }

    Food(int i,string n,double p,int s,string t,string e)
    :Product(i,n,p,s),type(t),expiry(e)
    {
    }

    void input() override
    {
        Product::input();
        cout<<"Enter Type(Fruit/Vegetable/Packaged):";getline(cin,type);
        cout<<"Enter Expiry Date:";getline(cin,expiry);
    }

    void display() override
    {
        Product::display();
        cout<<"Category:Food\nType:"<<type<<"\nExpiry:"<<expiry<<"\n";
    }

    string getCategory() override
    {
        return "Food";
    }
};

class Clothing:public Product
{
public:
    string size;
    string color;

    Clothing()
    :Product(),size(""),color("")
    {
    }

    Clothing(int i,string n,double p,int s,string sz,string c)
    :Product(i,n,p,s),size(sz),color(c)
    {
    }

    void input() override
    {
        Product::input();
        cout<<"Enter Size:";getline(cin,size);
        cout<<"Enter Color:";getline(cin,color);
    }

    void display() override
    {
        Product::display();
        cout<<"Category:Clothing\nSize:"<<size<<"\nColor:"<<color<<"\n";
    }

    string getCategory() override
    {
        return "Clothing";
    }
};

/////////////////////
// Order & Cart    //
/////////////////////

struct OrderItem
{
    int id;
    string name;
    double price;
    int qty;
};

struct Order
{
    string customerName;
    string address;
    string paymentStatus;
    vector<OrderItem> items;
    double total;
};

class Cart
{
public:
    vector<pair<Product*,int>> items; // product pointer + qty

    void addItem(Product* p,int qty)
    {
        if(p==nullptr)
        {
            cout<<"Error:Product not found.\n";
            return;
        }

        if(qty<=0)
        {
            cout<<"Error:Quantity must be positive.\n";
            return;
        }

        if(p->stock<qty)
        {
            cout<<"Error:Not enough stock available.\n";
            return;
        }

        // reserve stock
        p->stock-=qty;

        for(int i=0;i<(int)items.size();i++)
        {
            if(items[i].first->id==p->id)
            {
                items[i].second+=qty;
                cout<<"Added to existing cart entry.\n";
                return;
            }
        }

        items.push_back(make_pair(p,qty));
        cout<<"Item added to cart.\n";
    }

    void removeItemById(int id)
    {
        for(int i=0;i<(int)items.size();i++)
        {
            if(items[i].first->id==id)
            {
                // restore stock
                items[i].first->stock+=items[i].second;

                items.erase(items.begin()+i);
                cout<<"Removed item from cart.\n";
                return;
            }
        }

        cout<<"Error:Item not found in cart.\n";
    }

    void viewCart()
    {
        if(items.empty())
        {
            cout<<"Cart is empty.\n";
            return;
        }

        cout<<"\n--- Cart Items ---\n";

        for(int i=0;i<(int)items.size();i++)
        {
            Product* p=items[i].first;
            int q=items[i].second;

            cout<<"ID:"<<p->id
                <<" | "<<p->name
                <<" | Qty:"<<q
                <<" | Unit:"<<p->price<<"Rs"
                <<" | Sub:"<<p->price*q<<"Rs\n";
        }
    }

    double getTotal()
    {
        double total=0.0;

        for(auto &it:items)
        {
            total+=it.first->price*it.second;
        }

        return total;
    }

    double applyCoupon(string code,double total)
    {
        if(code=="DISC10")
        {
            cout<<"DISC10 applied:10% off\n";
            return total*0.90;
        }
        else if(code=="SAVE50")
        {
            cout<<"SAVE50 applied:50Rs off\n";
            total-=50;
            if(total<0) total=0;
            return total;
        }
        else if(code=="WELCOME5")
        {
            cout<<"WELCOME5 applied:5% off\n";
            return total*0.95;
        }
        else
        {
            cout<<"Error:Invalid coupon.\n";
            return total;
        }
    }

    Order checkout(string customerName)
    {
        Order ord;

        if(items.empty())
        {
            cout<<"Error:Cart is empty.\n";
            return ord;
        }

        double total=getTotal();

        cout<<"Bill Amount:"<<total<<"Rs\n";

        cout<<"Apply coupon? (y/n):";char c;cin>>c;cin.ignore();

        if(c=='y'||c=='Y')
        {
            cout<<"Enter coupon code:";string code;getline(cin,code);
            total=applyCoupon(code,total);
            cout<<"New Total:"<<total<<"Rs\n";
        }

        cout<<"Enter delivery address:";getline(cin,ord.address);

        ord.customerName=customerName;

        if(total>0.0)
        {
            ord.paymentStatus="Successful";
        }
        else
        {
            ord.paymentStatus="Failed";
        }

        for(int i=0;i<(int)items.size();i++)
        {
            OrderItem oi;
            oi.id=items[i].first->id;
            oi.name=items[i].first->name;
            oi.price=items[i].first->price;
            oi.qty=items[i].second;
            ord.items.push_back(oi);
        }

        ord.total=total;

        // clear cart after order
        items.clear();

        cout<<"Order placed. Payment status:"<<ord.paymentStatus<<"\n";

        return ord;
    }
};

/////////////////////
// Admin class     //
/////////////////////

class Admin
{
public:
    vector<Product*> catalog;
    vector<Order> orders;
    int nextID;

    Admin()
    :nextID(100)
    {
    }

    void preload()
    {
        // Electronics
        catalog.push_back(new Laptop(nextID++,"Dell XPS",120000,5,"Dell",16,512));
        catalog.push_back(new Laptop(nextID++,"HP Pavilion",65000,3,"HP",8,256));
        catalog.push_back(new Mobile(nextID++,"Phone Z",35000,10,"PhoneCo","Android"));

        // Food
        catalog.push_back(new Food(nextID++,"Apples",80,100,"Fruit","2026-01-01"));
        catalog.push_back(new Food(nextID++,"Chips",40,200,"Packaged","2026-06-01"));
        catalog.push_back(new Food(nextID++,"Milk Packet",50,150,"Packaged","2025-12-31"));

        // Clothing
        catalog.push_back(new Clothing(nextID++,"T-Shirt",399,50,"M","Blue"));
        catalog.push_back(new Clothing(nextID++,"Jeans",999,20,"L","Black"));
        catalog.push_back(new Clothing(nextID++,"Sneakers",2499,15,"42","White"));
    }

    Product* findById(int id)
    {
        for(int i=0;i<(int)catalog.size();i++)
        {
            if(catalog[i]->id==id)
            {
                return catalog[i];
            }
        }

        return nullptr;
    }

    void showCatalog()
    {
        if(catalog.empty())
        {
            cout<<"Catalog is empty.\n";
            return;
        }

        cout<<"\n---- Catalog ----\n";

        for(int i=0;i<(int)catalog.size();i++)
        {
            catalog[i]->display();
            cout<<"Category:"<<catalog[i]->getCategory()<<"\n";
            cout<<"----------------\n";
        }
    }

    void addProductMenu()
    {
        cout<<"\nSelect Category:\n";
        cout<<"1.Electronics\n";
        cout<<"2.Food\n";
        cout<<"3.Clothing\n";
        cout<<"Enter:";int cat;cin>>cat;cin.ignore();

        if(cat==1)
        {
            cout<<"1.Mobile\n";
            cout<<"2.Laptop\n";
            cout<<"Enter:";int sub;cin>>sub;cin.ignore();

            if(sub==1)
            {
                Mobile* m=new Mobile();
                m->id=nextID++;
                m->input();
                catalog.push_back(m);
                cout<<"Mobile added.\n";
            }
            else if(sub==2)
            {
                Laptop* l=new Laptop();
                l->id=nextID++;
                l->input();
                catalog.push_back(l);
                cout<<"Laptop added.\n";
            }
            else
            {
                cout<<"Error:Invalid option.\n";
            }
        }
        else if(cat==2)
        {
            cout<<"1.Snacks\n";
            cout<<"2.Dairy\n";
            cout<<"Enter:";int sub;cin>>sub;cin.ignore();

            if(sub==1 || sub==2)
            {
                Food* f=new Food();
                f->id=nextID++;
                f->input();
                catalog.push_back(f);
                cout<<"Food added.\n";
            }
            else
            {
                cout<<"Error:Invalid option.\n";
            }
        }
        else if(cat==3)
        {
            cout<<"1.Men\n";
            cout<<"2.Women\n";
            cout<<"Enter:";int sub;cin>>sub;cin.ignore();

            if(sub==1 || sub==2)
            {
                Clothing* c=new Clothing();
                c->id=nextID++;
                c->input();
                catalog.push_back(c);
                cout<<"Clothing added.\n";
            }
            else
            {
                cout<<"Error:Invalid option.\n";
            }
        }
        else
        {
            cout<<"Error:Invalid category.\n";
        }
    }

    void deleteProductById()
    {
        cout<<"Enter Product ID to delete:";int id;cin>>id;cin.ignore();

        for(int i=0;i<(int)catalog.size();i++)
        {
            if(catalog[i]->id==id)
            {
                delete catalog[i];
                catalog.erase(catalog.begin()+i);
                cout<<"Product deleted.\n";
                return;
            }
        }

        cout<<"Error:Product not found.\n";
    }

    void updateStockById()
    {
        cout<<"Enter Product ID to update:";int id;cin>>id;

        Product* p=findById(id);

        if(p==nullptr)
        {
            cout<<"Error:Product not found.\n";
            cin.ignore();
            return;
        }

        cout<<"Current stock:"<<p->stock<<"\n";
        cout<<"Enter new stock:";int s;cin>>s;cin.ignore();

        p->stock=s;

        cout<<"Stock updated.\n";
    }

    void viewOrders()
    {
        if(orders.empty())
        {
            cout<<"No orders placed yet.\n";
            return;
        }

        cout<<"\n---- Orders ----\n";

        for(int i=0;i<(int)orders.size();i++)
        {
            Order &o=orders[i];

            cout<<"Order#"<<i+1<<" | Total:"<<o.total<<"Rs"<<" | Payment:"<<o.paymentStatus<<"\n";
            cout<<"Address:"<<o.address<<"\n";
            cout<<"Items:\n";

            for(int j=0;j<(int)o.items.size();j++)
            {
                cout<<" - "<<o.items[j].name<<" x"<<o.items[j].qty<<" | "<<o.items[j].price<<"Rs\n";
            }

            cout<<"----------------\n";
        }
    }
};

///////////////////////
// Menus             //
///////////////////////

void adminMenu(Admin &admin)
{
    string u;
    string p;

    cout<<"Enter admin username:";cin>>u;
    cout<<"Enter admin password:";cin>>p;

    if(!(u=="admin" && p=="1234"))
    {
        cout<<"Error:Wrong credentials.\n";
        return;
    }

    while(true)
    {
        cout<<"\n--- ADMIN MENU ---\n";
        cout<<"1.Show Catalog\n";
        cout<<"2.Add Product\n";
        cout<<"3.Delete Product\n";
        cout<<"4.Update Stock\n";
        cout<<"5.View Orders\n";
        cout<<"6.Back\n";
        cout<<"Enter:";int ch;cin>>ch;cin.ignore();

        if(ch==1)
        {
            admin.showCatalog();
        }
        else if(ch==2)
        {
            admin.addProductMenu();
        }
        else if(ch==3)
        {
            admin.deleteProductById();
        }
        else if(ch==4)
        {
            admin.updateStockById();
        }
        else if(ch==5)
        {
            admin.viewOrders();
        }
        else if(ch==6)
        {
            break;
        }
        else
        {
            cout<<"Error:Invalid choice.\n";
        }
    }
}

void customerMenu(Admin &admin)
{
    Cart cart;

    cout<<"Enter your name:";cin.ignore();string customer;getline(cin,customer);

    while(true)
    {
        cout<<"\n--- CUSTOMER MENU ---\n";
        cout<<"1.View Catalog\n";
        cout<<"2.Add Item\n";
        cout<<"3.Remove Item\n";
        cout<<"4.View Cart\n";
        cout<<"5.Checkout\n";
        cout<<"6.Back\n";
        cout<<"Enter:";int ch;cin>>ch;cin.ignore();

        if(ch==1)
        {
            admin.showCatalog();
        }
        else if(ch==2)
        {
            cout<<"Enter product ID:";int id;cin>>id;cin.ignore();
            Product* p=admin.findById(id);

            if(p==nullptr)
            {
                cout<<"Product not found.\n";
                continue;
            }

            cout<<"Enter quantity:";int q;cin>>q;cin.ignore();

            cart.addItem(p,q);
        }
        else if(ch==3)
        {
            cout<<"Enter product ID to remove:";int id;cin>>id;cin.ignore();
            cart.removeItemById(id);
        }
        else if(ch==4)
        {
            cart.viewCart();
        }
        else if(ch==5)
        {
            Order ord=cart.checkout(customer);

            if(!ord.items.empty())
            {
                admin.orders.push_back(ord);
            }
        }
        else if(ch==6)
        {
            break;
        }
        else
        {
            cout<<"Error:Invalid choice.\n";
        }
    }
}

int main()
{
    Admin admin;
    admin.preload();

    while(true)
    {
        cout<<"\n=== MAIN MENU ===\n";
        cout<<"1.Customer\n";
        cout<<"2.Admin\n";
        cout<<"3.Exit\n";
        cout<<"Enter:";int choice;cin>>choice;cin.ignore();

        if(choice==1)
        {
            customerMenu(admin);
        }
        else if(choice==2)
        {
            adminMenu(admin);
        }
        else if(choice==3)
        {
            break;
        }
        else
        {
            cout<<"Error:Invalid choice.\n";
        }
    }

    cout<<"Exiting...\n";
    return 0;
}
