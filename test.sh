# Use RVO
g++ rvo.cc -o rvo --std=c++11 && ./rvo

# No RVO
g++ rvo.cc -o rvo --std=c++11 -fno-elide-constructors && ./rvo

# Use NRVO
g++ nrvo.cc -o nrvo --std=c++11 && ./nrvo

# No NRVO
g++ nrvo.cc -o nrvo --std=c++11 -fno-elide-constructors && ./nrvo
