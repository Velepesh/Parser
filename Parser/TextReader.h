#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "TextReader.h"

using namespace std;

class TextReader
{
    private:
        string _path;
        string GetFileName();
        string GetDirectory();
    public:
        TextReader(string path)
        {
            _path = path;
        }

        vector<string> GetCod(string);
        void WriteText(vector<string>);
};