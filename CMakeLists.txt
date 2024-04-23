cmake_minimum_required(VERSION 3.27)
project(lobi_cPlus_learn)

set(CMAKE_CXX_STANDARD 20)

add_executable(lobi_cPlus_learn
        file_open_read_write_buff.cpp
        about_dup_dup2.cpp
        about_pipe_fork_easy.cpp)
