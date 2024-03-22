# **简单的内存分配器实现**

It implements [malloc()](http://man7.org/linux/man-pages/man3/free.3.html), [calloc()](http://man7.org/linux/man-pages/man3/free.3.html), [realloc()](http://man7.org/linux/man-pages/man3/free.3.html) and [free()](http://man7.org/linux/man-pages/man3/free.3.html).

文章：

- [《【译】实现一个简单的内存分配器》](https://jasonkayzk.github.io/2024/03/22/【译】实现一个简单的内存分配器/)

<br/>

## **How to use**

Compile:

```
gcc -o memalloc.so -fPIC -shared memalloc.c
```

`-fPIC` 和 `-shared` 选项确保编译后的输出具有位置相关代码，并告诉链接器生成适合动态链接的共享对象；

在Linux上，如果将环境变量 `LD_PRELOAD` 设置为共享对象的路径，则该文件将在任何其他库之前加载；

我们可以使用此技巧来加载我们的动态链接文件，以便在 Shell 中运行的命令将使用我们的内存分配函数：

```
export LD_PRELOAD=$PWD/memalloc.so
```

此时再执行命令，将会使用我们的内存分配函数：

```
ls
memalloc.c		memalloc.so		README.md
```

一旦完成了实验，可以执行 `unset LD_PRELOAD` 来停止使用我们的分配器；

<br/>

## **Reference**

- https://github.com/arjun024/memalloc/tree/master
