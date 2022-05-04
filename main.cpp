#include <iostream>
#include <vector>
#include <unordered_map>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>
#include <fmt/os.h>
#include <fmt/color.h>


void simple_print() {
    fmt::print("Hello, {}\n", "world!");
}

void string_format() {
    std::string s = fmt::format("The answer is {}.", 42);
    fmt::print("{}\n", s);
}

void float_format() {
    fmt::print("The answer is {:.2f}\n", 1.12345678);
}

void position_param() {
    fmt::print("I'd rather be {1} than {0}.\n", "right", "happy");
}

void named_param() {
    fmt::print("Hello, {name}! The answer is {number}. Goodbye, {name}.\n",
               fmt::arg("name", "World"), fmt::arg("number", 42));
}

void suffix_named_param() {
    // #include <fmt/format.h> needed
    using namespace fmt::literals;
    fmt::print("Hello, {name}! The answer is {number}. Goodbye, {name}.\n",
               "name"_a = "World", "number"_a = 22);
}

void time_format() {
    // #include <fmt/chrono.h> needed
    using namespace std::literals::chrono_literals;
    fmt::print("Default format: {} {}\n", 42s, 100ms);
    fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);
}

void collection_format() {
    // #include <fmt/ranges.h> needed
    std::vector<int> v = {1, 2, 3};
    fmt::print("v: {}\n", v);

    std::unordered_map<std::string, int> m{{"a", 1},
                                           {"b", 2}};
    fmt::print("m: {}\n", m);
}

void format_to_file() {
    // #include <fmt/os.h> needed
    auto out = fmt::output_file("test.txt");
    out.print("Don't {}", "Panic");
}

void font_format() {
    // #include <fmt/color.h> needed
    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
               "Hello, {}!\n", "world");
    fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
               fmt::emphasis::underline, "Hello, {}!\n", "мир");
    fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
               "Hello, {}!\n", "世界");
}

int main() {

    simple_print();

    string_format();

    float_format();

    position_param();

    named_param();

    suffix_named_param();

    time_format();

    collection_format();

    format_to_file();

    font_format();

    return 0;
}
