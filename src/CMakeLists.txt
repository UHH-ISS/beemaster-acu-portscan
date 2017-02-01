# CMakeLists.txt for libacu

# Source files
set(SOURCE_FILES
        main.cc
        config_parser.cc
        rocks_storage.cc
        portscan_aggregation.cc
        portscan_correlation.cc
        tcp_event.cc)


# Executable definition
add_executable(acu-impl ${SOURCE_FILES})
target_link_libraries(acu-impl ${LINK_LIBS})
