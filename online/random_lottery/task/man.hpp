#ifndef MAN_H
#define MAN_H


class Lottery;
class Shop;

class Man {
public:
    std::string name;
    void goToWork();
    void showWallet();
    void goFishing();
    void makeBet(Lottery&);
    void visitShop(Shop&);
    void addCash(size_t);
    bool haveEnoughMoney(int64_t);
    bool buy(int64_t);

private:
    int64_t money = 2;
};

#endif
