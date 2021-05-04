#pragma once

#include <string>
#include <any>
#include <map>

class TreeData
{
public:
    TreeData() = default;
	TreeData(std::string name, std::any value):value(value), name(name){}
    TreeData(const TreeData &p1) {name = p1.name; value = p1.value; }
    TreeData& operator=(const TreeData& other)
    {
        if (this != &other) { // protect against invalid self-assignment
            name = other.name;
            value = other.value;
        }
        // by convention, always return *this
        return *this;
    }
    virtual ~TreeData(){}

    template<typename Type>
    Type Value(void){ return std::any_cast<Type>(value); }
    template<typename Type>
    void Value(Type new_value) { value = new_value; }

    std::string Name(){ return name; }
private:
    std::any value;
    std::string name;
};

using TreeNode = std::map<std::string, TreeData>;
