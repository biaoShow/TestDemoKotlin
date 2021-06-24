# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
#常量说明
#PROJECT_NAME	project命令中写的项目名
#CMAKE_VERSION	当前使用CMake的版本
#CMAKE_SOURCE_DIR	工程顶层目录，即入口CMakeLists文件所在路径
#PROJECT_SOURCE_DIR	同CMAKE_SOURCE_DIR
#CMAKE_BINARY_DIR	工程编译发生的目录，即执行cmake命令进行项目配置的目录，一般为build
#PROJECT_BINARY_DIR	同CMAKE_BINARY_DIR
#CMAKE_CURRENT_SOURCE_DIR	当前处理的CMakeLists.txt所在的路径
#CMAKE_CURRRENT_BINARY_DIR	当前处理的CMakeLists.txt中生成目标文件所在编译目录
#CMAKE_CURRENT_LIST_FILE	输出调用这个变量的CMakeLists.txt文件的完整路径
#CMAKE_CURRENT_LIST_DIR	当前处理的CMakeLists.txt文件所在目录的路径
#CMAKE_INSTALL_PREFIX	指定make install命令执行时包安装路径
#CMAKE_MODULE_PATH	find_package命令搜索包路径之一，默认为空

#指定cmake最小版本
cmake_minimum_required(VERSION 3.4.1)
#设置生成的so动态库最后输出的路径

#后去指定目录的源文件保存在NLUlib_src变量中
aux_source_directory(${CMAKE_SOURCE_DIR}/src/main/jni writelib_src)
#依赖的头文件
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/main/jni)

#include_directories(ncnn)
#
add_library(write SHARED ${writelib_src})

#依赖的add库
#add_library(dm_tts_en SHARED IMPORTED)
#set_target_properties(dm_tts_en
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jni/libs/${ANDROID_ABI}/libdm_tts_en.so)

##依赖的add库
#add_library(ncnn SHARED IMPORTED)
#set_target_properties(ncnn
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jni/libs/${ANDROID_ABI}/libncnn.so)

find_library( # log库的别名
        log-lib
        #log库
        log)

#链接代码到指定的库
target_link_libraries( # Specifies the target library.
        write
#        dm_tts_en
#        ncnn
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})