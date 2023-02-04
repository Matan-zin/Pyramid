#ifndef __shared_data__h
#define __shared_data__h

#include <mutex>

class SharedData 
{
public:

    SharedData(int max) : max_index(max) {};

    inline int get_index() {
        std::lock_guard<std::mutex> guard (mtx);

        return index;
    }

    inline void set_index(int v) {
        std::lock_guard<std::mutex> guard(mtx);

        index = v;
    }

private:
    int max_index;
    int index = 0;
    std::mutex mtx;
};

#endif