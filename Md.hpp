#include "Player.hpp"

class Md : public Player
{
private:
    enum
    {
        LEFT_POS_MD = 5,
        RIGHT_POS_MD = 7,
    };
public:
    Md(int &role, string &name);

    virtual void set_position(int pos);
};
