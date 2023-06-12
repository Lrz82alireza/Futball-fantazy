#include "Player.hpp"

class Fw : public Player
{
private:
    enum
    {
        LEFT_POS_FW = 8,
        RIGHT_POS_FW = 10,
    };
public:
    Fw(int &role, string &name);

    virtual bool is_clean_sheet(){ return false; }
    virtual void set_position(int pos);
};


