#pragma once

#include "treecore.h"

#include <string>
#include <iostream>
#include <regex>

struct Tree : public TreeCore<Tree> { 
    Tree (int __value, ...) : TreeCore(__value) {
    }
};

