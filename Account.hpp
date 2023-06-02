#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account
{
private:
    string username;
    string password;
public:
    string get_name() {return this->username;}

    Account(string &username_, string &pass);
    ~Account();
};
