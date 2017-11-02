#pragma once
///////////////////////////////////////////////////////////////////////////////
// interpret.hpp
#ifndef INTERPRET_HPP__
#define INTERPRET_HPP__

#include <ostream>
#include <string>
#include <boost/optional.hpp>

namespace abit {

    boost::optional<int> interpret(std::string::iterator begin, std::string::iterator end, std::ostream& errors_stream);

}

#endif