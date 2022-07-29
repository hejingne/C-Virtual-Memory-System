cmake_minimum_required(VERSION 3.21)
project(a3_starter_files_hejingne C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(traceprogs)

add_executable(a3_starter_files_hejingne
        traceprogs/blocked.c
        traceprogs/marker.h
        traceprogs/matmul.c
        traceprogs/repeatloop.c
        traceprogs/simpleloop.c
        traceprogs/timer.h
        clock.c
        fifo.c
        lru.c
        mru.c
        pagetable.c
        pagetable.h
        rand.c
        sim.c
        sim.h
        swap.c
        swap.h)
