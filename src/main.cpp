#include <iostream>
#include <string>

#include "interpret.hpp"
#include <boost/optional/optional_io.hpp>


int main(int argc, char *argv[])
{
    using namespace std;
    if (argc != 2)
    {
        cerr << "Usage: calculator expression\n";
        return 1;
    }

    string expr{ argv[1] };

    if (auto res = abit::interpret(begin(expr), end(expr), cerr))
    {
        cout << res << endl;
        return 0;
    }
    else
        return 2;
}