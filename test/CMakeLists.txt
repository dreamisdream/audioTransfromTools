cmake_minimum_required(VERSION 3.12)

project(audioTest)

set(LIB_NAME AudioSerialize)

include_directories($ENV{HOME}/${LIB_NAME}/include)

add_executable(audioTest testAudioDll.cpp)

target_link_libraries(audioTest AudioSerialize_shared)