#include "Input.hpp"
#include "Data_base.hpp"

int main()
{
    Input input;

    Data_base data_base(input.get_league(), input.get_weeks());

}