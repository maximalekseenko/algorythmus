#pragma once

#include "treecore.h"

#include <string>
#include <iostream>
#include <regex>

struct Tree : public TreeCore<Tree> { 
    Tree (int __value) : TreeCore(__value) { }
    void Update(){}
    std::string ToString() { return std::to_string(__get_value()); }
};

