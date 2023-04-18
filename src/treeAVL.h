#pragma once

#include "treecore.h"
#include <string>
#include <iostream>
#include <regex>


struct TreeAVL : public TreeCore<TreeAVL> {

    bool __is_balanced() {
        return __get_balance() < 2;
    }

    int __get_balance() {
        return abs(
            (__is_arm_left_exists() ? __get_arm_left()->DepthTree() : 0)
             - 
            (__is_arm_right_exists() ? __get_arm_right()->DepthTree() : 0)
        );
    }

    bool __is_left_unbalanced() {
        return  DepthTree(__get_arm_left()) - DepthTree(__get_arm_right()) > 1;
    }
    bool __is_right_unbalanced() {
        return  DepthTree(__get_arm_left()) - DepthTree(__get_arm_right()) < -1;
    }

    void __rotation_small_left() {
        TreeAVL* __b_arm = __get_arm_right();
        __b_arm->__set_parent(__get_parent());

        if (__b_arm->__is_arm_left_exists())
            __b_arm->__get_arm_left()->__set_parent(__this_as_t_node());

        __set_parent(__b_arm);
    }

    void __rotation_small_right() {
        TreeAVL* __b_arm = __get_arm_left();
        __b_arm->__set_parent(__get_parent());

        if (__b_arm->__is_arm_right_exists())
            __b_arm->__get_arm_right()->__set_parent(__this_as_t_node());

        __set_parent(__b_arm);
    }

    void __rotation_big_left() {
        TreeAVL* __b_arm = __get_arm_right();
        TreeAVL* __c_arm = __b_arm->__get_arm_left();
        __c_arm->__set_parent(__get_parent());

        if (__c_arm->__is_arm_left_exists())
            __c_arm->__get_arm_left()->__set_parent(__this_as_t_node());
        if (__c_arm->__is_arm_right_exists())
            __c_arm->__get_arm_right()->__set_parent(__b_arm);
            
        __b_arm->__set_parent(__c_arm);
        __set_parent(__c_arm);
    }

    void __rotation_big_right() {
        TreeAVL* __b_arm = __get_arm_left();
        TreeAVL* __c_arm = __b_arm->__get_arm_right();
        __c_arm->__set_parent(__get_parent());

        if (__c_arm->__is_arm_left_exists())
            __c_arm->__get_arm_left()->__set_parent(__b_arm);
        if (__c_arm->__is_arm_right_exists())
            __c_arm->__get_arm_right()->__set_parent(__this_as_t_node());

        __b_arm->__set_parent(__c_arm);
        __set_parent(__c_arm);
    }

    void __balance_back() {
        if (!__is_balanced()){
            if (__is_left_unbalanced()){
                if (__get_arm_left()->__is_left_unbalanced()) 
                    __rotation_small_right();
                else if (__get_arm_left()->__is_right_unbalanced())
                    __rotation_big_right();
            }
            else if (__is_right_unbalanced()){
                if (__get_arm_right()->__is_right_unbalanced())
                    __rotation_small_left();
                else if (__get_arm_right()->__is_left_unbalanced())
                    __rotation_big_left();
            }
        } 

        if (!__is_root()) __get_parent()->__balance_back();
    }

    void AddNode(int __value) {
        TreeCore::AddNode(__value);

        __balance_back();   
    }

    void DelNode() {
        TreeAVL* __hash_parent = __get_parent();
        TreeCore::DelNode();
        __hash_parent->__balance_back();
    }

    TreeAVL (int __value) : TreeCore(__value) { }
    void Update(){}
    std::string ToString() { return std::to_string(__get_value()) + " - " + std::to_string(__get_balance()); }
};

