#include <iostream>

using namespace std;

class person {
public:
    explicit person(std::string name = "", int age = 0) :
            name_(std::move(name)), age_(age) {
        std::cout << "Init a person!" << std::endl;
    }

    ~person() {
        std::cout << "Destroy a person!" << std::endl;
    }

private:
    [[maybe_unused]] const std::string name_;
    [[maybe_unused]] int age_;
};

void testPerson() {
    person p;
}

int main() {
    testPerson();
    return 0;
}
