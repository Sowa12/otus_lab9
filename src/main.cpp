#include <async.h>


void TestThread(const size_t bulkSize, const std::string& commandLine)
{
    auto bulk = async::connect(bulkSize);
    
    async::receive(bulk, commandLine.c_str(), commandLine.size());
}

int main()
{
    std::vector<std::pair<int, std::string>> commands;
    std::vector<std::thread> threads;

    commands.push_back({3, "cmd1\ncmd2\ncmd3\n{\ncmd4\ncmd5\n}\n{\ncmd6\n{\ncmd7\n}\n{\ncmd8\n}\n}\n"});
    commands.push_back({2, "cmd1\ncmd2\ncmd3\ncmd4\ncmd5\ncmd6"});
    commands.push_back({3, "cmd1\ncmd2\ncmd3\n{\ncmd4\ncmd5\n}\n{\ncmd6\n{\ncmd7\n}\n{\ncmd8\n}\n}\ncmd1\ncmd2\ncmd3\n{\ncmd4\ncmd5\n}\n{\ncmd6\n{\ncmd7\n}\n{\ncmd8\n}\n}\n"});

    for (auto& item : commands)
    {
        threads.push_back(std::thread(TestThread, item.first, item.second));
    }


    for (auto& thread : threads)
    {
        if (thread.joinable()) thread.join();
    }

    return 0;
}