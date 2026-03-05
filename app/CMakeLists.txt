file(GLOB_RECURSE APP_SOURCES src/*.cpp)
add_executable(RaytraceApp ${APP_SOURCES})
target_include_directories(RaytraceApp PRIVATE include/ libraries/raylib/include/)

if (WIN32)
    target_link_directories(RaytraceApp PRIVATE libraries/raylib/x64)
    target_link_libraries(RaytraceApp PRIVATE raylibdll)
    add_custom_command(TARGET RaytraceApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/libraries/raylib/x64/raylib.dll
            $<TARGET_FILE_DIR:RaytraceApp>
    )

elseif (APPLE)
    target_link_directories(RaytraceApp PRIVATE libraries/raylib/osx)
    target_link_libraries(RaytraceApp PRIVATE raylib)
    add_custom_command(TARGET RaytraceApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/libraries/raylib/osx/libraylib.dylib
            $<TARGET_FILE_DIR:RaytraceApp>
    )
    # Ensure the executable can find the dylib at runtime
    set_target_properties(RaytraceApp PROPERTIES
        BUILD_RPATH "@executable_path"
        INSTALL_RPATH "@executable_path"
    )
endif()
