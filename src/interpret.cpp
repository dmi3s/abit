#include "interpret.hpp"
#include "calculator_grammar.hpp"
#include <stdexcept>

namespace abit {

    boost::optional<int> interpret(std::string::iterator begin, std::string::iterator end, std::ostream& errors_stream)
    {
        using namespace std;

        try {
            calculator_interpreter<string::iterator> calc{ errors_stream };

            int result;
            bool success = qi::phrase_parse(begin
                , end
                , calc
                , qi::space
                , result);
            if (success && begin == end)
                return result;
            else
            {
                errors_stream << "Parsing failed\nstopped at: \""
                    << std::string(begin, end) << "\"\n";
                return boost::none;
            }

        }
        catch (const std::runtime_error& e)
        {
            errors_stream << "Runtime exception: \"" << e.what() << "\"" << std::endl;
            return boost::none;
        }
    }

}
