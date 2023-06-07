#include "Input.hpp"
#include "Data_base.hpp"

int main()
{
    Input input;
    Data_base data_base(input.get_league(), input.get_weeks());

    try
    {
        data_base.show();
    }
    catch (runtime_error &ex)
    {
        cout << ex.what() << '\n';
    }
}