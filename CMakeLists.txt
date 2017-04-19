cmake_minimum_required(VERSION 2.8.0)

project(EJVulkan)

# ------------------------------------------------------------------------------
# Set compiler options
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
if (NOT WIN32)
  # Linux or Mac OS X
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread")
endif()


# ------------------------------------------------------------------------------
# Set output path
# ------------------------------------------------------------------------------
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ------------------------------------------------------------------------------
# Set output path
# ------------------------------------------------------------------------------
add_executable(out
main.cpp
E_Manager.h
E_Manager.cpp
E_Renderer.h
E_Renderer.cpp
E_Camera.h
E_Camera.cpp
E_Object.h
E_Object.cpp
VDeleter.hpp
vulkan.hpp
E_Struct.hpp
)
# add_subdirectory(sources)

# ------------------------------------------------------------------------------
# Import graphics libraries
# ------------------------------------------------------------------------------
find_package(OpenGL REQUIRED)

# set(GLM_ROOT ${GLM_ROOT} CACHE PATH "GLM-NOT_FOUND")
# if (NOT EXISTS "${GLM_ROOT}/include/glm/glm.hpp")
#   message(FATAL_ERROR "[ERROR] glm not found!!")
# else()
#   message(STATUS "GLM: ${GLM_ROOT}")
#   set(GLM_INCLUDE_DIR "${GLM_ROOT}/include")
# endif()


#add GLFW
set(GLFW3_ROOT "/Users/ej/Documents/LIBS/glfw/LIB" CACHE PATH "GLFW3-NOT_FOUND")

if (NOT EXISTS "${GLFW3_ROOT}/include/GLFW/glfw3.h")
  message(FATAL_ERROR "[ERROR] GLFW3 not found!!")
else()
  message(STATUS "GLFW3: ${GLFW3_ROOT}")
  set(GLFW3_INCLUDE_DIR "${GLFW3_ROOT}/include")
  INCLUDE_DIRECTORIES(${GLFW3_INCLUDE_DIR})

  if (WIN32)
    set(GLFW3_LIBRARIES "${GLFW3_ROOT}/lib/glfw3.lib")
  elseif(APPLE)
    set(GLFW3_LIBRARIES "${GLFW3_ROOT}/lib/libglfw3.a")
    target_link_libraries(out ${GLFW3_LIBRARIES})
  endif()
endif()


#Addd Vulkan
set(VULKAN_ROOT "/Users/ej/Documents/LIBS/Molten-0.16.1/MoltenVK/macOS" CACHE PATH "VULKAN-NOT-FOUND")

if (MSVC)
  if (NOT EXISTS "${VULKAN_ROOT}/Include/vulkan/vulkan.h")
    message(FATAL_ERROR "[ERROR] Vulkan SDK not found!!")
  else()
    message(STATUS "Vulkan: ${VULKAN_ROOT}")
    set(VULKAN_INCLUDE_DIR "${VULKAN_ROOT}/Include")
    set(VULKAN_LIBRARIES "${VULKAN_ROOT}/Bin/vulkan-1.lib")
  endif()
elseif(APPLE)
  #add MoltenVK.framework from ${VULKAN_ROOT}
  find_library(VULKAN_LIBRARY NAMES MoltenVK PATHS "${VULKAN_ROOT}")
  set(VULKAN_INCLUDE_DIR "${VULKAN_ROOT}/MoltenVK.framework/Versions/A/Headers")
  INCLUDE_DIRECTORIES(${VULKAN_INCLUDE_DIR})
  INCLUDE_DIRECTORIES("/usr/local/include")


  target_link_libraries(out ${VULKAN_LIBRARY})
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework Metal -framework QuartzCore")
endif()
