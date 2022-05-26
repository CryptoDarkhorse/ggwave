if (GGWAVE_ALL_WARNINGS_3RD_PARTY)
    if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    else()
        # todo : windows
    endif()
endif()

set(TARGET imgui)
set(TARGET_SHARED imgui.shared)
set(TARGET_SDL2 imgui-sdl2)
set(TARGET_SDL2_SHARED imgui-sdl2.shared)

if (APPLE)
    set(ADDITIONAL_LIBRARIES "-framework Cocoa")
else (APPLE)
    unset(ADDITIONAL_LIBRARIES)
endif (APPLE)

add_library(${TARGET}
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_widgets.cpp
    )
add_library(${TARGET_SHARED} SHARED
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_widgets.cpp
    )

set_property(TARGET ${TARGET_SHARED} PROPERTY OUTPUT_NAME ${TARGET})

target_include_directories(${TARGET} INTERFACE
    .
    )
target_include_directories(${TARGET_SHARED} INTERFACE
    .
    )

target_include_directories(${TARGET} PRIVATE
    imgui
    )
target_include_directories(${TARGET_SHARED} PRIVATE
    imgui
    )

target_link_libraries(${TARGET} PRIVATE
    ${ADDITIONAL_LIBRARIES}
    )
target_link_libraries(${TARGET_SHARED} PRIVATE
    ${ADDITIONAL_LIBRARIES}
    )

if (MINGW)
    target_link_libraries(${TARGET} PUBLIC
        stdc++
        )
    target_link_libraries(${TARGET_SHARED} PUBLIC
        stdc++
        )
endif()

if (GGWAVE_SUPPORT_SDL2)
    if (MINGW)
        find_package(PkgConfig REQUIRED)
        pkg_search_module(SDL2 REQUIRED sdl2)

        add_library(${TARGET_SDL2}
            imgui/examples/libs/gl3w/GL/gl3w.c
            imgui-extra/imgui_impl.cpp
            imgui-extra/imgui_impl_sdl.cpp
            imgui-extra/imgui_impl_opengl3.cpp
            )
        add_library(${TARGET_SDL2_SHARED} SHARED
            imgui/examples/libs/gl3w/GL/gl3w.c
            imgui-extra/imgui_impl.cpp
            imgui-extra/imgui_impl_sdl.cpp
            imgui-extra/imgui_impl_opengl3.cpp
            )

		set_property(TARGET ${TARGET_SDL2_SHARED} PROPERTY OUTPUT_NAME ${TARGET_SDL2})

        target_include_directories(${TARGET_SDL2} PUBLIC
            imgui/examples/libs/gl3w
            ${SDL2_INCLUDE_DIRS}
            )
        target_include_directories(${TARGET_SDL2_SHARED} PUBLIC
            imgui/examples/libs/gl3w
            ${SDL2_INCLUDE_DIRS}
            )

        target_include_directories(${TARGET_SDL2} PRIVATE
            imgui
            imgui-extra
            )
        target_include_directories(${TARGET_SDL2_SHARED} PRIVATE
            imgui
            imgui-extra
            )

        target_link_libraries(${TARGET_SDL2} PUBLIC
            imgui
            opengl32
            ${SDL2_LIBRARIES}
            )
        target_link_libraries(${TARGET_SDL2_SHARED} PUBLIC
            imgui
            opengl32
            ${SDL2_LIBRARIES}
            )

        target_link_libraries(${TARGET_SDL2} PRIVATE
            ${CMAKE_DL_LIBS}
            ${CMAKE_THREAD_LIBS_INIT}
            ${ADDITIONAL_LIBRARIES}
            )
        target_link_libraries(${TARGET_SDL2_SHARED} PRIVATE
            ${CMAKE_DL_LIBS}
            ${CMAKE_THREAD_LIBS_INIT}
            ${ADDITIONAL_LIBRARIES}
            )
    elseif (EMSCRIPTEN)
        add_library(${TARGET_SDL2} SHARED
            imgui-extra/imgui_impl.cpp
            imgui-extra/imgui_impl_sdl.cpp
            imgui-extra/imgui_impl_opengl3.cpp
            )
        add_library(${TARGET_SDL2_SHARED}
            imgui-extra/imgui_impl.cpp
            imgui-extra/imgui_impl_sdl.cpp
            imgui-extra/imgui_impl_opengl3.cpp
            )

		set_property(TARGET ${TARGET_SDL2_SHARED} PROPERTY OUTPUT_NAME ${TARGET_SDL2})

        target_include_directories(${TARGET_SDL2} PRIVATE
            imgui
            imgui-extra
            )
        target_include_directories(${TARGET_SDL2_SHARED} PRIVATE
            imgui
            imgui-extra
            )

        target_link_libraries(${TARGET_SDL2} PUBLIC
            imgui
            )
        target_link_libraries(${TARGET_SDL2_SHARED} PUBLIC
            imgui
            )
    else()
        set(OpenGL_GL_PREFERENCE GLVND)
        find_package(OpenGL REQUIRED)

        add_library(${TARGET_SDL2}
            imgui/examples/libs/gl3w/GL/gl3w.c
            imgui-extra/imgui_impl.cpp
            imgui-extra/imgui_impl_sdl.cpp
            imgui-extra/imgui_impl_opengl3.cpp
            )
        add_library(${TARGET_SDL2_SHARED} SHARED
            imgui/examples/libs/gl3w/GL/gl3w.c
            imgui-extra/imgui_impl.cpp
            imgui-extra/imgui_impl_sdl.cpp
            imgui-extra/imgui_impl_opengl3.cpp
            )

		set_property(TARGET ${TARGET_SDL2_SHARED} PROPERTY OUTPUT_NAME ${TARGET_SDL2})

        # force GL3W loader
        target_compile_definitions(${TARGET_SDL2} PUBLIC
            IMGUI_IMPL_OPENGL_LOADER_GL3W=1
            )
        target_compile_definitions(${TARGET_SDL2_SHARED} PUBLIC
            IMGUI_IMPL_OPENGL_LOADER_GL3W=1
            )

        target_include_directories(${TARGET_SDL2} PUBLIC
            imgui/examples/libs/gl3w
            ${SDL2_INCLUDE_DIRS}
            )
        target_include_directories(${TARGET_SDL2_SHARED} PUBLIC
            imgui/examples/libs/gl3w
            ${SDL2_INCLUDE_DIRS}
            )

        target_include_directories(${TARGET_SDL2} PRIVATE
            imgui
            imgui-extra
            )
        target_include_directories(${TARGET_SDL2_SHARED} PRIVATE
            imgui
            imgui-extra
            )

        target_link_libraries(${TARGET_SDL2} PUBLIC
            imgui
            ${OPENGL_LIBRARIES}
            ${SDL2_LIBRARIES}
            )
        target_link_libraries(${TARGET_SDL2_SHARED} PUBLIC
            imgui
            ${OPENGL_LIBRARIES}
            ${SDL2_LIBRARIES}
            )

        target_link_libraries(${TARGET_SDL2} PRIVATE
            ${CMAKE_DL_LIBS}
            ${CMAKE_THREAD_LIBS_INIT}
            ${ADDITIONAL_LIBRARIES}
            )
        target_link_libraries(${TARGET_SDL2_SHARED} PRIVATE
            ${CMAKE_DL_LIBS}
            ${CMAKE_THREAD_LIBS_INIT}
            ${ADDITIONAL_LIBRARIES}
            )
    endif()
endif()

install(TARGETS ${TARGET}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
    )

if (GGWAVE_SUPPORT_SDL2)
    install(TARGETS ${TARGET_SDL2}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
        )
endif()
