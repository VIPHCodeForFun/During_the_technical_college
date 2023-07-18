#include <iostream>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <tuple>

template <typename T>
T square(T value) {
    return value * value;
}

template <typename T>
std::string square(std::string value) {
    throw std::exception("Squaring a string is not allowed");
}

template <typename T>
class sampleClass {
    T someValue;
};

class containerShow {
public:
    int var;
    containerShow(int var) : var{ var } {};
    containerShow(const containerShow& copy) : var{ copy.var } {
        std::cout << "In CCtor" << std::endl;
    }
};

struct DBEntries {
    int id;
    std::string name;
    float gehalt;
};

int main() {
#pragma region Templates Wh
    try {
        std::cout << square<float>(5.5) << std::endl;
        std::cout << square(7) << std::endl;
        std::cout << square<double>(-55) << std::endl;
        std::cout << square<std::string>("Hello World") << std::endl;
    }
    catch (std::exception& exc) {
        std::cerr << exc.what() << std::endl;
    }

    sampleClass<int> sc1;
    sampleClass<double> sc2;
    sampleClass<char> sc3;
#pragma endregion

#pragma region Sequentielle Container
    std::deque<containerShow> deque;
    deque.push_back(containerShow(5));
    deque.push_front(containerShow(10));
    deque.push_back(containerShow(-5));
    deque.push_front(containerShow(1));
    std::cout << deque[0].var << std::endl;

    std::list<containerShow> list;
    list.push_back(containerShow(5));
    list.push_front(containerShow(10));
    list.push_back(containerShow(-5));
    list.push_front(containerShow(1));
    for (auto it = list.begin(); it != list.end(); it++) {
        std::cout << (*it).var << std::endl;
    }
#pragma endregion

#pragma region Assoziative Container
    std::set<std::string> setOfStrings;
    setOfStrings.insert("Mars");
    setOfStrings.insert("Saturn");
    setOfStrings.insert("Saturn");
    setOfStrings.insert("Merkur");

    auto iterator = setOfStrings.find("Saturn");
    if (iterator == setOfStrings.end())
        std::cerr << "Not found: Saturn" << std::endl;

    iterator = setOfStrings.find("Venus");
    if (iterator == setOfStrings.end())
        std::cerr << "Not found: Venus" << std::endl;

    std::pair<int, std::string> p1{ 1, "Hello Pair" };

    std::map<char, std::string> mapOfPlanets;
    mapOfPlanets.insert(std::make_pair('0', "Merkur"));
    mapOfPlanets.insert(std::make_pair('1', "Venus"));
    mapOfPlanets.insert(std::make_pair('2', "Erde"));
    mapOfPlanets.insert(std::make_pair('3', "Mars"));
    auto v1 = mapOfPlanets['0'];
    auto v2 = mapOfPlanets['3'];
    for (auto& cval : mapOfPlanets) {
        std::cout << cval.first << ": " << cval.second << std::endl;
    }

    std::tuple<int, std::string, float> dbAcces1{4, "Musterfrau", 2800};
    std::cout << std::get<0>(dbAcces1) << " " << std::get<1>(dbAcces1) << " " << std::get<2>(dbAcces1) << std::endl;
    int id; std::string name; float gehalt;
    std::tie(id, name, gehalt) = dbAcces1;

    DBEntries dbAcces2{ 4, "Musterfrau", 2800 };
    std::cout << dbAcces2.id << " " << dbAcces2.name << " " << dbAcces2.gehalt << std::endl;
#pragma endregion

    []() -> void {}();
    return 0;
}