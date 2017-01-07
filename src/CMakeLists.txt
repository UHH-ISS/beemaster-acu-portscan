# CMakeLists.txt for libacu

# Source files
set(SOURCE_FILES
        main.cc
        rocks_storage.cc)

# Executable definition
add_executable(acu-impl ${SOURCE_FILES})
target_link_libraries(acu-impl ${LINK_LIBS})
