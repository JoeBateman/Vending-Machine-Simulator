/*
|　　|┌────────────┐|
|　　|│![] [] [] [] │
|　　|::l三三三三三!.|
|　　|│![] [] [] [] │
|　　|::l三三三三三!.|
|　　|┌────────────┐|　　　      lヽ,,lヽ
|　　|│＿＿＿＿＿∧∧　　　　　　 (　　　  ）　やめて！
{二二}￣￣￣￣⊂<  ヽ⌒ヽ　　　　 と　 　  i
　　　　　　　   ∪(＿つつ　　 　　 しー J
*/



#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cmath>


class machine_item{
    public: 
        std::string item_name;
        int price_in_pennies;
        std::string name;
        void set_item_price(int price){
            price_in_pennies = price;     
        }
        void set_item_name(std::string name){
            item_name = name;
        }
};

class user_items{
    public:
        std::string items[20];
        bool add_item(std::string item){
            if(number_of_items < 20){
                items[number_of_items] = item;
                ++number_of_items;
                return true;
            }
            else{return false;}
            };
        std::string get_items(){
            std::string filled_spaces{""};
            for(int i =0; i < 20; ++i){
                if(items[i] != "Empty"){
                filled_spaces.append(items[i]);
                }
                else{break;}
            }
            return filled_spaces;
        }
        
        user_items(){
            for(int i =0; i < 20; ++i){
                items[i]="Empty";
        }
        } 
    private: 
        int number_of_items{0};  
};

class wallet{
    private:
        int money_in_pennies{200};
    public:
        int get_balance(){
            return money_in_pennies;
        }
        bool change_balance(int pennies){
            if(money_in_pennies + pennies <0){
                return false;
            }
            else {money_in_pennies += pennies; return true;}
        }
        void set_balance(int balance){
            money_in_pennies = balance;
        }
        bool empty_wallet(){

            if(money_in_pennies == 0){
                return true;
            }
            else {return false;}
        }  
        
};

int main()
{
    bool running{true};

    const std::string names_and_prices[5][2]{
        {"Pepsi","80"},
        {"Coke","100"},
        {"Salt and vinegar crisps","100"},
        {"Mars bar","50"},
        {"Skittles","200"},
    };
    const int number_of_items{sizeof names_and_prices / sizeof names_and_prices[0]};

    machine_item items[number_of_items];
    for(int i{0}; i < number_of_items; ++i){
        items[i].set_item_name(names_and_prices[i][0]);
        items[i].set_item_price(std::stoi(names_and_prices[i][1]));
    };

    user_items myBag;

    std::string outcome_table[number_of_items + 1];
    for(int i =0; i < number_of_items; ++i){
            outcome_table[i] = names_and_prices[i][0];
    };
    outcome_table[number_of_items] = "Death";

    int minimum_product_price;
    
    for(int i{0}; i < number_of_items-1; ++i){
        if(items[i+1].price_in_pennies < items[i].price_in_pennies){
            minimum_product_price = items[i+1].price_in_pennies;
        };
    }

    wallet myWallet;
    myWallet.set_balance(200);
    std::string user_input;
    
    std::cout << '\n' << " |　　|┌────────────┐| \n |　　|│![] [] [] [] │ \n |　　|::l三三三三三!.| \n |　　|│![] [] [] [] │ \n |　　|::l三三三三三!.| \n |　　|┌────────────┐|　　　       lヽ,,lヽ\ \n |　　|│＿＿＿＿＿∧∧　　　　　　  (　　　  ）　やめて！ \n {二二}￣￣￣￣⊂<ヽ  ⌒ヽ　　　　  と　 　  i \n 　　　　　　　   ∪(＿つつ　　 　　 しー J \n";
    std::cout << "You approach a vending machine in the dead of night. You finally are off shift and  in desperate need of a simple meal. \n You look in your wallet: $"<< myWallet.get_balance()<<" . Let's see what you can get. \n";
    
    for(int i{0}; i <number_of_items; ++i){
        float dollar_price = static_cast<float>(std::stoi(names_and_prices[i][1]))/100;
        std::cout << names_and_prices[i][0] << ", $" << std::fixed << std::setprecision(2) << dollar_price << '\n';
    };
    std::cout << "Would you like to buy an item, shake the machine for an item, or see what items you have? \n";
    bool can_buy_items{true};
    do{
    std::getline (std::cin, user_input);
    bool attempted_purchase{false};
    
    
    if(user_input != "Shake" && user_input != "Items" && myWallet.get_balance() >= minimum_product_price){
        for(int i{0}; i <number_of_items; ++i){
            if(user_input == names_and_prices[i][0]){
                int price{std::stoi(names_and_prices[i][1])};
                attempted_purchase = true;
                int remaining = myWallet.get_balance() - price;
                if((remaining >= 0) && !myWallet.empty_wallet() ){
                std::cout << "\n You bought " << names_and_prices[i][0];
                myWallet.change_balance(-price);
                bool item_in_bag{myBag.add_item(names_and_prices[i][0])};
                std::cout << "\n You have $" << static_cast<float>(remaining)/100 << " remaining";
                if(!item_in_bag){
                    std::cout << "Your bag is full, so you can't take any more from the vending machine.";
                    can_buy_items = false;
                }
                break;
                }
                else{std::cout << "\n You can't afford that."; break;}
            }
        };
        if(!attempted_purchase){std::cout << '\n' << user_input << " isn't for sale here.";};
    }
    else if(user_input == "Shake"){
        int number{rand() % number_of_items+1};
        std::string outcome = outcome_table[number];
        
        
        if(outcome != "Death"){
            std::cout << "You shook free " << outcome << ". \n";
            bool item_in_bag{myBag.add_item(outcome)};
            if(!item_in_bag){
                    std::cout << "Your bag is full, so you can't take any more from the vending machine.";
                    can_buy_items = false;
            }
        }
        else{
            std::cout << "The machine fell on top of you.";
            std::cout << "\n ┌─────────────────────┐\n │	  	       │　\n │三三三三三三三三三三 │　		lヽ,,lヽ\n │	  	       │    	       (　　　   ）　やめて！\n │三三三三三三三三三三 │　		と　 　  i\n │　　　　　　  ＿つつ │　	  	  しー J\n ￣￣￣￣￣￣￣￣￣￣￣";
            can_buy_items = false;
        }
    
    }
    else if(user_input == "Items"){
        std::cout << "You open your backpack. There is " << myBag.get_items();
    }

    
    if((myWallet.get_balance() >= minimum_product_price) && can_buy_items == true){std::cout << "\n Would you like to buy anything else, or shake the machine? \n";}
    }
    while(can_buy_items); 
    
    
    std::cout << "\nShutting down...";
    return 0;
}