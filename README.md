# **Boost Library Learn**

A branch to learn how to use [boost library](https://www.boost.org/)

## **Install**

First, download the compressed file, at:

- https://www.boost.org/users/download/

Then, extract the file:

```shell
tar -zxvf boost_1_78_0.tar.gz
```

Finally, install the boost library

```shell
cd boost_1_78_0
./bootstrap.sh
sudo ./b2 install
```

The, boost library is installed!

- header files: `/usr/local/include/boost`
- library files: `/usr/local/lib`

## **Boost Library Used Demo**

Modify `CMakeList.txt`:

```text
cmake_minimum_required(VERSION 3.21)

project(cpp_learn)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "/usr/local/include/boost")

include_directories(/usr/local/include) # header files searching path

link_directories(/usr/local/lib) # library files searching path

add_executable(cpp_learn main.cpp)
```

Modify `main.cpp` to use:

```C++
#include <iostream>
#include <boost/version.hpp>

int main() {
    std::cout << "Hello, Boost Library: " << BOOST_VERSION << std::endl;
    return 0;
}
```

Then print:

```text
Hello, Boost Library: 107800
```

# **Reference**

- https://www.boost.org/
