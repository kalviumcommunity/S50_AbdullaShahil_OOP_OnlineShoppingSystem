#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Abstract Product class
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

    // Pure virtual function
    virtual float getPrice() const = 0;

    // Virtual function
    virtual void displayDetails() const = 0;

    // Virtual destructor
    virtual ~Product() {}
};

// Derived class for standard products
class StandardProduct : public Product
{
public:
    StandardProduct(const string &name, float price)
        : Product(name, price) {}

    // Overriding getPrice to return base price
    float getPrice() const override
    {
        return this->price;
    }

    void displayDetails() const override
    {
        cout << "-> " << this->name << " - Rs." << fixed << setprecision(2) << this->price << endl;
    }
};

// Derived class for discounted products
class DiscountedProduct : public Product
{
private:
    float discountPercentage;

public:
    DiscountedProduct(const string &name, float price, float discountPercentage)
        : Product(name, price), discountPercentage(discountPercentage) {}

    // Overriding getPrice to apply discount
    float getPrice() const override
    {
        return price * (1 - discountPercentage / 100);
    }

    void displayDetails() const override
    {
        cout << "-> " << name << " - Rs." << fixed << setprecision(2) << getPrice() << " (Discount: " << discountPercentage << "%)" << endl;
    }
};

// New Cart class - responsible only for cart management
class Cart
{
private:
    vector<Product *> products;

public:
    // Add product to the cart
    void addProduct(Product *product)
    {
        products.push_back(product);
    }

    // Remove product from the cart
    void removeProduct(const string &productName)
    {
        for (int i = 0; i < products.size(); ++i)
        {
            if (products[i]->getName() == productName)
            {
                delete products[i];
                products.erase(products.begin() + i);
                cout << productName << " removed from cart." << endl;
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }

    // Display all products in the cart
    void displayCart() const
    {
        cout << "-------------------------------" << endl;
        cout << "Cart items:" << endl;
        cout << "-------------------------------" << endl;

        for (Product *product : products)
        {
            product->displayDetails();
        }
    }

    // Calculate total price of all products in the cart
    float calculateTotal()
    {
        float total = 0;
        for (Product *product : products)
        {
            total += product->getPrice();
        }
        return total;
    }

    // Destructor for clearing the cart memory
    ~Cart()
    {
        for (Product *product : products)
        {
            delete product;
        }
        products.clear();
        cout << "Cart memory deallocated." << endl;
    }
};

// Refactored Customer class
class Customer
{
protected:
    string username;
    string password;
    Cart cart; // Customer "has a" Cart (composition)

    static int totalCustomers;
    static float totalRevenue;

public:
    // Constructor for Customer
    Customer(const string &username, const string &password)
    {
        this->username = username;
        this->password = password;
        totalCustomers++;
    }

    // Add product to the customer's cart
    void addToCart(Product *product)
    {
        cart.addProduct(product);
    }

    // Remove product from the customer's cart
    void removeFromCart(const string &productName)
    {
        cart.removeProduct(productName);
    }

    // Display the customer's cart
    void displayCart() const
    {
        cart.displayCart();
    }

    // Checkout - Calculate total and clear cart
    virtual float checkout()
    {
        float total = cart.calculateTotal();
        totalRevenue += total;

        cout << "-------------------------------" << endl;
        cout << "Total amount to pay: Rs." << fixed << setprecision(2) << total << endl;
        cout << "-------------------------------" << endl;

        return total;
    }

    // Static function to display statistics
    static void displayStatistics()
    {
        cout << "Total customers: " << totalCustomers << endl;
        cout << "Total revenue: Rs." << fixed << setprecision(2) << totalRevenue << endl;
    }

    virtual ~Customer() {}
};

int Customer::totalCustomers = 0;
float Customer::totalRevenue = 0;

// Derived class PremiumCustomer with discounts
class PremiumCustomer : public Customer
{
public:
    PremiumCustomer(const string &username, const string &password)
        : Customer(username, password) {}

    // Premium customers get a 5% discount on their total purchase
    float checkout() override
    {
        float total = Customer::checkout();
        float discount = total * 0.05;
        cout << "Premium customer discount (5%): Rs." << fixed << setprecision(2) << discount << endl;
        return total - discount;
    }
};

// Derived class LoyalCustomer - Multilevel Inheritance
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

// Main function to demonstrate functionality
int main()
{
    vector<Product *> productList;
    productList.push_back(new StandardProduct("Laptop", 45999.99));
    productList.push_back(new DiscountedProduct("Headphones", 1149.99, 10));
    productList.push_back(new DiscountedProduct("Smartphone", 30699.99, 15));
    productList.push_back(new StandardProduct("Tablet", 20299.99));
    productList.push_back(new StandardProduct("Smartwatch", 2199.99));
    productList.push_back(new StandardProduct("Mouse", 529.99));
    productList.push_back(new StandardProduct("Keyboard", 859.99));
    productList.push_back(new StandardProduct("Monitor", 10199.99));

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
