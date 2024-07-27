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
    Product(const string& name, float price) : name(name), price(price) {}

    string getName() const {
        return name;
    }

    float getPrice() const {
        return price;
    }

    void displayDetails() const {
        cout << "-> " << name << " - Rs." << fixed << setprecision(2) << price << endl;
    }
};

class Customer {
private:
    string username;
    string password;
    vector<Product> cart;

public:
    Customer(const string& username, const string& password) : username(username), password(password) {}

    void addToCart(const Product& product) {
        cart.push_back(product);
    }

    void removeFromCart(const string& productName) {

        for (int i = 0; i < cart.size(); ++i) {
            if (cart[i].getName() == productName) {
                cart.erase(cart.begin() + i);
                cout << productName << " removed from cart." << endl;
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }

    void displayCart() const {
        cout << "-------------------------------" << endl;
        cout << "Cart items for " << username << ":" << endl;
        cout << "-------------------------------" << endl;

        for (int i = 0; i < cart.size(); ++i) {
            cart[i].displayDetails();
        }
    }

    float checkout() {
        float total = 0;
        for (int i = 0; i < cart.size(); ++i) {
            total += cart[i].getPrice();
        }
        cout << "-------------------------------" << endl;
        cout << "Total amount to pay: Rs." << fixed << setprecision(2) << total << endl;
        cout << "-------------------------------" << endl;

        cart.clear();
        return total;
    }
};

int main() {
    vector<Product> productList;
    productList.push_back(Product("Laptop", 45999.99));
    productList.push_back(Product("Headphones", 1149.99));
    productList.push_back(Product("Mouse", 529.99));
    productList.push_back(Product("Keyboard", 859.99));
    productList.push_back(Product("Monitor", 10199.99));
    productList.push_back(Product("Smartphone", 30699.99));
    productList.push_back(Product("Tablet", 20299.99));
    productList.push_back(Product("Smartwatch", 2199.99));
    productList.push_back(Product("Printer", 4149.99));
    productList.push_back(Product("External Hard Drive", 2089.99));
    productList.push_back(Product("USB Flash Drive", 519.99));
    productList.push_back(Product("Webcam", 1049.99));
    productList.push_back(Product("Speakers", 1579.99));
    productList.push_back(Product("Router", 1089.99));
    productList.push_back(Product("Gaming Console", 2399.99));

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Customer customer(username, password);

    int choice;
    bool done = false;

    cout << "\nAvailable Products:" << endl;
    for (int i = 0; i < productList.size(); ++i) {
        cout << i + 1 << ". ";
        productList[i].displayDetails();
    }
    cout << "-------------------------------" << endl;

    while (!done) {
        cout << "Enter the number of the product to add to cart (0 to checkout, -1 to remove an item from the cart, -2 view cart): ";
        cin >> choice;

        if (choice == 0) {
            customer.displayCart();
            float totalAmount = customer.checkout();
            cout << "Thank you for shopping with us!" << endl;
            cout << "Total paid amount: Rs." << fixed << setprecision(2) << totalAmount << endl;
            done = true;

        } else if (choice == -1) {
            string productName;
            cout << "Enter the name of the product to remove from the cart: ";
            cin.ignore();
            getline(cin, productName);
            customer.removeFromCart(productName);

        } else if (choice > 0 && choice <= static_cast<int>(productList.size())) {
            customer.addToCart(productList[choice - 1]);
            cout << productList[choice - 1].getName() << " added to cart." << endl;

        } else if (choice == -2) {
            customer.displayCart();
            
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
