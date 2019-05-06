#ifndef LOTTERY_H
#define LOTTERY_H

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


typedef std::tuple<Man*,size_t,size_t> betTuple;

class Man;

class Lottery {
public:
    std::thread start();
    void bet(Man&, size_t);

private:
    std::vector<betTuple> people;

    void run();
    size_t nextLot();
};

#endif
