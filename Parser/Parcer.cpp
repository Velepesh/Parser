#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include "Parcer.h"

using namespace std;

vector<string> Parcer::Parse(vector<string> cod)
{
    regex assign(_assignExpr);
    cmatch result;

    for (size_t i = 0; i < cod.size(); i++)
    {
        if (regex_search(cod[i].c_str(), result, assign))
        {
            vector<string> splittingBySemicolon = SplitBySemicolon(cod[i]);
            RemoveSpaces(splittingBySemicolon);


            size_t index = i + 1;
            string splitting = "";

            for (size_t j = 0; j < splittingBySemicolon.size(); j++)
            {
                splitting = to_string(index) + " " + ParseAssignExpr(splittingBySemicolon[j]);
                _splittingCod.push_back(splitting);
            }
        }
    }

    return PrepeareForOutput(_splittingCod);
}


void Parcer::RemoveSpaces(vector<string> input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        input[i].erase(
            unique_copy(input[i].begin(), input[i].end(), input[i].begin(),
                [](char c1, char c2) { return c1 == ' ' && c2 == ' '; }),
            input[i].end());
    }
}

vector<string> Parcer::SplitBySemicolon(string& input)
{
    vector<string> result;
    string str = "";

    for (size_t i = 0; i < input.size(); i++)
    {
        str += input[i];

        if (input[i] == ';')
        {
            result.push_back(str);
            str = "";
        }
    }

    return result;
}

string Parcer::ParseAssignExpr(string input)
{
    regex var(_varExpr);
    regex whitespace(_whitespaceExpr);
    cmatch result;

    string buffer = "";
    string previousSymbol = "";

    while (input.at(0) != ';')
    {
        string symbol = string(1, input.at(0));

        if (regex_search(symbol.c_str(), result, var))
        {
            buffer.append(symbol);
        }
        else if (regex_search(symbol.c_str(), result, whitespace))
        {
            if (regex_search(previousSymbol.c_str(), result, var))
            {
                string sym = string(1, input.at(1));

                if (regex_search(sym.c_str(), result, var))
                    buffer.erase(0, buffer.length());
            }
        }
        else
        {
            buffer.append(" ");
        }

        previousSymbol = symbol;
        input.erase(0, 1);
    }

    return buffer;
}

vector<string> Parcer::PrepeareForOutput(vector<string> splittingCod)
{
    vector<string> parsedCod;
    regex number(_numberExpr);
    cmatch matchResult;

    for (size_t i = 0; i < splittingCod.size(); i++)
    {
        string parsed = "";
        vector<string> result;

        stringstream ss(splittingCod[i]);

        string word = "";

        bool isIndex = true;

        while (ss >> word) 
        {
            if (isIndex == false)
            {
                if (regex_search(word.c_str(), matchResult, number) == false)
                    result.push_back(word);
            }
            else
            {
                result.push_back(word);
                isIndex = false;
            }
        }

        if (result.size() > 2)
        {
            parsed += "Строка " + result.at(0) + " Параметр " + result.at(1) + " зависит от: ";

            for (size_t i = 2; i < result.size(); i++)
            {
                if (i == result.size() - 1)
                    parsed += result[i] + "\n";
                else
                    parsed += result[i] + ", ";
            }

            parsedCod.push_back(parsed);
        }
    }

    return parsedCod;
}