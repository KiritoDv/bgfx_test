#include <iostream>
#include <functional>

template <typename ... T> using Lambda = std::function<void(T...)>;

using namespace std;
class Core {
    public:
        static void init(Lambda<> init, Lambda<> update);
};
