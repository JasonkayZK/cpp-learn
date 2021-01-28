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
