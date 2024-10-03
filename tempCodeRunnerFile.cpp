#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Product
{
private:
    string name;
    float price;

public:
    Product(const string &name, float price)
    {
        this->name = name;
        this->price = price;
    }

    // Getter for name
    string getName() const
    {
        return this->name;
    }

    // Getter for price
    float getPrice() const
    {
        return this->price;
    }

    // Mutator for price
    void setPrice(float price)
    {
        if (price > 0)
        {
            this->price = price;
        }
        else
        {
            cout << "Price must be greater than zero." << endl;
        }
    }

    void displayDetails() const
    {
        cout << "-> " << this->name << " - Rs." << fixed << setprecision(2) << this->price << endl;
    }
};

class Customer
{
private:
    string username;
    string password;
    vector<Product *> cart;

    static int totalCustomers;
    static float totalRevenue;

public:
    Customer(const string &username, const string &password)
    {
        this->username = username;
        this->password = password;
        totalCustomers++;
    }

    ~Customer()
    {
        for (Product *product : cart)
        {
            delete product;
        }
        cart.clear();
        cout << "Customer " << username << "'s cart has been cleared and memory deallocated." << endl;
    }

    // Getter for username
    string getUsername() const
    {
        return this->username;
    }

    // Setter for username
    void setUsername(const string &username)
    {
        if (!username.empty())
        {
            this->username = username;
        }
        else
        {
            cout << "Username cannot be empty." << endl;
        }
    }

    // Getter for password
    string getPassword() const
    {
        return this->password;
    }

    // Setter for password
    void setPassword(const string &password)
    {
        if (!password.empty()){
            this->password = password;
        }else{
            cout << "Password cannot be empty." << endl;
        }
    }

    // Add product to cart (single product)
    void addToCart(Product *product)
    {
        this->cart.push_back(product);
    }

    // Remove product from cart
    void removeFromCart(const string &productName)
    {
        for (int i = 0; i < this->cart.size(); ++i)
        {
            if (this->cart[i]->getName() == productName)
            {
                delete this->cart[i];
                this->cart.erase(this->cart.begin() + i);
                cout << productName << " removed from cart." << endl;
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }

    // Display cart items
    void displayCart() const
    {
        cout << "-------------------------------" << endl;
        cout << "Cart items for " << this->username << ":" << endl;
        cout << "-------------------------------" << endl;

        for (int i = 0; i < this->cart.size(); ++i)
        {
            this->cart[i]->displayDetails();
        }
    }

    // Checkout
    float checkout()
    {
        float total = 0;
        for (int i = 0; i < this->cart.size(); ++i)
        {
            total += this->cart[i]->getPrice();
        }
        totalRevenue += total;

        cout << "-------------------------------" << endl;
        cout << "Total amount to pay: Rs." << fixed << setprecision(2) << total << endl;
        cout << "-------------------------------" << endl;

        this->cart.clear();
        return total;
    }

    static void displayStatistics()
    {
        cout << "Total customers: " << totalCustomers << endl;
        cout << "Total revenue: Rs." << fixed << setprecision(2) << totalRevenue << endl;
    }
};

int Customer::totalCustomers = 0;
float Customer::totalRevenue = 0;

int main()
{
    vector<Product *> productList;
    productList.push_back(new Product("Laptop", 45999.99));
    productList.push_back(new Product("Headphones", 1149.99));
    productList.push_back(new Product("Mouse", 529.99));
    productList.push_back(new Product("Keyboard", 859.99));
    productList.push_back(new Product("Monitor", 10199.99));
    productList.push_back(new Product("Smartphone", 30699.99));
    productList.push_back(new Product("Tablet", 20299.99));
    productList.push_back(new Product("Smartwatch", 2199.99));
    productList.push_back(new Product("Printer", 4149.99));
    productList.push_back(new Product("External Hard Drive", 2089.99));
    productList.push_back(new Product("USB Flash Drive", 519.99));
    productList.push_back(new Product("Webcam", 1049.99));
    productList.push_back(new Product("Speakers", 1579.99));
    productList.push_back(new Product("Router", 1089.99));
    productList.push_back(new Product("Gaming Console", 2399.99));

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Customer *customer = new Customer(username, password);

    int choice;
    bool done = false;

    cout << "\nAvailable Products:" << endl;
    for (int i = 0; i < productList.size(); ++i)
    {
        cout << i + 1 << ". ";
        productList[i]->displayDetails();
    }
    cout << "-------------------------------" << endl;

    while (!done)
    {
        cout << "Enter the number of the product to add to cart (0 to checkout, -1 to remove an item from the cart, -2 to view cart): ";
        cin >> choice;

        if (choice == 0)
        {
            customer->displayCart();
            float totalAmount = customer->checkout();
            cout << "Thank you for shopping with us!" << endl;
            cout << "Total paid amount: Rs." << fixed << setprecision(2) << totalAmount << endl;
            done = true;
        }
        else if (choice == -1)
        {
            string productName;
            cout << "Enter the name of the product to remove from the cart: ";
            cin.ignore();
            getline(cin, productName);
            customer->removeFromCart(productName);
        }
        else if (choice > 0 && choice <= static_cast<int>(productList.size()))
        {
            customer->addToCart(productList[choice - 1]);
            cout << productList[choice - 1]->getName() << " added to cart." << endl;
        }
        else if (choice == -2)
        {
            customer->displayCart();
        }
        else
        {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    delete customer;

    Customer::displayStatistics();

    return 0;
}
