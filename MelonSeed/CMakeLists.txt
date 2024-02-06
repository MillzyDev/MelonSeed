set(COMPILE_ID MelonSeed)

cmake_minimum_required(VERSION 3.27)
project(${COMPILE_ID})

set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shared)

if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    message(SEND_ERROR "Compiler is not supported. Please use Clang.")
endif ()

MACRO(RECURSE_FILES return_list filter)
    FILE(GLOB_RECURSE new_list ${filter})
    SET(file_list "")
    FOREACH(file_path ${new_list})
        SET(file_list ${file_list} ${file_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES file_list)
    SET(${return_list} ${file_list})
ENDMACRO()

file(READ game_path.txt GAME_PATH)
file(READ unity_path.txt UNITY_PATH)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${GAME_PATH}/${COMPILE_ID}")

RECURSE_FILES(cpp_file_list ${SOURCE_DIR}/*.cpp)
RECURSE_FILES(c_file_list ${SOURCE_DIR}/*.c)

add_library(
        ${COMPILE_ID}
        SHARED
        ${cpp_file_list}
        ${c_file_list}
)

target_include_directories(${COMPILE_ID} PRIVATE .)
target_include_directories(${COMPILE_ID} PRIVATE ${SOURCE_DIR})
target_include_directories(${COMPILE_ID} PRIVATE ${INCLUDE_DIR})
target_include_directories(${COMPILE_ID} PUBLIC ${SHARED_DIR})

target_compile_definitions(${COMPILE_ID} PUBLIC MELON_SEED_EXPORTS)

add_subdirectory(Dobby)
target_link_libraries(${COMPILE_ID} PUBLIC dobby)

# These definitions ensure IL2CPP doesnt cause build errors because we're not using MSVC on Windows
if (WIN32)
    add_compile_definitions(
          IL2CPP_TARGET_CUSTOM=1 # Prevents IL2CPP from producing a compile error

          # Everything else is just other settings I stole from what using MSVC would set.
          IL2CPP_TARGET_WINDOWS=1

          IL2CPP_TARGET_WINDOWS_DESKTOP=1
          IL2CPP_PLATFORM_SUPPORTS_SYSTEM_CERTIFICATES=1
          IL2CPP_PLATFORM_SUPPORTS_CPU_INFO=1

          NTDDI_VERSION=0x06010000
          _WIN32_WINNT=0x0601
          WINVER=0x0601

          _UNICODE=1
          UNICODE=1
          STRICT=1
    )
else ()

endif ()

target_include_directories(${COMPILE_ID} PUBLIC "${UNITY_PATH}/Editor/Data/il2cpp/libil2cpp")
target_link_libraries(${COMPILE_ID} PUBLIC "${GAME_PATH}/GameAssembly.dll")