cmake_minimum_required(VERSION 3.25)
project(TrabalhoPratico C)

set(CMAKE_C_STANDARD 99)

add_executable(TrabalhoPratico main.c Metro/Station.c Metro/Station.h Generic/String.c Generic/String.h Metro/FRoute.c Metro/FRoute.h Generic/DynamicArray.c Generic/DynamicArray.h AppManager.c AppManager.h Metro/MetroManager.c Metro/MetroManager.h Generic/LinkedList.c Generic/LinkedList.h)
