#include "Input.hpp"

void Input::set()
{
    string line;
    getline(cin, line);
    if (line == "")
        return;

    vector<string> temp = seperate_words(line, " ");
    if (temp.size() <= 2)
        throw runtime_error("INVALID_ARGUMENTS");

    command.first = temp[0];
    command.second = temp[1];

    for (vector<string>::size_type i = 2; i < temp.size(); i++)
        value.push_back(temp[i]);
}

void Input::clear()
{
    command.first.clear();
    command.second.clear();
    value.clear();
}

shared_ptr<CSV_input> Input::read_info_from_scv(string file_name)
{
    ifstream data(file_name);
    shared_ptr<CSV_input> input = make_shared<CSV_input>();

    int row = 0;

    string line;
    getline(data, line); // first row
    while (getline(data, line))
    {
        input->resize(row + 1);
        stringstream lineStream(line);
        string cell;
        vector<string> words;

        while (getline(lineStream, cell, ','))
        {
            words = seperate_words(cell, ";");
            (*input)[row].push_back(words);
        }
    }
    if (input->size() == 0)
        throw runtime_error("empty input file!");
    data.close();
    return input;
}

void Input::init_csv_data()
{
    try
    {
        string file_name;
        int week_num = 1;

        league = read_info_from_scv(LEAGUE);
        while (true)
        {
            ifstream file;
            file_name = WEEKS_ADDRESS + to_string(week_num) + ".csv";
            file.open(file_name);
            if (!file)
                return;
            shared_ptr<CSV_input> week = read_info_from_scv(file_name);
            weeks.push_back(week);
            file.close();
        }
    }
    catch(runtime_error & ex)
    {
        cout << ex.what() << endl;
    }
}
