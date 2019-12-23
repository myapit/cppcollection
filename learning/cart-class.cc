#include <iostream>

class Cart 
{
    private:
        int total;

    public:
        Cart(int item)
        {
            this->total = item;
        }

        Cart& addItem(int itemPrice)
        {
            total += itemPrice;
            return *this;
        }

        void checkOut()
        {
            std::cout << "Total: RM " << total << "\n";
        }
};

int main()
{
    Cart myCart(0);
    myCart.addItem(100).addItem(200).addItem(300);
    myCart.checkOut();
    
    Cart(0);
    myCart.addItem(10)
        .addItem(20)
        .addItem(30);
    
    myCart.checkOut();
}

