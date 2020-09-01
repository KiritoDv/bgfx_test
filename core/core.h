#include <iostream>
#include <functional>

using namespace std;
class Core {
    public:
        static void init(function<void()> init, function<void()> update);
};
