#include "Player.hpp"

class Fw : public Player
{
private:
    enum
    {
        LEFT_POS_FW = 8,
        RIGHT_POS_FW = 10,
    };

    enum
    {
        GOAl_POINT = 3,
        ASSIST_POINT = 1,
        DEMERIT_POINT = -1
    };

public:
    Fw(int &role, string &name);

    virtual bool is_clean_sheet(){ return false; }
    virtual void set_position(int pos);

    virtual void set_score(vector<shared_ptr<Player>> against_composition, int goals_for, int goals_against);
};


