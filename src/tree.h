#pragma once

#include <string>
#include <iostream>
#include <regex>


struct TreeNode
{
    // parameters
    int value;
    TreeNode* armLeft  = nullptr;
    TreeNode* armRight = nullptr;
    TreeNode* parent   = nullptr;

    // constructor
    TreeNode(int __value) : value(__value) {}
    TreeNode(int __value, TreeNode* __parent) : value(__value), parent(__parent) {}

    // functions
    void AddNode(int __value) {
        if (value == __value) return;

        if (value > __value) {
            if (armLeft == nullptr) armLeft = new TreeNode(__value, this);
            else armLeft->AddNode(__value);
        }
        if (value < __value) {
            if (armRight == nullptr) armRight = new TreeNode(__value, this);
            else armRight->AddNode(__value);
        }
    }

    void PrintTree() { std::cout << ToString() << std::endl; }

    int DepthTree() {
        int armLeftDepth = armLeft == nullptr ? 0 : armLeft->DepthTree();
        int armRightDepth = armRight == nullptr ? 0 : armRight->DepthTree();
        return 1 + (armLeftDepth > armRightDepth ? armLeftDepth : armRightDepth);
    }

    TreeNode* SearchNode(int __value) {
        if (value == __value) return this;
        if (value > __value && armLeft != nullptr)
            return armLeft->SearchNode(__value);
        if (value < __value && armRight != nullptr)
            return armRight->SearchNode(__value);
        return nullptr;
    }

    void DelTree() {
        if (armLeft != nullptr) {
            armLeft->parent = nullptr;
            armLeft->DelTree();
        }
        if (armRight != nullptr) {
            armRight->parent = nullptr;
            armRight->DelTree();
        }
        if (parent != nullptr) {
            if (parent->armLeft == this)
                parent->armLeft = nullptr;
            if (parent->armRight == this)
                parent->armRight = nullptr;
            parent->DelTree();
        }
        delete this;
    }

    void _CutSelfFromParent() {
    }

    void DelNode() {

        // no arms
        if (armLeft == nullptr && armRight == nullptr){
            if (parent != nullptr) {
                if (parent->armLeft == this)
                    parent->armLeft = nullptr;
                if (parent->armRight == this)
                    parent->armRight = nullptr;
            }
        }

        // two arms; left has right
        else if (armLeft != nullptr && armRight != nullptr && armLeft->armRight != nullptr){
            // find best
            TreeNode* best = armLeft;
            while (best->armRight != nullptr)
                best = best->armRight;
            
            
            // cut best
            best->parent->armRight = best->armLeft;

            // paste best
            best->armLeft = armLeft;
            best->armRight = armRight;
            best->parent = parent;
            if (parent->armLeft == this)
                parent->armLeft = best;
            if (parent->armRight == this)
                parent->armRight = best;            
        }

        // two arms; left has no right
        else if (armLeft != nullptr && armRight != nullptr && armLeft->armRight == nullptr) {
            armLeft->armRight = armRight;
            if (parent->armLeft == this)
                parent->armLeft = armLeft;
            if (parent->armRight == this)
                parent->armRight = armLeft; 
        }

        // one arm; left only
        else if (armLeft != nullptr && armRight == nullptr) {
            armLeft->parent = parent;
            if (parent->armLeft == this)
                parent->armLeft = armLeft;
            if (parent->armRight == this)
                parent->armRight = armLeft; 
        }

        // one arm; right only
        else if (armLeft == nullptr && armRight != nullptr) {
            armRight->parent = parent;
            if (parent->armLeft == this)
                parent->armLeft = armRight;
            if (parent->armRight == this)
                parent->armRight = armRight;
        }

        delete this;
    }

    std::string ToString() {
        std::string returnString = std::to_string(value);
        if (armLeft != nullptr) 
            returnString += "\n├" + std::regex_replace(armLeft->ToString(), std::regex("\n"), "\n│");
        if (armRight != nullptr) 
            returnString += "\n├" + std::regex_replace(armRight->ToString(), std::regex("\n"), "\n│");

        return returnString;
    }
};

