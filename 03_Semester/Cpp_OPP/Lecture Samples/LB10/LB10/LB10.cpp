#include <algorithm>
#include "TemplateBasics.h"
#include "MyArray.h"

int main() {
#pragma region Template Basics
    std::vector<int> vec1{};
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    std::vector<char> vec2{};
    vec2.push_back('a');
    vec2.push_back('b');
    vec2.push_back('c');

    // C-Way
    int res11 = intAdd(5, 7);
    float res12 = floatAdd(5, 7);
    std::string res13 = stringAdd("Hello", "World");

    // Operator overloading
    int res21 = Add(5, 7);
    float res22 = Add(5.5f, 7.3f);
    std::string res23 = Add("Hello", "World");
    // auto res24 = Add(4, 3.3f); // Ambiguity

    // Using templates
    MyClass<int> c1{};
    MyClass<char> c2{};
    int res31 = TAdd<int>(5, 7);
    float res32 = TAdd(5.5f, 7.3f);
    std::string res33 = TAdd<std::string>("Hello", "World");

    // Multiplication function template
    int res41 = TMulti<int>(5, 7);
    float res42 = TMulti(5.5f, 7.3f);
    std::string res43 = TMulti<std::string>("Hello", "World");
#pragma endregion

    MyArray<char, 10> arr = MyArray<char, 10>('a', 'b', 'z');

    // Labdas
    std::cout << Add(10, 20) << std::endl;

    std::cout << [](int a, int b) -> int {
        return a + b;
    }(10, 20) << std::endl;

    std::vector<int> vec{ -1, 33, 2, 5, 5, -2, 6 };
    std::sort(vec.begin(), vec.end(), [](int a, int b) {
        if (a <= b)
            return false;
        else
            return true;
    });

    auto lambda = [](int toIncrement) {
        return ++toIncrement;
    };

    int i = 0;
    i = lambda(i);
    i = lambda(i);
    i = lambda(i);
    i = lambda(i);
    i = lambda(i);

    return 0;
}