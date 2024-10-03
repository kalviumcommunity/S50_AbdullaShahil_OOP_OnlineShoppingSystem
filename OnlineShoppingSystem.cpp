#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Base Product class
class Product
{
protected:
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
    virtual float getPrice() const // Virtual to allow overriding in derived classes
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

    virtual void displayDetails() const
    {
        cout << "-> " << this->name << " - Rs." << fixed << setprecision(2) << this->price << endl;
    }
};

// Derived class for discounted products - Single Inheritance
class DiscountedProduct : public Product
{
private:
    float discountPercentage;

public:
    DiscountedProduct(const string &name, float price, float discountPercentage)
        : Product(name, price), discountPercentage(discountPercentage) {}

    // Overriding getPrice to apply the discount
    float getPrice() const override
    {
        return price * (1 - discountPercentage / 100);
    }

    void displayDetails() const override
    {
        cout << "-> " << name << " - Rs." << fixed << setprecision(2) << getPrice() << " (Discount: " << discountPercentage << "%)" << endl;
    }
};

// Base class for customers
class Customer
{
protected:
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

    virtual ~Customer() // Virtual destructor for proper cleanup in derived classes
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

    // Add product to cart (single product)
    void addToCart(Product *product)
    {
        this->cart.push_back(product);
    }

    // Overloaded function to add multiple products to cart
    void addToCart(const vector<Product *> &products)
    {
        for (Product *product : products)
        {
            this->cart.push_back(product);
        }
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
    virtual void displayCart() const
    {
        cout << "-------------------------------" << endl;
        cout << "Cart items for " << this->username << ":" << endl;
        cout << "-------------------------------" << endl;

        for (Product *product : this->cart)
        {
            product->displayDetails();
        }
    }

    // Virtual checkout method
    virtual float checkout() // Marked as virtual to allow overriding
    {
        float total = 0;
        for (Product *product : this->cart)
        {
            total += product->getPrice();
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

// Derived class PremiumCustomer
class PremiumCustomer : public Customer
{
public:
    PremiumCustomer(const string &username, const string &password)
        : Customer(username, password) {}

    // Premium customers get 5% discount on their total purchase
    float checkout() override
    {
        float total = Customer::checkout();
        float discount = total * 0.05;
        cout << "Premium customer discount (5%): Rs." << fixed << setprecision(2) << discount << endl;
        return total - discount;
    }
};

// Derived class LoyalCustomer from PremiumCustomer - Multilevel Inheritance
class LoyalCustomer : public PremiumCustomer
{
public:
    LoyalCustomer(const string &username, const string &password)
        : PremiumCustomer(username, password) {}

    // Loyal customers get an additional 10% discount on their total purchase
    float checkout() override
    {
        float total = PremiumCustomer::checkout();
        float additionalDiscount = total * 0.10;
        cout << "Loyal customer additional discount (10%): Rs." << fixed << setprecision(2) << additionalDiscount << endl;
        cout << "-------------------------------" << endl;

        return total - additionalDiscount;
    }
};

int main()
{
    vector<Product *> productList;
    productList.push_back(new Product("Laptop", 45999.99));
    productList.push_back(new DiscountedProduct("Headphones", 1149.99, 10));
    productList.push_back(new DiscountedProduct("Smartphone", 30699.99, 15));
    productList.push_back(new Product("Tablet", 20299.99));
    productList.push_back(new Product("Smartwatch", 2199.99));
    productList.push_back(new Product("Mouse", 529.99));
    productList.push_back(new Product("Keyboard", 859.99));
    productList.push_back(new Product("Monitor", 10199.99));

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Using LoyalCustomer to demonstrate multilevel inheritance
    LoyalCustomer *customer = new LoyalCustomer(username, password);

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
            cout << "-> Total paid amount: Rs." << fixed << setprecision(2) << totalAmount << endl;
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
