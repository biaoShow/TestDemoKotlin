package com.biao.testdemokotlin

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.os.Message
import android.util.Log
import android.view.View

class MainActivity : AppCompatActivity() {


    private val TAG: String = "MainActivity"
    private val LOCAL_DDR: String = "sdcard/Documents/c.txt"

    //    lateinit var handler: Handler
    lateinit var jni: Jni

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        jni = Jni()
//        test()
    }

//    private fun test() {
//        Thread {
//            Looper.prepare()
//            handler = object : Handler() {
//                override fun handleMessage(msg: Message) {
//                    super.handleMessage(msg)
//                    Log.e(TAG, "handleMessage")
//                }
//            }
//            Looper.loop()
//        }.start()
//    }

    fun test(view: View) {
//        handler.sendEmptyMessage(1001)
        jni.write(LOCAL_DDR, "hello ,my name is liyuanbiao!")
    }

    fun read(view: View) {
        val text: String = jni.read(LOCAL_DDR)
        Log.e(TAG, "text = $text")
    }
}