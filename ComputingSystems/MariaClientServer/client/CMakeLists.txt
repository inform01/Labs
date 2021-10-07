project(client)
cmake_minimum_required(VERSION 3.12)

set(PROJECT_SOURCES
        main.cpp
        client.cpp
        )

set(PROJECT_HEADERS
        client.h
        )

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})