# Generate dynamic lib
g++ -std=c++11 -shared -fPIC ./lib/testlib.cc -o ./lib/testlib.so -I/usr/local/include -I. -I/Users/zk/.vcpkg-clion/vcpkg/packages/lua_arm64-osx/include -L/usr/local/lib -ldl
