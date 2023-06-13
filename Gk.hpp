#include "Player.hpp"

#include <string>

class Gk : public Player
{
private:
    enum
    {
        POS
    };

    enum
    {
        CLEAN_SHEET_POINT = 5,
        DEMERIT_POINT = -1,
        DEAFAULT_POINT = 3
    };

public:
    Gk(int &role, string &name);

    virtual void set_score(vector<shared_ptr<Player>> against_composition , int goals_for , int goals_against);

    virtual void set_position(int pos);
};
