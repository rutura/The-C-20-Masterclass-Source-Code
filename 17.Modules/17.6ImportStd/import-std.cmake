# target_use_import_std(<target>)
#
# Lets the sources of <target> say `import std;`, with MSVC, GCC and Clang.
#
#   MSVC        CMake's own support for `import std;` (experimental in CMake 3.30 and
#               3.31): it compiles Microsoft's std.ixx for you. The experimental gate
#               must be switched on BEFORE project(); see the top of CMakeLists.txt.
#   GCC, Clang  CMake cannot do it yet, but the standard library ships the SOURCE of the
#               module `std`. We add that file to the target as one more module, and
#               CMake compiles it first, like any module of the project.
#               Clang needs libc++ for this: libstdc++ has no module source Clang can use.
#
# If the module source is not found (a different compiler installation), pass its
# path:   -DSTD_MODULE_SOURCE=/path/to/std.cc      (GCC)
#         -DSTD_MODULE_SOURCE=/path/to/std.cppm    (Clang with libc++)

function(target_use_import_std target)
    if(MSVC)
        set_target_properties(${target} PROPERTIES CXX_MODULE_STD ON)
        return()
    endif()

    set(source "${STD_MODULE_SOURCE}")

    if(NOT source AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # GCC 15 and later describe their module sources in libstdc++.modules.json,
        # with paths relative to that file.
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -print-file-name=libstdc++.modules.json
                        OUTPUT_VARIABLE json_path OUTPUT_STRIP_TRAILING_WHITESPACE)
        if(EXISTS "${json_path}")
            file(READ "${json_path}" json)
            string(JSON relative_source GET "${json}" modules 0 source-path)
            get_filename_component(json_dir "${json_path}" DIRECTORY)
            get_filename_component(source "${json_dir}/${relative_source}" ABSOLUTE)
        endif()
    endif()

    if(NOT source AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # The course image keeps libc++'s module source here.
        file(GLOB candidates "/usr/lib/llvm-*/share/libc++/v1/std.cppm" "/usr/share/libc++/v1/std.cppm")
        list(GET candidates 0 source)
    endif()

    if(NOT EXISTS "${source}")
        message(FATAL_ERROR "cannot find the source of the module std; pass -DSTD_MODULE_SOURCE=...")
    endif()

    get_filename_component(source_dir "${source}" DIRECTORY)
    target_sources(${target} PRIVATE
        FILE_SET CXX_MODULES BASE_DIRS "${source_dir}" FILES "${source}")

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${target} PRIVATE -stdlib=libc++ -Wno-reserved-module-identifier)
        target_link_options(${target} PRIVATE -stdlib=libc++)
    endif()
endfunction()
