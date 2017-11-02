#pragma once
///////////////////////////////////////////////////////////////////////////////
// symbol_table.hpp
#ifndef SYMBOL_TABLE_HPP__
#define SYMBOL_TABLE_HPP__

#include <vector>
#include <utility>
#include <algorithm>

class symbols_table {
public:

    void push(const std::pair<std::string, int>& local_variable)
    {
        table.push_back(local_variable);
    }

    void pop()
    {
        if (table.empty())
            throw std::runtime_error("trying pop scope from empty table");
        table.pop_back();
    }

    bool lookup(const std::string& name, int& value) const
    {
        auto i = find_if(rbegin(table), rend(table), [&name](auto const& el) -> bool { return el.first == name; });
        if (i == rend(table))
            return false;

        value = i->second;
        return true;
    }

private:

    std::vector<std::pair<std::string, int>> table;
};




#endif

