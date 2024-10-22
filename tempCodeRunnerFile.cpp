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
