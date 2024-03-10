mkdir -p bin
gcc random_num.c -o ./bin/random_num

./bin/random_num
#25
#18
#89
#3
#70
#90
#87
#41
#47
#2

gcc -shared -fPIC unrandom.c -o bin/unrandom.so

LD_PRELOAD=$PWD/bin/unrandom.so ./bin/random_num
#42
#42
#42
#42
#42
#42
#42
#42
#42
#42
