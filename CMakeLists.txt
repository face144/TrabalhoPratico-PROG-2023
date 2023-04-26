cmake_minimum_required(VERSION 3.25)
project(TrabalhoPratico C)

set(CMAKE_C_STANDARD 99)

add_executable(TrabalhoPratico main.c Metro/Station.c Metro/Station.h Metro/FRoute.c Metro/FRoute.h AppManager.c AppManager.h Metro/MetroManager.c Metro/MetroManager.h Metro/RouteList.c Metro/RouteList.h Metro/StationList.c Metro/StationList.h)
