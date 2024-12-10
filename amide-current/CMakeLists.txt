cmake_minimum_required(VERSION 3.20)
project(amide LANGUAGES C CXX)
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


# try to locate optional libs

find_package(DCMTK)
if (DCMTK_DIR)
  option(AMIDE_LIBDCMDATA_SUPPORT "Enable DCMTK support" ON)
endif()
 
find_path(libmdc_INCLUDE_DIR
  NAMES medcon.h
  PATHS /usr/include
)
mark_as_advanced(libmdc_INCLUDE_DIR)
if (libmdc_INCLUDE_DIR)
  option(AMIDE_LIBMDC_SUPPORT "Enable libmdc support" ON)
else()
  message(FATAL_ERROR
    "/usr/include/medcon.h not found")
endif()

find_library(libmdc_LIBPATH
  NAMES libmdc.so
	PATHS /usr/lib/x86_64-linux-gnu
)


find_path(libgsl_INCLUDE_DIR
  NAMES gsl_version.h
  PATHS /usr/include/gsl
)
mark_as_advanced(libgsl_INCLUDE_DIR)
if (libgsl_INCLUDE_DIR)
  option(AMIDE_LIBGSL_SUPPORT "Enable libgsl support" ON)
else()
  message(FATAL_ERROR
    "gsl/gsl_version.h not found")
endif()

find_library(libgsl_LIB_DIR
  NAMES libgsl.so
	PATHS /usr/lib/x86_64-linux-gnu
)
# if (libgsl_LIB_DIR)
  # target_link_libraries(amide PRIVATE gsl)
#   target_link_directories(amide PRIVATE ${libgsl_LIB_DIR})
# endif()

find_path(volpack_INCLUDE_DIR
  NAMES volpack.h
  PATHS /usr/include
)
mark_as_advanced(volpack_INCLUDE_DIR)
if (volpack_INCLUDE_DIR)
  option(AMIDE_LIBVOLPACK_SUPPORT "Enable libvolpack support" ON)
else()
  message(FATAL_ERROR
    "volpack.h not found")
endif()

find_library(libvolpack_LIBPATH
  NAMES libvolpack.so
  PATH /usr/lib/x86_64-linux-gnu
)

option(AMIDE_LIBGNOMECANVAS_AA "Enable libgnomecanvas" ON)

set(PACKAGE_TARNAME "amide")
set(PACKAGE_VERSION "1.0.6")
set(PACKAGE "amide")
set(VERSION "1.0.6")
set(PACKAGE_BUGREPORT "amide-users@lists.sourceforge.net")
set(GETTEXT_PACKAGE "amide")
set(AMIDE_DATADIR "/tmp")
set(SIZEOF_LONG_LONG 8)
configure_file(amide_config.h.in src/amide_config.h @ONLY)

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
	${libmdc_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_BINARY_DIR}/src
)

target_link_libraries(${PROJECT_NAME} ${GTK2_LIBRARIES} gnomecanvas-2 ${LIBXML2_LIBRARIES} ${libgsl_LIB_DIR} ${libvolpack_LIBPATH} ${libmdc_LIBPATH} DCMTK::DCMTK m)
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
