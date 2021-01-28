## 使用CMake生成动态链接库DLL

### **项目说明**

项目使用cmake构建，通常情况下，DLL都是以lib库的形式编写的，所以我们使用cmake以类似于子项目的形式创建dll库，并构建整个项目；

整个项目的结构如下：

```bash
.
│  CMakeLists.txt
│  run_dll.cpp
│
└─lib
        CMakeLists.txt
        my_dll.cpp
        my_dll.h
```

其中，根目录下放置了`CMakeLists.txt`，用于声明整个项目；

而`run_dll.cpp`为最终生成DLL库的加载测试代码，这里可以暂时忽略；

`lib`目录下就是生成DLL库的代码；

在这个简单的项目中，我们会在C++代码中创建一个`add`函数，用于实现两个数字相加，并返回结果；

生成DLL库，以供其他代码调用；

### **项目使用**

#### **编译DLL**

在根目录先使用`cmake .`命令，在根目录和lib目录下编译出Makefile文件；

然后在根目录或者lib目录下使用`make install`即可编译出DLL库；

编译出的DLL库位于根目录的`lib_out`目录下，名称为：`my_dll.dll`；

和我们在cmake中配置的完全相同；

<br/>

#### **测试DLL**

为了测试生成的DLL能否正常运行，我们需要编写代码并加载测试生成的DLL是否可以正常被调用；

在根目录下创建`run_dll.cpp`：

run_dll.cpp

```cpp
#include <windows.h>
#include <iostream>

typedef int (*add)(int, int);

int main() {
    HINSTANCE handle = LoadLibrary("./lib_out/my_dll.dll");
    auto f = (add) GetProcAddress(handle, "add");
    std::cout << f(1, 32) << std::endl;
    FreeLibrary(handle);
    return 0;
}
```

在run_dll.cpp中，我们首先动态加载了生成的DLL库，随后获取到了`add`方法，最后调用并输出了求和结果；

编写完成后，还要在根目录中的`CMakeLists.txt`中添加编译可执行文件的声明：

```diff
cmake_minimum_required(VERSION 3.16)
project(dll_learn)

set(CMAKE_CXX_STANDARD 20)

ADD_SUBDIRECTORY(lib)

+ add_executable(run_dll run_dll.cpp)
```

然后重新执行`cmake .`和`make install`编译项目；

这时会在项目根目录生成`run_dll.exe`；

运行`run_dll.exe`，可以生成结果：

```bash
$ run_dll.exe
33
```

测试成功！

>   关于其他编程语言加载DLL库，见：
>
>   -   [各编程语言加载并调用dll库](/2021/01/28/各编程语言加载并调用dll库/)

### 其他编程语言测试

#### **Golang调用DLL**

Golang在`syscall`中已经提供了系统调用相关的API，我们可以直接使用这个包完成；

代码如下：

demo/run_dll.go

```go
package main

import (
	"fmt"
	"syscall"
)

var (
	dll     = syscall.NewLazyDLL("../lib_out/my_dll.dll")
	addFunc = dll.NewProc("add")
)

func main() {
	ret1, ret2, err := addFunc.Call(123, 22)
	fmt.Println(ret1, ret2, err)
}
```

上面的代码通过`syscall.NewLazyDLL`懒加载了DLL；

随后通过`dll.NewProc`获取到了`add`函数；

最后通过`addFunc.Call`调用了函数，并打印了结果；

运行并获取结果：

```bash
$ go run run_dll.go
145 123 The operation completed successfully.
```

在调用`Call`时，需要注意；下面是Go中Call源码的注释：

```go
// Call executes procedure p with arguments a. It will panic if more than 18 arguments
// are supplied.
//
// The returned error is always non-nil, constructed from the result of GetLastError.
// Callers must inspect the primary return value to decide whether an error occurred
// (according to the semantics of the specific function being called) before consulting
// the error. The error always has type syscall.Errno.
//
// On amd64, Call can pass and return floating-point values. To pass
// an argument x with C type "float", use
// uintptr(math.Float32bits(x)). To pass an argument with C type
// "double", use uintptr(math.Float64bits(x)). Floating-point return
// values are returned in r2. The return value for C type "float" is
// math.Float32frombits(uint32(r2)). For C type "double", it is
// math.Float64frombits(uint64(r2)).
func (p *Proc) Call(a ...uintptr) (r1, r2 uintptr, lastErr error) {
	switch len(a) {
	case 0:
		return Syscall(p.Addr(), uintptr(len(a)), 0, 0, 0)
	case 1:
		return Syscall(p.Addr(), uintptr(len(a)), a[0], 0, 0)
	……
	default:
		panic("Call " + p.Name + " with too many arguments " + itoa(len(a)) + ".")
	}
}
```

首先，调用的参数个数不得多于18个；

其次，<font color="#f00">**返回的err一定不为空（如上面输出的：`The operation completed successfully.`），而调用者需要判断第一个返回值是否符合调用逻辑来判断是否调用成功！**</font>

随后就是，在调用时传参为浮点数时的处理；

#### **Python调用DLL**

在Python中调用DLL需要引入`ctypes`库；

随后，直接使用`CDLL`引入DLL库即可使用！

代码如下：

demo/run_dll.py

```python
import ctypes

dll = ctypes.CDLL("../lib_out/my_dll.dll")
a = dll.add(1, 2)
print(a)
```

运行代码并输出结果：

```bash
$ python run_dll.py
3
```

#### **Java调用DLL**

看了这么多概念性的东西，接下来我们看一下如何在Java中调用DLL库；

创建一个Maven工程，修改`pom.xml`，加入jna依赖：

