import ctypes

dll = ctypes.CDLL("../lib_out/my_dll.dll")
a = dll.add(1, 2)
print(a)
