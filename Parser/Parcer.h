#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

class Parcer
{
private:
    string _assignExpr = "[^=,<,>]=[^=]";
    string _varExpr = "[a-zA-Z0-9_]";
    string _numberExpr = "0$|^[1-9][0-9]*";
    string _whitespaceExpr = "^\\s+$";
    vector<string> _splittingCod;

    string ParseAssignExpr(string);
    void RemoveSpaces(vector<string>);
    vector<string> SplitBySemicolon(string&);
    vector<string> PrepeareForOutput(vector<string>);

public:
    vector<string> Parse(vector<string>);
};