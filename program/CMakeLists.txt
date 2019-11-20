SET(program_source main.cpp)

#SET(third_party_libs
        #${CMAKE_SOURCE_DIR}/thirdParty/boost_1_70_0/stage/lib/libboost_program_options.a
        #${CMAKE_SOURCE_DIR}/thirdParty/boost_1_70_0/stage/lib/libboost_thread.a
        #${CMAKE_SOURCE_DIR}/thirdParty/json/libjsoncpp.a)

ADD_EXECUTABLE(main ${program_source})

TARGET_LINK_LIBRARIES(main pledge)
