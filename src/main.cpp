#include <async.h>


void TestThread(const size_t bulkSize, const std::string& commandLine)
{
    auto bulk = async::connect(bulkSize);
    
    async::receive(bulk, commandLine.c_str(), commandLine.size());
}

const std::string HELP = 
R"(async_bin <bulk_size>
bulk_size - size for a static command
)";

int main(int argc, char** argv)
{
    // std::vector<std::pair<int, std::string>> commands;
    std::vector<std::thread> threads;

    // commands.push_back({3, "cmd1\ncmd2\ncmd3\n{\ncmd4\ncmd5\n}\n{\ncmd6\n{\ncmd7\n}\n{\ncmd8\n}\n}\n"});
    // commands.push_back({2, "cmd1\ncmd2\ncmd3\ncmd4\ncmd5\ncmd6"});
    // commands.push_back({3, "cmd1\ncmd2\ncmd3\n{\ncmd4\ncmd5\n}\n{\ncmd6\n{\ncmd7\n}\n{\ncmd8\n}\n}\ncmd1\ncmd2\ncmd3\n{\ncmd4\ncmd5\n}\n{\ncmd6\n{\ncmd7\n}\n{\ncmd8\n}\n}\n"});

    // for (auto& item : commands)
    // {
    //     threads.push_back(std::thread(TestThread, item.first, item.second));
    // }


    // for (auto& thread : threads)
    // {
    //     if (thread.joinable()) thread.join();
    // }


    if (argc < 2)
    {
        std::cout << HELP << std::endl;
        return EXIT_SUCCESS;
    } else {
        try
        {
            uint32_t bsize = std::stoi(argv[1]);
            std::string commandLine;
            auto bulk = async::connect(bsize);
            
            while(std::getline(std::cin, commandLine))
            {
                async::receive(bulk, commandLine.c_str(), commandLine.size());
            }

            async::disconnect(bulk);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}