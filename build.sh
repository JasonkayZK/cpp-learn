# build
mkdir -p cmake/build
cd cmake/build
cmake ../..
make -j

# test
./greeter_server

./greeter_client

# print out: Greeter received: Hello world
