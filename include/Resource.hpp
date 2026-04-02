#pragma once
#include <memory>
#include <string>
using namespace std;

class Resource
{

private:
    string name;

public:
    Resource(const string& name);
    ~Resource();

    void use() const;
};