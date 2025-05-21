#include <iostream>

using namespace std;

class Vehicle {
protected:
    int id;
    double rate;
    string make;
    string model;
    int year;

public:
    Vehicle(int vehicleId, double rentalRate, string vehicleMake, string vehicleModel, int vehicleYear) {
        id = vehicleId;
        rate = rentalRate;
        make = vehicleMake;
        model = vehicleModel;
        year = vehicleYear;
    }

   ~Vehicle() {
        cout << "Vehicle with ID " << id << " destroyed." << endl;
    }

    double getRate()  {
        return rate;
    }

    int getId()  {
        return id;
    }

    virtual void display()  {
        cout << "Vehicle ID: " << id << ", " << year << " " << make << " " << model
             << ", Rate: $" << rate << "/day" << endl;
    }
};


class LuxuryVehicle : public Vehicle {
private:
    double luxuryTax;

public:
    LuxuryVehicle(int vehicleId, double rentalRate, string vehicleMake, string vehicleModel, int vehicleYear, double tax)
        : Vehicle(vehicleId, rentalRate, vehicleMake, vehicleModel, vehicleYear), luxuryTax(tax) {}

    ~LuxuryVehicle()  {
        cout << "Luxury vehicle destroyed." << endl;
    }

    double getLuxuryTax()  {
        return luxuryTax;
    }

    void display() override {
    cout << "LuxuryVehicle ID: " << getId() << ", " << year << " " << make << " " << model
         << ", Rate: $" << getRate() << "/day" << endl;
    cout << "Includes additional luxury tax: $" << luxuryTax << endl;
}
};

class Customer {
private:
    int id;
    string name;
    string phone;

public:
    Customer(int customerId , string customerName , string customerPhone ) {
        id = customerId;
        name = customerName;
        phone = customerPhone;
    }

    ~Customer() {
        cout << "Customer with ID " << id << " destroyed." << endl;
    }

    int getId()  {
        return id;
    }

    void display()  {
        cout << "Customer ID: " << id << ", Name: " << name << ", Phone: " << phone << endl;
    }
};

class RentalTransaction {
private:
    int id;
    int vehicleId;
    int customerId;
    double totalCost;
    int days;

public:
    RentalTransaction(int transactionId , int vId , int cId , int numDays ) {
        id = transactionId;
        vehicleId = vId;
        customerId = cId;
        days = numDays;
        totalCost = 0.0;
    }

    ~RentalTransaction() {
        cout << "Transaction with ID " << id << " destroyed." << endl;
    }


    void calculateCost(double rate) {
        totalCost = rate * days;
    }


    void calculateCost(double rate, double discount) {
        totalCost = (rate * days) - discount;
        if (totalCost < 0) totalCost = 0;
    }

    int getDays()  {
        return days;
    }

    void setTotalCost(double cost) {
        totalCost = cost;
    }

    double getTotalCost()  {
        return totalCost;
    }

    void display()  {
        cout << "Transaction ID: " << id << ", Vehicle ID: " << vehicleId
             << ", Customer ID: " << customerId << ", Days: " << days
             << ", Total Cost: $" << totalCost << endl;
    }
};


class PremiumRental : public LuxuryVehicle, public RentalTransaction {
public:
    PremiumRental(int transactionId, int vehicleId, int customerId, int numDays,double rentalRate, string vehicleMake, string vehicleModel, int vehicleYear, double tax)
        : LuxuryVehicle(vehicleId, rentalRate, vehicleMake, vehicleModel, vehicleYear, tax),
          RentalTransaction(transactionId, vehicleId, customerId, numDays) {}

    void calculateTotalCost() {
        double baseCost = getRate() * getDays();
        double total = baseCost + getLuxuryTax();
        setTotalCost(total);
    }

    void display()  {
        cout << "Premium Rental Transaction Details:" << endl;
        LuxuryVehicle::display();
        RentalTransaction::display();
    }
};

int main() {
    Vehicle v(1, 45.5, "Toyota", "Corolla", 2020);
    v.display();

    LuxuryVehicle lv(2, 150.0, "BMW", "7 Series", 2023, 25.0);
    lv.display();

    Customer c(101, "GG group", "077777777");  // <--- define BEFORE usage
    c.display();

    RentalTransaction t(5001, v.getId(), c.getId(), 3);
    t.calculateCost(v.getRate());
    t.display();

    RentalTransaction t2(5002, v.getId(), c.getId(), 3);
    t2.calculateCost(v.getRate(), 20.0);    // discounted cost of $20
    t2.display();

    PremiumRental pr(6001, 2, 101, 4, 150.0, "BMW", "7 Series", 2023, 25.0);
    pr.calculateTotalCost();
    pr.display();

    return 0;
}

