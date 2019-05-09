// g++ -lpthread -lsodium -Wall random_lottery.c -o random_lottery
#include <iostream>
#include <string>
#include <map>
#include <random>
#include <time.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <fstream>
#include <streambuf>
#include <vector>
#include <algorithm>

#include <sodium.h>  // https://libsodium.gitbook.io/doc/installation

#include "man.hpp"
#include "lottery.hpp"
#include "shop.hpp"

using std::string;
using std::cout;
using std::cin;
using std::thread;
using std::mutex;

mutex theMutex;
Man you;
string itemPath = "./data/";


void Man::goToWork() {
    for (int i = 0; i < 10; ++i)
    {
        cout << "Yohoho and the bootle of rum!\n";
        sleep(60);
    }
    cout << "Job done!\n";
    this->money += 1;
}

void Man::showWallet() {
    cout << "Your wallet contains " << this->money << ".00$\n";
}

void Man::goFishing() {
    cout << "Bye!\n";
    exit(0);
}

bool Man::buy(size_t price) {
    if(price <= this->money) {
        this->money -= price;
        return true;
    }
    else {
        cout << "I don't have this kind of money :(\n";
        cout << "I better go to work...\n";
        return false;
    }
}

bool Man::haveEnoughMoney(int64_t toBet) {
    cout <<"Cheking wallet, is there " << toBet << "$?\n";
    if(toBet > this->money) {
        cout << "I don't have this kind of money :(\n";
        cout << "I better go to work...\n";
        return false;
    }
    return true;
}

void Man::makeBet(Lottery &lottery) {
    std::unique_lock<std::mutex> lock(theMutex);
    int64_t toBet;

    cout << "How much do I want to invest? ";
    cin >> toBet;

    if(toBet < 0)
        toBet = abs(toBet);

    if(this->haveEnoughMoney(toBet)) {
        this->money -= toBet;
        lottery.bet(*this, toBet);
    }
}

void Man::visitShop(Shop &shop) {
    shop.visit(*this);
}

void Man::addCash(size_t money) {
    this->money += money;
}


thread Lottery::start() {
    return thread(&Lottery::run, this);
}

void Lottery::bet(Man &you, size_t toBet) {
    size_t theBet;

    cout << "Well well, " << you.name << " wants to play!\n";
    cout << "And what is your bet? ";
    cin >> theBet;

    this->people.push_back(betTuple(&you, theBet, toBet));
    cout << "Your bet is accepted, wait until the game starts\n";
}

void Lottery::run() {
    while(true) {
        sleep(10);

        {
            std::unique_lock<std::mutex> lock(theMutex);
            cout << "\nLottery betting time!\n";

            cout << "Random lot is... ";
            sleep(1); 
            size_t value = nextLot();
            cout << value << "!\n";

            for(auto somebodyBet : this->people) {
                auto somebody = std::get<0>(somebodyBet);
                auto bet = std::get<1>(somebodyBet);
                auto moneyInvested = std::get<2>(somebodyBet);

                if(bet == value) {
                    cout << somebody->name << " won " << moneyInvested << "$!\n";
                    somebody->addCash(2*moneyInvested);
                }
            }

            sleep(2);
            std::cout << "Lottery end!\n";
            this->people.clear();
        }
    }
}

size_t Lottery::nextLot() {
    return (size_t)randombytes_uniform(4);
}


thread Shop::start() {
    return std::thread(&Shop::open, this);
}

void Shop::visit(Man &you) {
    if(!this->isOpen) {
        cout << "Shop is closed, come back later.\n";
        return;
    }

    cout << "Shop assortment:\n";
    for(auto item : this->items) {
        auto itemName = std::get<0>(item);
        auto itemPrice = std::get<1>(item);
        cout << "* " << itemName << " (" << itemPrice << "$)\n";
    }

    string toBuy, answer;
    cout << "What do you want to buy? ";
    cin >> toBuy;

    bool itemFound = false;
    for(auto item : this->items) {
        auto itemName = std::get<0>(item);
        auto itemPrice = std::get<1>(item);

        if(itemName == toBuy) {
            itemFound = true;
            cout << "It will cost you " << itemPrice << ".00$. Are you shure? ";
            cin >> answer;
            std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
            if(answer == "yes" || answer == "y") {
                if(you.buy(itemPrice)) {
                    std::ifstream t(itemPath + itemName);
                    std::string itemValue((std::istreambuf_iterator<char>(t)),
                                           std::istreambuf_iterator<char>());
                    cout << "Here it is:\n" << itemValue << "\n";
                }
            }
        }
    }

    if(!itemFound) {
        cout << "We don't have such thing.\n";
    }
}

void Shop::open() {
    this->items.push_back(itemTuple("beer", 1));
    this->items.push_back(itemTuple("whisky", 10));
    this->items.push_back(itemTuple("malibu", 3));
    this->items.push_back(itemTuple("flag", 4242424242));
    this->items.push_back(itemTuple("immortality", 7331));

    while(true) {
        isOpen = true;
        sleep(3);
        isOpen = false;
    }
}


void printMenu() {
    std::unique_lock<mutex> lock(theMutex);
    cout << "Menu\n";
    cout << "1) Show wallet\n";
    cout << "2) Go to work\n";
    cout << "3) Bet\n";
    cout << "4) Visit shop\n";
    cout << "5) Go fishing...\n";
}


int main() {
    if (sodium_init() < 0) {
        cout << "error - Sodium not initialized\n";
        exit(1);
    }

    Lottery lottery;
    Shop shop;
    thread shopThread = shop.start();
    thread lotteryThread = lottery.start();

    clock_t timeStart = clock();

    {
        std::unique_lock<mutex> lock(theMutex);
        cout << "What is your name? ";
        cin >> you.name;
        cout << "Hello " << you.name  << "! ";
        cout << "Welcome in the lottery!\n";
        cout << "You can bet your money and if you win, you will be awarded with the ame amount!\n";
        cout << "And with the money, you can buy useful stuff!\n\n";
    }

    unsigned short choice;
    do {
        printMenu();
        cin >> choice;
        switch(choice) {
            case 1: you.showWallet();
                    break;
            case 2: you.goToWork();
                    break;
            case 3: you.makeBet(lottery);
                    break;
            case 4: you.visitShop(shop);
                    break;
            case 5: you.goFishing();
                    break;
            default: cout << "Invalid choice\n";
        }
    } while((double)(clock() - timeStart)/CLOCKS_PER_SEC < 40);

    lotteryThread.join();
    shopThread.join();

    cout << "Loterry closed!\n";
    return 0;
}
