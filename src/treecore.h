#pragma once

#include <string>
#include <iostream>
#include <regex>


template<typename T_Node>
struct TreeCore {

    private:

    int value;
    T_Node* armLeft  = nullptr;
    T_Node* armRight = nullptr;
    T_Node* parent   = nullptr;

    public:

    // constructors and destructors
    TreeCore(int __value) : value(__value) {}
    virtual ~TreeCore(){}

    T_Node* __this_as_t_node() { return dynamic_cast<T_Node*>(this); }

    public: // getters
        T_Node* __get_arm_left() { return armLeft; }
        T_Node* __get_arm_right() { return armRight; }
        T_Node* __get_parent() { return parent; }
        int __get_value() { return value; }
    
    public: // common
        bool __is_root() { return !__is_parent_exists(); }
        bool __is_leaf() { return !__is_arm_any_exists(); }

    public: // ckecks

        // arms and parent checks
        bool __is_arm_left(T_Node* __node_to_check) { return __node_to_check == __get_arm_left(); }
        bool __is_arm_left_exists() { return !__is_arm_left(nullptr); }
        
        bool __is_arm_right(T_Node* __node_to_check) { return __node_to_check == __get_arm_right(); }
        bool __is_arm_right_exists() { return !__is_arm_right(nullptr); }

        bool __is_parent(T_Node* __node_to_check) { return __node_to_check == __get_parent(); }
        bool __is_parent_exists() { return !__is_parent(nullptr); }

        // arm checks extend
        bool __is_arm(T_Node* __node_to_check) {
            return __is_arm_left(__node_to_check) || __is_arm_right(__node_to_check);
        }
        bool __is_arm_any_exists() {
            return __is_arm_left_exists() || __is_arm_right_exists();
        }
        bool __is_arm_all_exists() {
            return __is_arm_left_exists() && __is_arm_right_exists();
        }

        // value checks
        bool __is_value_left(int __value_to_check) { return __value_to_check < __get_value(); }
        bool __is_value_right(int __value_to_check) { return __value_to_check > __get_value(); }
        bool __is_value_this(int __value_to_check) { return __value_to_check == __get_value(); }

    protected: // set parent
        void __set_parent(T_Node* __new_parent_node) {

            // old parent remove this (arm)
            if (__is_parent_exists()){
                if (__get_parent()->__is_arm_left(__this_as_t_node()))
                    __get_parent()->armLeft = nullptr;
                else if (__get_parent()->__is_arm_right(__this_as_t_node()))
                    __get_parent()->armRight = nullptr;
                else throw "Set Parent Error in old parent";
            }

            // new parent set correct arm
            if (__new_parent_node != nullptr) {
                if (__new_parent_node->__is_value_left(__get_value())) {
                    if (__new_parent_node->__is_arm_left_exists())
                        __new_parent_node->__get_arm_left()->__set_parent(nullptr);
                    __new_parent_node->armLeft = __this_as_t_node();
                }
                else if (__new_parent_node->__is_value_right(__get_value())) {
                    if (__new_parent_node->__is_arm_right_exists())
                        __new_parent_node->__get_arm_right()->__set_parent(nullptr);
                    __new_parent_node->armRight = __this_as_t_node();
                }
                else throw "Set Parent Error in new parent";
            }

            // set parent
            parent = __new_parent_node;
        }

    public:

        void AddNode(int __value) {
            if (__is_value_this(__value)) return;

            else if (__is_value_left(__value)) {
                if (__is_arm_left_exists()) 
                    __get_arm_left()->AddNode(__value);
                else 
                    (new T_Node(__value))->__set_parent(__this_as_t_node());
            }
            else if (__is_value_right(__value)) {
                if (__is_arm_right_exists()) 
                    __get_arm_right()->AddNode(__value);
                else 
                    (new T_Node(__value))->__set_parent(__this_as_t_node());
            }
        }

        void PrintTree() { std::cout << GetFullString() << std::endl; }


        int DepthTree() {
            int armLeftDepth = __is_arm_left_exists() ? armLeft->DepthTree() : 0;
            int armRightDepth = __is_arm_right_exists() ? armRight->DepthTree() : 0;
            return 1 + (armLeftDepth > armRightDepth ? armLeftDepth : armRightDepth);
        }

        T_Node* SearchNode(int __value) {
            if (__is_value_this(__value)) return __this_as_t_node();
            if (__is_value_left(__value) && __is_arm_left_exists())
                return __get_arm_left()->SearchNode(__value);
            if (__is_value_right(__value) && __is_arm_right_exists())
                return __get_arm_right()->SearchNode(__value);
            return nullptr;
        }

        void DelTree() {
            if (__is_arm_left_exists()) {
                armLeft->DelTree();
            }
            if (__is_arm_right_exists()) {
                armRight->DelTree();
            }
            DelNode();
        }

        void DelNode() {

            // no arms
            if (!__is_arm_any_exists()){
                if (!__is_root()) {
                    __set_parent(nullptr);
                }
            }

            // two arms; left has right
            else if (__is_arm_all_exists() && __get_arm_left()->__is_arm_right_exists()) {

                // find biggest node on the left
                T_Node* __node_to_set = __get_arm_left();
                while (__node_to_set->__is_arm_right_exists())
                    __node_to_set = __node_to_set->__get_arm_right();

                if (__node_to_set->__is_arm_left_exists())
                    __node_to_set->__get_arm_left()->__set_parent(__node_to_set->__get_parent());
                
                // set biggest node
                __node_to_set->__set_parent(__get_parent());
                __get_arm_left()->__set_parent(__node_to_set);
                __get_arm_right()->__set_parent(__node_to_set);
            }

            // two arms; left has no right
            else if (__is_arm_all_exists() && !__get_arm_left()->__is_arm_right_exists()) {
                __get_arm_right()->__set_parent(__get_arm_left());
                __get_arm_left()->__set_parent(__get_parent());
            }

            // one arm; left only
            else if (__is_arm_left_exists() && !__is_arm_right_exists()) {
                __get_arm_left()->__set_parent(__get_parent());
            }

            // one arm; right only
            else if (!__is_arm_left_exists() && __is_arm_right_exists()) {
                __get_arm_right()->__set_parent(__get_parent());
            }

            delete this;
        }

        std::string GetFullString() {
            std::string returnString = __this_as_t_node()->ToString();
            if (__is_arm_left_exists()) 
                returnString += "\n├" + std::regex_replace(__get_arm_left()->GetFullString(), std::regex("\n"), "\n│");
            if (__is_arm_right_exists()) 
                returnString += "\n├" + std::regex_replace(__get_arm_right()->GetFullString(), std::regex("\n"), "\n│");

            return returnString;
        }


    public:
        void Update();
        std::string ToString();

};

