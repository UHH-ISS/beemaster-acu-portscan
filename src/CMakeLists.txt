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

# Executable definition
add_executable(acu-impl ${SOURCE_FILES})
target_link_libraries(acu-impl ${LINK_LIBS})
