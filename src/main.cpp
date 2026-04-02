#include "Resource.hpp"
#include "ResourceManger.hpp"
#include <vector>

int main()
{
    unique_ptr<ResourceManager> obj = make_unique<ResourceManager>();

    // obj->getResource("weak1");
    // obj->UniqueExample();
    // obj->getResource("unique1");
    // obj->WeakExample();
    // obj->getResource("weak1");

    obj->SharedExample();
    obj->getResource("shared1");
    obj->PrintResources();

    vector<thread> threads;

    for (int i = 0; i < 5; i++)
    {
        threads.emplace_back(&ResourceManager::Worker, obj.get(), "File1");
    }

    for (auto &thread : threads)
    {
        if (thread.joinable())
            thread.join();
    }

    return 0;
}