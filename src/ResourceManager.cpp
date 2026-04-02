#include "ResourceManger.hpp"
#include <iostream>

/* 🚀 Simple Way to Remember
auto → "Give me a copy"
auto& → "Let me edit the original"
const auto& → "Let me see, don’t let me touch"

"Why use map<string, weak_ptr<Resource>>?"

"To cache and reuse resources by key while avoiding ownership, ensuring that resources are automatically
destroyed when no longer in use."
*/

shared_ptr<Resource> ResourceManager::getResource(const string &name)
{
    {
        // lock_guard<mutex> lock(mtx);
        auto it = resources.find(name);
        shared_lock<shared_mutex> readLock(shmtx);

        if (it != resources.end())
        {
            cout << "Resuing existing resource\n";
            return it->second;
        }
    }
    cout << "Creating new resource\n";

    shared_ptr<Resource> resource = make_shared<Resource>(name);
    {
        // lock_guard<mutex> lock(mtx);
        shared_lock<shared_mutex> writelock(shmtx);
        auto it = resources.find(name);
        if (it != resources.end())
        {
            return it->second;
        }
        resources[name] = resource;
    }
    return resource;
}

void ResourceManager::UniqueExample()
{
    unique_ptr<Resource> uniquePointer = make_unique<Resource>("Unique1");
    uniquePointer->use();

    unique_ptr<Resource> uniqueCopyPointer = move(uniquePointer);

    if (!uniquePointer)
    {
        cout << " uniquePointer is null\n";
    }
    uniqueCopyPointer->use();
}

void ResourceManager::SharedExample()
{
    shared_ptr<Resource> sharedPointer = make_shared<Resource>("Shared1");

    cout << " Count of sharedpointer " << sharedPointer.use_count() << endl;

    auto secondSharedPointer = sharedPointer;

    cout << " Count of sharedpointer after sharing " << sharedPointer.use_count() << endl;

    sharedPointer->use();
}

void ResourceManager::WeakExample()
{
    shared_ptr<Resource> firstSharedPointer = make_shared<Resource>("Weak1");

    cout << " count of firstSharedPointer " << firstSharedPointer.use_count() << endl;

    weak_ptr<Resource> weakPointer = firstSharedPointer;

    cout << " count of firstSharedPointer after sharing" << firstSharedPointer.use_count() << endl;

    if (auto temp = weakPointer.lock())
    {
        temp->use();
    }
    else
    {
        cout << " resource Destroyed\n";
    }
}

void ResourceManager::PrintResources()
{
    for (const auto &resource : resources)
    {
        cout << "------------------------Resource - " << resource.first << endl;
    }
}

void ResourceManager::Worker(const string &name)
{
    auto RM = getResource(name);
    RM->use();
}