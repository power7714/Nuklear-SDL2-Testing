cmake_minimum_required(VERSION 3.10)
project(ArithmeticGame)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Define the source files
set(SOURCE_FILES
        main.c         # Replace with your actual source file names
        nuklear.h      # Include nuklear header if needed
        nuklear_sdl.h
        functions.h
        functions.c
        nuklear_sdl.c
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find OpenGL package
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Add necessary include directories
include_directories(${CMAKE_SOURCE_DIR})

# Add Nuklear (assuming nuklear.h and nuklear_sdl.h are in the project directory)
include_directories(${CMAKE_SOURCE_DIR})

# Link SDL2, OpenGL, and Nuklear
# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find TTF (optional, for text rendering)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# Find OpenGL package
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Find GLEW package
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Add necessary include directories
include_directories(${CMAKE_SOURCE_DIR})

# Add Nuklear (assuming nuklear.h and nuklear_sdl.h are in the project directory)
include_directories(${CMAKE_SOURCE_DIR})

# Link SDL2, OpenGL, and Nuklear
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} GL)
