#include "Resource.hpp"
#include <iostream>

Resource::Resource(const string& name) 
{
    this->name = name;
    cout << " Resource " << name << " created\n";
}

Resource::~Resource()
{
    cout << " Resource " << name << " destoryed\n";
}

void Resource::use() const
{
    cout << " Resource " << name << " is being used\n";
}