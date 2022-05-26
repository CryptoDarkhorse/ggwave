# core

set(TARGET ggwave)
set(TARGET_SHARED ggwave.shared)

add_library(${TARGET}
    ggwave.cpp
    resampler.cpp
    )

add_library(${TARGET_SHARED} SHARED
    ggwave.cpp
    resampler.cpp
    )

set_property(TARGET ${TARGET_SHARED} PROPERTY OUTPUT_NAME ${TARGET})

target_include_directories(${TARGET} PUBLIC
    .
    ../include
    )

target_include_directories(${TARGET_SHARED} PUBLIC
    .
    ../include
    )

target_link_libraries(${TARGET_SHARED} PUBLIC
    ${CMAKE_DL_LIBS}
)

target_compile_definitions(${TARGET_SHARED} PUBLIC
	GGWAVE_SHARED
)

if (MINGW)
    target_link_libraries(${TARGET} PUBLIC
        stdc++
        )
endif()

install(TARGETS ${TARGET}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
    )
