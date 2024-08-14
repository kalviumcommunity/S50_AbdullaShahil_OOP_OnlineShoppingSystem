#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Product {
protected:
    string name;
    float price;

public:
    Product(const string& name, float price) {
        this->name = name;
        this->price = price;
    }

    string getName() const {
        return this->name;
    }

    float getPrice() const {
        return this->price;
    }

    void displayDetails() const {
        cout << "-> " << this->name << " - Rs." << fixed << setprecision(2) << this->price << endl;
    }
};

class Customer {
private:
    string username;
    string password;
    vector<Product*> cart;  // Now a vector of pointers to Product

public:
    Customer(const string& username, const string& password) {
        this->username = username;
        this->password = password;
    }

    ~Customer() {
        // We do not delete the products here since they are managed externally
    }

    void addToCart(Product* product) {
        this->cart.push_back(product);
    }

    void removeFromCart(const string& productName) {
        for (int i = 0; i < this->cart.size(); ++i) {
            if (this->cart[i]->getName() == productName) {
                this->cart.erase(this->cart.begin() + i);
                cout << productName << " removed from cart." << endl;
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }

    void displayCart() const {
        cout << "-------------------------------" << endl;
        cout << "Cart items for " << this->username << ":" << endl;
        cout << "-------------------------------" << endl;

        for (int i = 0; i < this->cart.size(); ++i) {
            this->cart[i]->displayDetails();
        }
    }

    float checkout() {
        float total = 0;
        for (int i = 0; i < this->cart.size(); ++i) {
            total += this->cart[i]->getPrice();
        }
        cout << "-------------------------------" << endl;
        cout << "Total amount to pay: Rs." << fixed << setprecision(2) << total << endl;
        cout << "-------------------------------" << endl;

        this->cart.clear(); 
        return total;
    }
};

int main() {
    vector<Product*> productList; 
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

    Customer* customer = new Customer(username, password); 

    int choice;
    bool done = false;

    cout << "\nAvailable Products:" << endl;
    for (int i = 0; i < productList.size(); ++i) {
        cout << i + 1 << ". ";
        productList[i]->displayDetails();
    }
    cout << "-------------------------------" << endl;

    while (!done) {
        cout << "Enter the number of the product to add to cart (0 to checkout, -1 to remove an item from the cart, -2 view cart): ";
        cin >> choice;

        if (choice == 0) {
            customer->displayCart();
            float totalAmount = customer->checkout();
            cout << "Thank you for shopping with us!" << endl;
            cout << "Total paid amount: Rs." << fixed << setprecision(2) << totalAmount << endl;
            done = true;

        } else if (choice == -1) {
            string productName;
            cout << "Enter the name of the product to remove from the cart: ";
            cin.ignore();
            getline(cin, productName);
            customer->removeFromCart(productName);

        } else if (choice > 0 && choice <= static_cast<int>(productList.size())) {
            customer->addToCart(productList[choice - 1]);
            cout << productList[choice - 1]->getName() << " added to cart." << endl;

        } else if (choice == -2) {
            customer->displayCart();

        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }


    delete customer;

    for (auto product : productList) {
        delete product;  
    }

    return 0;
}
