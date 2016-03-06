#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm> 

const uint64_t num_loops = 20000000;

template<typename TimeT = std::chrono::microseconds>
struct measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F&& func, Args&&... args)
    {
        auto start = std::chrono::system_clock::now();
        std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast< TimeT>
            (std::chrono::system_clock::now() - start);
        return duration.count();
    }
};


inline void myfunction(int& i) {  // function:
    i = 20;
}

void foo_n() {
    std::vector<int> container(num_loops, 0);
    for (uint64_t i = 0; i<num_loops; ++i) {
        myfunction(container[i]);
    }
}

void reverse_foo_n() {
    std::vector<int> container(num_loops, 0);
    for (uint64_t i = num_loops; i > 0;) {
        myfunction(container[--i]);
    }
}

void it_foo_n() {
    std::vector<int> container(num_loops, 0);
    auto it = container.begin();
    do {
        myfunction(*it);
        ++it;
    } while (it != container.end());

}

void reverse_it_foo_n() {
    std::vector<int> container(num_loops, 0);
    auto it = container.end();
    do {
        --it;
        myfunction(*it);
    } while (it != container.begin());

}

void foo_log_n() {
    std::vector<int> container(num_loops, 0);
    for (uint64_t i = container.size()-1; i>=0; i /= 2) {
        for (uint64_t j = i; j>i / 2; --j) {
            myfunction(container[j]);
        }
    }
}

void reverse_it_foo_log_n() {
    std::vector<int> container(num_loops, 0);

    auto it_x = container.end();
    do {
        auto dist  = std::distance(container.begin(), it_x) / 2;
    
        dist = dist == 0 ? 1 : dist;

        it_x -= dist;

        for (auto it_y = it_x; it_y < it_x + dist; ++it_y) {
            *it_y = 20;
        }


    } while (it_x != container.begin());

}

void std_foreach() {
    std::vector<int> container(num_loops, 0);
    std::for_each(container.begin(), container.end(), myfunction);
}

void for_each(){
    std::vector<int> container(num_loops, 0);
    for(int &num : container)
        myfunction(num);
}

int main() {
    std::cout << "foo_n                " << measure<>::execution(foo_n) << std::endl;
    std::cout << "it_foo_n             " << measure<>::execution(it_foo_n) << std::endl;
    std::cout << "reverse_it_foo_n     " << measure<>::execution(reverse_it_foo_n) << std::endl;
    std::cout << "reverse_foo_n        " << measure<>::execution(reverse_foo_n) << std::endl;
    std::cout << "foo_log_n            " << measure<>::execution(foo_log_n) << std::endl;
    std::cout << "reverse_it_foo_log_n " << measure<>::execution(reverse_it_foo_log_n) << std::endl;
    std::cout << "std_for_each         " << measure<>::execution(std_foreach) << std::endl;
    std::cout << "for_each             " << measure<>::execution(for_each) << std::endl;
}
