cmake_minimum_required(VERSION 3.20)
project(amide LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(${PROJECT_NAME})
target_compile_definitions(${PROJECT_NAME} PUBLIC AMIDE_DEBUG)

find_package(GTK2 REQUIRED)
find_package(LibXml2 REQUIRED)

find_path(gnomecanvas-2_INCLUDE_DIR
  NAMES libgnomecanvas/libgnomecanvas.h
  PATHS /usr/include/libgnomecanvas-2.0
)
mark_as_advanced(gnomecanvas-2_INCLUDE_DIR)
if (NOT gnomecanvas-2_INCLUDE_DIR)
  message(FATAL_ERROR
    "libgnomecanvas.h not found")
endif()

find_path(libart-2_INCLUDE_DIR
  NAMES libart_lgpl/libart.h
  PATHS /usr/include/libart-2.0
)
mark_as_advanced(libart-2_INCLUDE_DIR)
if (NOT libart-2_INCLUDE_DIR)
  message(FATAL_ERROR
    "libart.h not found")
endif()

INCLUDE_DIRECTORIES(
  ${GTK2_X11_INCLUDE_DIR}
  ${GTK2_GLIB_INCLUDE_DIR}
  ${GTK2_GLIBCONFIG_INCLUDE_DIR}
  ${GTK2_PANGO_INCLUDE_DIR}
  ${GTK2_HARFBUZZ_INCLUDE_DIR}
  ${GTK2_GTK_INCLUDE_DIR}
  ${GTK2_CAIRO_INCLUDE_DIR}
  ${GTK2_GDKCONFIG_INCLUDE_DIR}
  ${GTK2_GDK_PIXBUF_INCLUDE_DIR}
  ${GTK2_ATK_INCLUDE_DIR}
  ${gnomecanvas-2_INCLUDE_DIR}
  ${libart-2_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_BINARY_DIR}/src
)

target_link_libraries(${PROJECT_NAME} ${GTK2_LIBRARIES} gnomecanvas-2 ${LIBXML2_LIBRARIES} m)
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
