SET(core_source strategy.cpp holding.cpp contract.cpp pledge.cpp)

#SET(third_party_libs
        #${CMAKE_SOURCE_DIR}/thirdParty/boost_1_70_0/stage/lib/libboost_program_options.a
        #${CMAKE_SOURCE_DIR}/thirdParty/boost_1_70_0/stage/lib/libboost_thread.a
        #${CMAKE_SOURCE_DIR}/thirdParty/json/libjsoncpp.a)

ADD_LIBRARY(core ${core_source})
