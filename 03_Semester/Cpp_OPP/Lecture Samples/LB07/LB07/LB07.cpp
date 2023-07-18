#include "Problem.h"
#include "Solution.h"
#include "Abstract.h"

void Print(Worker& m) {
    m.print();
}

void Print(WorkerSolved& m) {
    m.print();
}

int main() {
    Worker w1;
    Manager m1;
    // Works as expected
    w1.print(); // Worker ...
    m1.print(); // Manager ...

    // Does not work as expected
    // Compile time Cast -> Only possible during Runtime to differentiate
    Print(w1); // Worker ...
    Print(m1); // Worker ...

    std::cout << "-----------------------" << std::endl;

    WorkerSolved w2;
    ManagerSolved m2;
    BigBossSolved b2;
    // Now all works as expected
    w2.print(); // Worker ...
    m2.print(); // Manager ...
    Print(w2); // Worker ...
    Print(m2); // Manager ...
    Print(b2); // Manager ...

    // Abstract a1; // Does not work due to it being an abstract class
    Concrete c1;
    // AbstractConcrete ac1; // Does not work due to it being an abstract class

    return 0;
}