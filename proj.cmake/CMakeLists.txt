cmake_minimum_required (VERSION 2.6)
project (The_game_of_life)

add_subdirectory(../../libs/oxygine-framework/ oxygine-framework)
#add_subdirectory(../../libs/oxygine-freetype/ oxygine-freetype)
#add_subdirectory(../../libs/oxygine-sound/ oxygine-sound)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

add_executable(The_game_of_life ../src/example.cpp ../src/example.h ../src/main.cpp)
target_link_libraries(The_game_of_life ${OXYGINE_CORE_LIBS})

if (WIN32) #disable console mode for VC++
	set_target_properties(The_game_of_life PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

if (EMSCRIPTEN)
	SET(CMAKE_EXECUTABLE_SUFFIX ".html")	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1 -s WASM=0 -s WARN_ON_UNDEFINED_SYMBOLS=1 --memory-init-file 0 -s TOTAL_MEMORY=50331648 -s FORCE_FILESYSTEM=1")
	em_link_pre_js(The_game_of_life  ${OXYGINE_JS_LIBRARIES}  ${CMAKE_CURRENT_SOURCE_DIR}/data.js)
endif(EMSCRIPTEN)