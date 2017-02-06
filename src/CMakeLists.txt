# CMakeLists.txt for libacu

# Source files
set(SOURCE_FILES
        main.cc
        alert_mapper.cc
        config_parser.cc
        rocks_storage.cc
        portscan_aggregation.cc
        portscan_alert.cc
        portscan_correlation.cc
        tcp_alert.cc
        vector_storage.cc)

# Disable -Wununsed-parameter as broker::get produces this error even when used correctly (I think?!)
# TODO: Maybe scope this to the source files where broker::get is used? (Currently alert_mapper/tcp_alert)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

# Executable definition
add_executable(acu-impl ${SOURCE_FILES})
target_link_libraries(acu-impl ${LINK_LIBS})
