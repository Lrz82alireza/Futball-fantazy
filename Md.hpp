#include "Player.hpp"

class Md : public Player
{
private:
    enum
    {
        LEFT_POS_MD = 5,
        RIGHT_POS_MD = 7,
    };

    enum
    {
        CLEAN_SHEET_POINT = 1,
        GOAl_POINT = 3,
        ASSIST_POINT = 2,
        DEMERIT_POINT = -1,
    };

    void set_special_point(vector<shared_ptr<Player>> against_composition);
    void demerit_score(vector<shared_ptr<Player>> against_composition , int pos);

public:
    Md(int &role, string &name);

    void set_score(vector<shared_ptr<Player>> against_composition, int goals_for, int goals_against) override;

    virtual void set_position(int pos);
};
