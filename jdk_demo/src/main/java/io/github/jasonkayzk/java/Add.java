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
