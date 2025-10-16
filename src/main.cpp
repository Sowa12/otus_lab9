#include <async.h>

int main()
{
    auto bulk = async::connect(3);
    
    char buf[] = "cmd1\ncmd2\ncmd3\n{\ncmd4\ncmd5\n}\n{\ncmd6\n{\ncmd7\n}\n{\ncmd8\n}\n}\n";

    async::receive(bulk, buf, sizeof(buf));

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}