# CMakeList.txt: CMakeAudioTransform 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
project(AudioSerialize)

#设置库文件路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#设置可执行程序路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#安装目录
if(WIN32)
	set(INSTALL_PATH_LIB $ENV{HOME}/${PROJECT_NAME}/lib)
	set(INSTALL_PATH_INCLUDE $ENV{HOME}/${PROJECT_NAME}/include)
	set(INSTALL_PATH_BIN $ENV{HOME}/${PROJECT_NAME}/bin)
endif()

#打印库文件
message(STATUS "将链接依赖库:${LINK_LIB_LIST}")
#使能c++11
set(CMAKE_CXX_STANDARD 11)

aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library (${PROJECT_NAME}_static STATIC ${DIR_LIB_SRCS})
# 生成动态库
add_library (${PROJECT_NAME}_shared SHARED ${DIR_LIB_SRCS})
#安装静态库至系统目录
install(TARGETS ${PROJECT_NAME}_shared DESTINATION ${INSTALL_PATH_BIN})

install(FILES "./common.h" DESTINATION ${INSTALL_PATH_INCLUDE})
install(FILES "./PcmSerializeApi.h" DESTINATION ${INSTALL_PATH_INCLUDE})