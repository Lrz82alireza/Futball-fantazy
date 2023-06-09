#include "Player.hpp"

class Df : public Player
{
private:
    enum
    {
        LEFT_POS_DF = 1,
        RIGHT_POS_DF = 4,
    };

    enum
    {
        CLEAN_SHEET_POINT = 2,
        GOAl_POINT = 4,
        ASSIST_POINT = 3,
        DEAFAULT_POINT = 1,
        DEMERIT_POINT = -1,
    };

    void set_special_point(vector<shared_ptr<Player>> against_composition);
    void demerit_score(vector<shared_ptr<Player>> against_composition , int pos);

public:
    Df(int &role, string &name);

    virtual void set_score(vector<shared_ptr<Player>> against_composition, int goals_for, int goals_against);

    virtual void set_position(int pos);
};
