#pragma once

#include <memory>
#include <map>
#include "Resource.hpp"
#include <thread>
#include <mutex>

class ResourceManager
{
private:
    std::map<string, shared_ptr<Resource>> resources;
    std::mutex mtx;

public:
    shared_ptr<Resource> getResource(const string &name);
    void UniqueExample();
    void SharedExample();
    void WeakExample();
    void PrintResources();
    void Worker(const string& name);
};
