#include <iostream>

class Core {
    public:
        static void init(void (*init)(), void (*update)());
};
