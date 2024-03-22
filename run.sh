# Compile dynamic lib
gcc -o memalloc.so -fPIC -shared memalloc.c

# Export LD_PRELOAD
export LD_PRELOAD=$PWD/memalloc.so

# Run command
ls

# Unset LD_PRELOAD
unset LD_PRELOAD
