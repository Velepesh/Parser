#include <iostream>
#include <string>
#include <vector>
#include "TextReader.h"
#include "Parcer.h"

using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
   
   

    for (int i = 1; i < argc; i++)
    {
        string path(argv[i]);
        TextReader textReader = TextReader(path);
        vector<string> cod = {};
        Parcer parcer;
        cod = textReader.GetCod(path);

        textReader.WriteText(parcer.Parse(cod));
        //C:\Users\shepe\source\repos\Parser\Parser\test.c
        //C:\Users\shepe\source\repos\Parser\Debug\Parser.exe
    }

    return 0;
}