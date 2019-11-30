SET(utils_source log.cpp csv.cpp)

#SET(third_party_libs
        #${CMAKE_SOURCE_DIR}/thirdParty/boost_1_70_0/stage/lib/libboost_program_options.a
        #${CMAKE_SOURCE_DIR}/thirdParty/boost_1_70_0/stage/lib/libboost_thread.a
        #${CMAKE_SOURCE_DIR}/thirdParty/json/libjsoncpp.a)

ADD_LIBRARY(utils ${utils_source})
