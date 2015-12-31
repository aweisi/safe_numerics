#include <iostream>
#include <cassert>
#include <limits>

#include "../include/utility.hpp"
#include "../include/safe_range.hpp"

template<typename T>
void display_log(T Max){
    std::cout
        << "log(" << Max << ") = "
        << boost::numeric::log(Max) << std::endl;
}

bool test_log(){
    using namespace boost::numeric;
    assert(log(127u) == 7); // 7 bits
    assert(log(127u) == 7); // 7 bits
    assert(log(128u) == 8); // 8 bits
    assert(log(129u) == 8); // 8 bits
    assert(log(255u) == 8); // 8 bits
    assert(log(256u) == 9); // 9 bits

    assert(log(127) == 8); // 7 bits + 1 sign bit
    assert(log(128) == 9); // 8 bits + 1 sign bit
    assert(log(129) == 9); // 8 bits + 1 sign bit
    assert(log(255) == 9); // 8 bits + 1 sign bit
    assert(log(256) == 10); // 9 bits + 1 sign bit

    assert(log(-127) == 8); // 7 bits + 1 sign bit
    assert(log(-128) == 8); // 7 bits + 1 sign bit
    assert(log(-129) == 9); // 8 bits + 1 sign bit
    assert(log(-255) == 9); // 8 bits + 1 sign bit
    assert(log(-256) == 9); // 8 bits + 1 sign bit
    return true;
}

bool test1(){
    using namespace boost::numeric;
    typedef signed_stored_type<-256, 254> t1;

    safe_signed_range<-128, 127> s1(1);
    safe_signed_range<-256, 254> s2(2);

    typedef safe_unsigned_range<0u, 1000u> t2;
    static_assert(
        std::numeric_limits<t2>::is_signed == false,
        "this range should be unsigned"
    );

    //typedef ::print_type<t2>::type p_t2;

    return true;
}

#include "../include/automatic.hpp"

template <
    std::intmax_t Min,
    std::intmax_t Max
>
using safe_t = boost::numeric::safe_signed_range<
    Min,
    Max,
    boost::numeric::automatic,
    boost::numeric::throw_exception
>;

bool test2(){
    std::cout << "test1" << std::endl;
    try{
        constexpr const safe_t<-64, 63> x(1);
        safe_t<-64, 63> y;
        y = 2;
        std::cout << "x = " << x << std::endl;
        std::cout << "y = " << y << std::endl;
        auto z = x + y;
        std::cout << "x + y = ["
            << std::numeric_limits<decltype(z)>::min() << ","
            << std::numeric_limits<decltype(z)>::max() << "] = "
            << z << std::endl;

        auto z2 = x - y;
        std::cout << "x - y = ["
            << std::numeric_limits<decltype(z2)>::min() << ","
            << std::numeric_limits<decltype(z2)>::max() << "] = "
            << z2 << std::endl;

            short int yi, zi;
            yi = y;
            zi = x + yi;
    }
    catch(std::exception e){
        // none of the above should trap. Mark failure if they do
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

int main(){
    //using namespace boost::numeric;
    //safe_signed_literal2<100> one_hundred;
    //one_hundred = 200;

    return (
        test_log() &&
        test1() &&
        test2() /* &&
        test3() &&
        test4()
        */
    ) ? EXIT_SUCCESS : EXIT_FAILURE;
}
