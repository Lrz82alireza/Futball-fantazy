#include "Input.hpp"
#include "Data_base.hpp"
#include <typeinfo>

int main()
{
    Input input;
    Data_base data_base(input.get_league(), input.get_weeks());


while (input.set())
{
    try
    {
        data_base.manage_command(input.command_(), input.value_());
    }
    catch (runtime_error &ex)
    {
        cout << ex.what() << '\n';
    }
    input.clear();
}

}