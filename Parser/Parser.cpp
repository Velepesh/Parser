#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <fstream>
#include <filesystem>
#include "TextReader.h"
#include "Parcer.h"

namespace fs = std::filesystem;
using namespace std;

void Parsing(string argv);

string GetFileExtension(const std::string FileName)
{
    int idx = FileName.rfind('.');
    if (idx != std::string::npos)
    {
        std::string extension = FileName.substr(idx);
        return extension;
    }

    return "";
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
   
    string extension = ".c";

    for (int i = 1; i < argc; i++)
    {
        try
        {
            string path(argv[i]);

            if (GetFileExtension(path) == extension)
            {
                Parsing(path);
            }
            else
            {
                fs::directory_iterator iterator(path);

                for (; iterator != fs::end(iterator); iterator++)
                {
                    if (iterator->path().extension() == extension)
                    {
                        Parsing(iterator->path().string());
                    }
                }
            }
        }
        catch (std::exception& e)
        {
            cout << "Error: " << e.what() << '\n';
        }
    }

   /* for (int i = 1; i < argc; i++)
    {
        string path(argv[i]);
        TextReader textReader = TextReader(path);
        vector<string> cod = {};
        Parcer parcer;
        cod = textReader.GetCod(path);

        textReader.WriteText(parcer.Parse(cod));
    }*/

    return 0;
}

void Parsing(string argv)
{
    string path(argv);
    TextReader textReader = TextReader(argv);
    vector<string> cod = {};
    Parcer parcer;
    cod = textReader.GetCod(argv);

    textReader.WriteText(parcer.Parse(cod));
}