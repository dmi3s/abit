#include <iostream>
#include <string>

#include <boost/spirit/include/qi.hpp>

#include "calculator_grammar.hpp"

int main()
{
    std::cout << "//////////////////////////////////////////////\n\n";
    std::cout << "Expression parser...\n";
    std::cout << "//////////////////////////////////////////////\n\n";
    std::cout << "Type an expression... or [q or Q] to quit\n\n";

    std::string expression;

    calculator_interpreter<std::string::iterator> calc;

    while (true)
    {
        std::getline(std::cin, expression);
        if (expression == "q" || expression == "Q") break;
        std::string::iterator  begin = expression.begin()
            , end = expression.end();

        int result;
        bool success = qi::phrase_parse(begin
            , end
            , calc
            , qi::space
            , result);

        std::cout << "-----------------------\n";
        if (success && begin == end)
        {
            std::cout << "Parsing succeeded\n";
            std::cout << "result = " << result << "\n";
        }
        else
        {
            std::cout << "Parsing failed\nstopped at: \""
                << std::string(begin, end) << "\"\n";
        }
        std::cout << "-----------------------\n";
    }
}