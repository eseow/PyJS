#include <iostream>
#include <string>
#include "../include/Scanner.h"
#include "Parser.h"
using std::string;

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        string filename = argv[1];
        std::ifstream file;
        file.open(filename, std::ios::binary);
        if (file.is_open())
        {
            Scanner *scanner = new Scanner(&file);
            scanner->scanTokens();
            scanner->printTokens();
            std::cout << "\n";
            Parser parser(scanner->getTokens());
            parser.parse();
            std::vector<Expr *> exprs = parser.getExprs();
            for (int i = 0; i < (int)exprs.size(); i++)
            {
                std::cout << exprs.at(i)->toString();
            }
        }
        else
        {
            std::cout << "File does not exist: " << filename << std::endl;
        }
        file.close();
    }
    else
    {
        std::cout << "No file name provided." << std::endl;
    }
    return 0;
}