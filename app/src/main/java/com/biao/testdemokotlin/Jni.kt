package com.biao.testdemokotlin

class Jni {
    companion object {
        init {
            System.loadLibrary("write")
        }

    }

    external fun write(path: String, text: String):Boolean
    external fun read(path: String):String
}