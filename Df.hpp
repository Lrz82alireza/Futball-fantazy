#include "Player.hpp"

class Df : public Player
{
private:
    enum
    {
        LEFT_POS_DF = 1,
        RIGHT_POS_DF = 4,
    };
public:
    Df(int &role, string &name);

    virtual void set_position(int pos);
};

