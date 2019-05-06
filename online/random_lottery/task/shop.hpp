#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <streambuf>
#include <vector>

typedef std::tuple<std::string, size_t> itemTuple;

class Man;

class Shop {
public:
    std::thread start();
    void visit(Man&);

private:
    std::vector<itemTuple> items;
    bool isOpen = false;
    void open();
};

#endif
