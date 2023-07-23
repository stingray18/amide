cmake_minimum_required(VERSION 3.20)
project(amide LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PUBLIC AMIDE_DEBUG)

INCLUDE_DIRECTORIES("/usr/include/glib-2.0" "/usr/lib64/glib-2.0/include" "/usr/include/pango-1.0" "/usr/include/harfbuzz"
	"/usr/include/gtk-2.0" "/usr/include/cairo" "/usr/include/gdk-pixbuf-2.0" "/usr/include/atk-1.0" "/usr/include/libgnomecanvas-2.0"
	"/usr/include/libart-2.0" "/usr/include/libxml2" "/usr/lib64/gtk-2.0/include" "/usr/include/glib-2.0" ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} gtk-x11-2.0 glib-2.0 gobject-2.0 gdk-x11-2.0 atk-1.0 pango-1.0 gnomecanvas-2 gdk_pixbuf-2.0 xml2 m)
add_subdirectory(src)
add_subdirectory(pixmaps)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
# configure_file("amide_config.h.cmakein" "src/amide_config.h")


if (CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(
		-fdiagnostics-color=auto
		-Wall
		-Wextra
		-Wno-unused-parameter
		-Wno-unused-but-set-parameter
		-Wno-implicit-fallthrough
	)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
	if (USE_LLD_LINKER)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=lld")
	endif(USE_LLD_LINKER)
	set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")
endif (CMAKE_COMPILER_IS_GNUCXX)


if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
		"Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel."
		FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS None Debug Release RelWithDebInfo MinSizeRel)
endif()
