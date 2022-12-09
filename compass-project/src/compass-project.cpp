#include <iostream>
#include "app.h"
#include <chrono> //time library to calculate runtime

template <
    class result_t = std::chrono::milliseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}
//return time
int main()
{
    auto start = std::chrono::steady_clock::now(); 
    

    try {
        App(); //main app
    }
    catch (std::runtime_error& e) {
        std::cout << e.what(); //throw error
    }
    std::cout << "Elapsed(ms)=" << since(start).count() << std::endl;
}
