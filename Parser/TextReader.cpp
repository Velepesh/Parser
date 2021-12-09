#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "TextReader.h"

using namespace std;

vector<string> TextReader::GetCod(string path)
{
    vector<string> cod;
    string line = "";

    ifstream in(_path);

    if (in.is_open())
        while (getline(in, line))
            cod.push_back(line);

    in.close();

    return cod;
}

void TextReader::WriteText(vector<string> parsedText)
{
    vector<string> cod;
    string line = "";

    ofstream out;

    string path = GetDirectory() + GetFileName() + "Parsed.txt";

    out.open(path);

    if (out.is_open())
        for (size_t i = 0; i < parsedText.size(); i++)
            out << parsedText[i];
}

string TextReader::GetFileName()
{
    string fileName = "";

    fileName = _path.substr(_path.find_last_of("/\\"));
    fileName = fileName.substr(0, fileName.find_last_of('.'));

    return fileName;
}

string TextReader::GetDirectory()
{
    string directory;

    const size_t lastSlashIdex = _path.rfind('\\');

    if (string::npos != lastSlashIdex)
        directory = _path.substr(0, lastSlashIdex);

    return directory;
}