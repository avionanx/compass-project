
#include <iostream>
#include "app.h"
#include <chrono>
template <
    class result_t = std::chrono::milliseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}
int main()
{
    auto start = std::chrono::steady_clock::now();
    

    try {
        App();
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
    }
    std::cout << "Elapsed(ms)=" << since(start).count() << std::endl;
}
