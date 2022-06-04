# Get init project help
xmake create --help

# Init project
xmake create -l c++ -P ./hello

# Build project
cd ./hello && xmake

# Run project
xmake r
# xmake run
# xmake run hello

# Debug project
xmake r -d
# xmake run -d
# xmake run -d hello
