#include "Automat.h"
#include "Typumwandlung.h"

Automat foo(Automat a) {
    Automat a1("Puch", "167.168.0.12");
    return a1;
}

void getPoint(int w, int x = 3, int y = 4) {

}

int main() {
    auto a1 = Automat("Hallein", "192.168.0.12");
    auto a2 = a1;
    auto a3{ a1 };
    a2.GetServer()->SetIp("192.168.0.112");
    auto a4 = foo(a1);
    auto a5 = std::move(a1);

    getPoint(1, 2, 3);  // getPoint(1,2,3)
    getPoint(1, 2);     // getPoint(1,2,4)
    getPoint(1);        // getPoint(1,3,4)

    Typumwandlung t1 = 10;
    Typumwandlung t2 = { 10, "test" };
    Typumwandlung t3 = Typumwandlung(10, "test" );

    return 0;
}