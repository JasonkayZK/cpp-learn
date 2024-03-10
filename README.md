# **Hot reload**

C++ 几种热更新方式的总结：

- 动态链接库（DLL）：代码中加载动态库进行热更新
- 模块热替换（MHR）：借用lua c进行程序热更新
- 动态代码生成（JIT）：更改程序运行时的代码段实现热更新


# **Reference**

参考文章：

- [linux c/c++的4种热更新方法](https://juejin.cn/post/7110091118385037319)
- [Linux Preload Hook原理与实践](https://www.0xaa55.com/thread-25664-1-1.html)
- [使用LD_PRELOAD注入程序](https://www.cnblogs.com/sandeepin/p/ld-preload-inject.html)
- https://github.com/zhangyi1357/Notes/blob/main/hot-reload.md
- [Lua与C/C++交互——C/C++调用Lua脚本](https://www.cnblogs.com/DeeLMind/p/7655968.html)

