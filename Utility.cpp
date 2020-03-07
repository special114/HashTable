#include "Utility.h"

/* File from HashTable project
 * author: Rafał Surdej
 */

using namespace std;

InvalidHashFunction::InvalidHashFunction(const string& s) : runtime_error(s) {}

void addToTable(HashTable<string, string>& t1, string& line, size_t p)
{
    line.erase(LINE_BEG, p + DEFINE_LENGTH);            // deleting "#define"
    p = line.find(' ');                                 // looking for a word to redefine
    string key = line.substr(LINE_BEG, p);
    line.erase(LINE_BEG, p + 1);
    if (t1.find(key))
        t1.erase(key);
    t1.insert(key, line);
    line = "";                                          // the rest of the line is in dictionary
}

/* The function below is similar to #define directive. It changes the meaning of certain strings
 * from input file and stores the changed file in output file
 */

int defineFun ()
{
    fstream input_f, output_f;
    input_f.exceptions(ifstream::failbit | ifstream::badbit);
    output_f.exceptions(ofstream::failbit | ofstream::badbit);
    try
    {
        input_f.open(IN_FILE, ios::in);
    }
    catch(ifstream::failure& err)
    {
        cout << err.what() << endl;
        perror("Problem with input file.");
        return 1;
    }
    try
    {
        output_f.open(OUT_FILE, ios::trunc | ios::out);
    }
    catch(ofstream::failure& err)
    {
        input_f.close();
        cout << err.what() << endl;
        perror("Problem with output file.");
        return 1;
    }
    input_f.exceptions(ifstream::goodbit);

    string line;
    size_t pos;
    bool is_found = false;
    while(!is_found && getline(input_f, line))              // Looking for first #define appearance
    {
        pos = line.find("#define");

        if (pos != line.npos)
            is_found = true;
        else
            output_f << line << "\n";
    }
    if (is_found)
    {
        HashTable<string, string> dict;
        string tmp = line.substr(LINE_BEG, pos);
        output_f << tmp;
        if (pos)
            output_f << '\n';
        addToTable(dict, line, pos);
        while (getline(input_f, line))
        {
            bool new_line_flag = true;
            while (line.length())
            {
                pos = line.find_first_of(" ;,   ");          // dividing a line into words and looking for "#define" or changing
                                                             // redefined words
                string word;
                if (pos != line.npos)
                    word = line.substr(LINE_BEG, pos);
                else
                    word = line;
                if (!word.compare("#define"))
                {
                    addToTable(dict, line);
                    new_line_flag = false;
                }
                else
                {
                    Node<string, string>* dict_word = dict.find(word);  // changing word from input file if it exsists in dictionary
                    if (dict_word)
                        output_f << dict_word->data;
                    else
                        output_f << word;
                    line.erase(LINE_BEG, pos);
                    pos = line.find_first_not_of(" ;,   ");             // putting additional whitespace into output file and deleting them
                                                                        // from our line
                    if (pos != line.npos)
                    {
                        tmp = line.substr(LINE_BEG, pos);
                        output_f << tmp;
                        line.erase(LINE_BEG, pos);
                    }
                    else
                    {
                        output_f << line;
                        line = "";                                      // similar to above but whitespace is at the end of a line
                    }
                   new_line_flag = true;
                }
            }
            if(new_line_flag)
                output_f << "\n";
        }
    dict.print(cout);
    }
    input_f.close();
    output_f.close();
    return 0;
}
