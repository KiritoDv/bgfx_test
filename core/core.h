#include <iostream>
#include <functional>

using namespace std;
class Core {
    public:
        static void init(std::function<void()> init, std::function<void()> update);
};
