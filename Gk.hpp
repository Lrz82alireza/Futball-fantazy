#include "Player.hpp"

#include <string>

class Gk : public Player
{
private:
    enum
    {
        POS
    };

public:
    Gk(int &role, string &name);

    virtual void set_position(int pos);
};
