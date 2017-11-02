#pragma once
///////////////////////////////////////////////////////////////////////////////
// interpret.hpp
#ifndef INTERPRET_HPP__
#define INTERPRET_HPP__

#include <ostream>
#include <string>
#include <boost/optional.hpp>

namespace abit {

    boost::optional<int> interpret(std::string::const_iterator begin, std::string::const_iterator end, std::ostream& errors_stream);

}

#endif