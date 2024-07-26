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
    Product(const string name, float price) : name(name), price(price) {}

    string getName() const {
        return name;
    }

    float getPrice() const {
        return price;
    }

    void displayDetails() const {
        cout << "-> " << name << " - Rs." << fixed << setprecision(2) << price << endl;
    }

    bool operator==(const Product& other) const {
        return name == other.name && price == other.price;
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
        for (vector<Product>::iterator it = cart.begin(); it != cart.end(); ++it) {
            if (it->getName() == productName) {
                cart.erase(it);
                cout << productName << " removed from cart." << endl;
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }

    void displayCart() const {
        cout << "-------------------------------" <<endl;
        cout << "Cart items for " << username << ":" << endl;
        cout << "-------------------------------" <<endl;
        for (vector<Product>::const_iterator it = cart.begin(); it != cart.end(); ++it) {
            it->displayDetails();
        }
    }

    float checkout() {
        float total = 0;
        for (vector<Product>::const_iterator it = cart.begin(); it != cart.end(); ++it) {
            total += it->getPrice();
        }
        cout << "-------------------------------" <<endl;
        cout << "Total amount to pay: Rs." << fixed << setprecision(2) << total << endl;
        cout << "-------------------------------" <<endl;

        cart.clear();
        return total;
    }
};

int main() {
    vector<Product> productList;
    productList.push_back(Product("Laptop", 999.99));
    productList.push_back(Product("Headphones", 149.99));
    productList.push_back(Product("Mouse", 29.99));
    productList.push_back(Product("Keyboard", 59.99));
    productList.push_back(Product("Monitor", 199.99));
    productList.push_back(Product("Smartphone", 699.99));
    productList.push_back(Product("Tablet", 299.99));
    productList.push_back(Product("Smartwatch", 199.99));
    productList.push_back(Product("Printer", 149.99));
    productList.push_back(Product("External Hard Drive", 89.99));
    productList.push_back(Product("USB Flash Drive", 19.99));
    productList.push_back(Product("Webcam", 49.99));
    productList.push_back(Product("Speakers", 79.99));
    productList.push_back(Product("Router", 89.99));
    productList.push_back(Product("Gaming Console", 399.99));

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Customer customer(username, password);

    int choice;
    bool done = false;

    while (!done) {
        cout << "\nAvailable Products:" << endl;
        for (size_t i = 0; i < productList.size(); ++i) {
            cout << i + 1 << ". ";
            productList[i].displayDetails();
        }
        cout << "Enter the number of the product to add to cart (0 to checkout, -1 to remove an item from the cart): ";
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
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
