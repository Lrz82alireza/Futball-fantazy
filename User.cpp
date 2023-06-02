#include "User.hpp"

User::User(string &username_, string &pass)
    : Account(username_, pass)
{
    this->team = make_shared<Team>(username_);
}