```xml
<dependencies>
    <dependency>
        <groupId>net.java.dev.jna</groupId>
        <artifactId>jna</artifactId>
        <version>5.6.0</version>
    </dependency>
</dependencies>
```

编写JNA接口：

src/main/java/io.github.jasonkayzk/java/Add.java

```java
package io.github.jasonkayzk.java;

import com.sun.jna.Library;
import com.sun.jna.Native;

/**
 * 测试JNA调用DLL的接口
 */
public interface Add extends Library {
    /**
     * 根据C提供的接口构造的接口
     */
    int add(int x, int y);

    /**
     * 需要将dll或so件放入Java运行目录
     */
    Add LIBRARY = Native.load("my_dll.dll", Add.class);
}
```

启动类：

src/main/java/io.github.jasonkayzk/java/DllRun.java

```java
package io.github.jasonkayzk.java;

public class DllRun {
    public static void main(String[] args) {
        int res = Add.LIBRARY.add(12, 20);
        System.out.println(res);
    }
}
```

<font color="#f00">**并在resources目录下放入编译好的`my_dll.dll`文件；**</font>

代码说明：

上面的Add接口声明了一个与DLL库中`add`函数对应的接口，并在接口中声明了一个Add接口类型的静态常量LIBRARY：LIBRARY使用`Native.load`方法加载了DLL库；

在DllRun启动类中，使用Add中定义并加载了DLL的常量调用add方法，完成调用！

>   <font color="#f00">**从上面的代码可以看出来，JNA的解决方案相当优雅：通过接口声明代替了头文件，并且直接通过一个函数加载即可像调用Java方法一样调用本地代码！**</font>

<br/>

#### **Kotlin调用DLL**

由于Kotlin和Java同属于JVM语言，所以，Java能够实现的，Kotlin当然也能够实现！

而且由于Kotlin更加简洁的语法，和语言抽象能力，所以DLL在Kotlin中使用更加简单；

在上面的Maven项目之上，我们添加Kotlin的插件，修改`pom.xml`：

```xml
<properties>
    <kotlin.version>1.4.30-RC</kotlin.version>
</properties>

<dependencies>
    <dependency>
        <groupId>net.java.dev.jna</groupId>
        <artifactId>jna</artifactId>
        <version>5.6.0</version>
    </dependency>
    <dependency>
        <groupId>org.jetbrains.kotlin</groupId>
        <artifactId>kotlin-stdlib-jdk8</artifactId>
        <version>${kotlin.version}</version>
    </dependency>
    <dependency>
        <groupId>org.jetbrains.kotlin</groupId>
        <artifactId>kotlin-test</artifactId>
        <version>${kotlin.version}</version>
        <scope>test</scope>
    </dependency>
</dependencies>

<build>
    <plugins>
        <plugin>
            <groupId>org.jetbrains.kotlin</groupId>
            <artifactId>kotlin-maven-plugin</artifactId>
            <version>${kotlin.version}</version>
            <executions>
                <execution>
                    <id>compile</id>
                    <phase>compile</phase>
                    <goals>
                        <goal>compile</goal>
                    </goals>
                </execution>
                <execution>
                    <id>test-compile</id>
                    <phase>test-compile</phase>
                    <goals>
                        <goal>test-compile</goal>
                    </goals>
                </execution>
            </executions>
            <configuration>
                <jvmTarget>1.8</jvmTarget>
            </configuration>
        </plugin>
        <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-compiler-plugin</artifactId>
            <executions>
                <execution>
                    <id>compile</id>
                    <phase>compile</phase>
                    <goals>
                        <goal>compile</goal>
                    </goals>
                </execution>
                <execution>
                    <id>testCompile</id>
                    <phase>test-compile</phase>
                    <goals>
                        <goal>testCompile</goal>
                    </goals>
                </execution>
            </executions>
        </plugin>
    </plugins>
</build>
```

编写在Kotlin中加载和调用DLL的代码：

Add接口：

src/main/java/io.github.jasonkayzk/kotlin/Add.kt

```kotlin
package io.github.jasonkayzk.kotlin

import com.sun.jna.Library
import com.sun.jna.Native

interface Add : Library {

    fun add(x: Int, y: Int): Int

    companion object {
        // 懒加载的方式
        val LIBRARY by lazy { Native.load("my_dll.dll", Add::class.java) as Add }
    }
}
```

调用逻辑：

src/main/java/io.github.jasonkayzk/kotlin/DllRun.kt

```kotlin
package io.github.jasonkayzk.kotlin

fun main() {
    val res = Add.LIBRARY.add(10, 20)
    println(res)
    println(res)
}
```

和Java类似，在Kotlin中，我们在Add接口中定义了和DLL对应的add方法，并且定义了一个单例类，以懒加载的方式加载了DLL库；

在main函数中，我们直接使用接口调用了函数，使用起来也是相当简洁！

#### **JS调用DLL**

在JS中调用DLL的坑比较多；

主要的实现方式有两种：

-   使用C++编写C++ Addons；
-   使用`ffi`库，而ffi库底层使用了编译套件：node-gyp + 各个操作系统的编译环境；

由于配置开发环境较为麻烦，这里不做演示了；

关于使用C++编写C++ Addons，可以Node参考官方文档：

-   https://nodejs.org/api/addons.html

关于`ffi`库，可以参考：

-   https://github.com/node-ffi/node-ffi
-   https://github.com/nodejs/node-gyp#installation

### 其他

系列文章：

-   [cmake生成动态链接库dll](/2021/01/27/cmake生成动态链接库dll/)
-   [各编程语言加载并调用dll库](/2021/01/28/各编程语言加载并调用dll库/)

