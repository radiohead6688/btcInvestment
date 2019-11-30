CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET(GSE_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
LIST(APPEND CMAKE_MODULE_PATH ${GSE_CMAKE_DIR})

SET(HUNTER_CONFIGURATION_TYPES Release CACHE STRING "Hunter configuration types")
SET(HUNTER_JOBS_NUMBER 4 CACHE STRING "Hunter jobs number")
SET(HUNTER_CACHE_SERVERS "https://github.com/ethereum/hunter-cache" CACHE STRING "Hunter cache servers")
SET(HUNTER_PASSWORDS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Hunter/passwords.cmake CACHE STRING "Hunter password path")

INCLUDE(HunterGate)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.21.16.tar.gz"
    SHA1 "aa1faccd24f33dd2c368f85a4e9ca2e5d9c249cb"
    LOCAL
)

# ----------------------- BTC Investment Project ----------------------- #
PROJECT(BTC_INVESTMENT)
SET(PROJECT_VERSION 1.0)

SET(CMAKE_CXX_STANDARD 11)

SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
hunter_add_package(Boost COMPONENTS program_options filesystem system thread context log)
FIND_PACKAGE(Boost CONFIG REQUIRED program_options filesystem system thread context log)
SET(BOOST_LIBS
    ${Boost_LOG_LIBRARY}
    ${Boost_LOG_SETUP_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_ATOMIC_LIBRARY}
    ${Boost_CONTEXT_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
)

INCLUDE_DIRECTORIES(
    ${Boost_INCLUDE_DIR}
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/program/include")
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/core/include")
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/mining/include")
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/utils/include")
)


ADD_SUBDIRECTORY(program)
ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(mining)
ADD_SUBDIRECTORY(utils)

TARGET_COMPILE_OPTIONS(main PUBLIC -g -O0)


#LINK_DIRECTORIES("${CMAKE_SOURCE_DIR}/thirdParty/boost_1_70_0/stage/lib/")

#AUX_SOURCE_DIRECTORY(. DIR_SRCS)
