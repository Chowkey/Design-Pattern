#include <iostream>
using namespace std;
class Payment {
public:
    virtual void processPayment() const = 0;
    virtual ~Payment() {}
};

// Abstract Product for Shipping
class Shipping {
public:
    virtual void ship() const = 0;
    virtual ~Shipping() {}
};

class CreditCardPayment : public Payment {
public:
    void processPayment() const override {
        cout << "Processing payment via Credit Card.";
    }
};
class PayPalPayment : public Payment {
public:
    void processPayment() const override {
        std::cout << "Processing payment via PayPal.";
    }
};
class StandardShipping : public Shipping {
public:
    void ship() const override {
        cout << "Shipping with Standard Shipping.";
    }
};
class ExpressShipping : public Shipping {
public:
    void ship() const override {
        cout << "Shipping with Express Shipping.";
    }
};

// Abstract Factory
class PaymentShippingFactory {
public:
    virtual Payment* createPayment() const = 0;
    virtual Shipping* createShipping() const = 0;
    virtual ~PaymentShippingFactory() {}
};

// Concrete Factory for Credit Card Payment and Standard Shipping
class CreditCardStandardFactory : public PaymentShippingFactory {
public:
    Payment* createPayment() const override {
        return new CreditCardPayment();
    }
    
    Shipping* createShipping() const override {
        return new StandardShipping();
    }
};

// Concrete Factory for Credit Card Payment and Express Shipping
class CreditCardExpressFactory : public PaymentShippingFactory {
public:
    Payment* createPayment() const override {
        return new CreditCardPayment();
    }
    
    Shipping* createShipping() const override {
        return new ExpressShipping();
    }
};

// Concrete Factory for PayPal Payment and Standard Shipping
class PayPalStandardFactory : public PaymentShippingFactory {
public:
    Payment* createPayment() const override {
        return new PayPalPayment();
    }
    
    Shipping* createShipping() const override {
        return new StandardShipping();
    }
};

// Concrete Factory for PayPal Payment and Express Shipping
class PayPalExpressFactory : public PaymentShippingFactory {
public:
    Payment* createPayment() const override {
        return new PayPalPayment();
    }
    
    Shipping* createShipping() const override {
        return new ExpressShipping();
    }
};

void processOrder(const PaymentShippingFactory& factory) {
    Payment* payment = factory.createPayment();
    Shipping* shipping = factory.createShipping();
    
    payment->processPayment();
    shipping->ship();
    
    // Clean up
    delete payment;
    delete shipping;
}

int main() {
    cout << "Order 1:" <<endl;
    CreditCardStandardFactory creditCardStandardFactory;
    processOrder(creditCardStandardFactory);

    cout << "Order 2:" <<endl;
    PayPalExpressFactory payPalExpressFactory;
    processOrder(payPalExpressFactory);

    cout << "Order 3:" <<endl;
    CreditCardExpressFactory creditCardExpressFactory;
    processOrder(creditCardExpressFactory);
    
    cout << "Order 4:" << endl;
    PayPalStandardFactory payPalStandardFactory;
    processOrder(payPalStandardFactory);
}


