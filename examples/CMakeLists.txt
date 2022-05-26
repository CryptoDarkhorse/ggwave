# dependencies

find_package(Threads REQUIRED)

if (GGWAVE_SUPPORT_SDL2)
    # SDL2

    if (EMSCRIPTEN)
        set(CMAKE_CXX_FLAGS " \
        -s USE_SDL=2 \
        -s DISABLE_EXCEPTION_CATCHING=0 \
        ")

        set(CMAKE_CXX_LINK_FLAGS " \
        --bind \
        -s TOTAL_MEMORY=67108864 \
        -s ASSERTIONS=1 \
        -s 'EXPORTED_RUNTIME_METHODS=[\"writeArrayToMemory\"]' \
        ")

        unset(SDL2_INCLUDE_DIRS)
        unset(SDL2_LIBRARIES)
    endif()

    if (NOT EMSCRIPTEN)
        find_package(SDL2)

        if (NOT USE_FINDSDL2 AND NOT SDL2_FOUND)
            message(WARNING "Unable to find SDL2 library. It is either not installed or CMake cannot find it."
                " In the latter case, setting the USE_FINDSDL2 variable might help:\n"
                "   $ cmake -D USE_FINDSDL2 .."
                )

            message(FATAL_ERROR "Aborting")
        endif()

        string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

        message(STATUS "SDL2_INCLUDE_DIRS = ${SDL2_INCLUDE_DIRS}")
        message(STATUS "SDL2_LIBRARIES = ${SDL2_LIBRARIES}")
    endif()
endif()

# third-party

add_subdirectory(third-party)

# helper libraries

set(TARGET ggwave-common)
set(TARGET_SHARED ggwave-common.shared)

add_library(${TARGET}
    ggwave-common.cpp
    )
add_library(${TARGET_SHARED} SHARED
    ggwave-common.cpp
    )

set_property(TARGET ${TARGET_SHARED} PROPERTY OUTPUT_NAME ${TARGET})

target_include_directories(${TARGET} PUBLIC
	${DLFCN_DIR_INCLUDE}
    )
target_include_directories(${TARGET_SHARED} PUBLIC
	${DLFCN_DIR_INCLUDE}
    )

target_link_libraries(${TARGET} PRIVATE
    ${CMAKE_DL_LIBS}
    )
target_link_libraries(${TARGET_SHARED} PRIVATE
    ${CMAKE_DL_LIBS}
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
    # ggwave-common-sdl2

	set(TARGET_SDL2 ggwave-common-sdl2)
	set(TARGET_SDL2_SHARED ggwave-common-sdl2.shared)

    add_library(${TARGET_SDL2}
        ggwave-common-sdl2.cpp
        )

	SET (CMAKE_LINK_DEF_FILE_FLAG "/DEF:ggwave-common-sdl2.def")
    add_library(${TARGET_SDL2_SHARED} SHARED
        ggwave-common-sdl2.cpp
		ggwave-common-sdl2.def
        )

	set_property(TARGET ${TARGET_SDL2_SHARED} PROPERTY OUTPUT_NAME ${TARGET_SDL2})

	target_include_directories(${TARGET_SDL2} PUBLIC
        ${SDL2_INCLUDE_DIRS}
        )
    target_include_directories(${TARGET_SDL2_SHARED} PUBLIC
        ${SDL2_INCLUDE_DIRS}
        )

    target_link_libraries(${TARGET_SDL2} PRIVATE
        ggwave
        imgui-sdl2
        ${SDL2_LIBRARIES}
        )
    target_link_libraries(${TARGET_SDL2_SHARED} PRIVATE
        ggwave
        imgui-sdl2
        ${SDL2_LIBRARIES}
        )
endif()

# examples

if (EMSCRIPTEN)
    add_subdirectory(ggwave-js)
    add_subdirectory(buttons)
else()
    add_subdirectory(ggwave-to-file)
endif()

if (GGWAVE_SUPPORT_SDL2)
    if (UNIX AND NOT APPLE)
        add_subdirectory(r2t2)
    endif()

    if (EMSCRIPTEN)
        # emscripten sdl2 examples

        add_subdirectory(ggwave-wasm)
    else()
        # non-emscripten sdl2 examples

        add_subdirectory(ggwave-rx)
        add_subdirectory(ggwave-cli)
    endif()

    add_subdirectory(waver)
    add_subdirectory(spectrogram)
endif()

install(TARGETS ggwave-common
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
    )

if (GGWAVE_SUPPORT_SDL2)
    install(TARGETS ggwave-common-sdl2
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
        )
endif()
