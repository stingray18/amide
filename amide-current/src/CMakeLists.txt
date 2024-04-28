set(AMITK_ROI_VARIABLE_C
	amitk_roi_ELLIPSOID.c
	amitk_roi_CYLINDER.c
	amitk_roi_BOX.c
	amitk_roi_ISOCONTOUR_2D.c
	amitk_roi_ISOCONTOUR_3D.c
	amitk_roi_FREEHAND_2D.c
	amitk_roi_FREEHAND_3D.c
)
# set_source_files_properties(${AMITK_ROI_VARIABLE_C} PROPERTIES GENERATED TRUE)
set(AMITK_ROI_VARIABLE_C_TARGET)
foreach(file ${AMITK_ROI_VARIABLE_C})
	add_custom_command(
		OUTPUT ${file}
		# COMMAND rm -f ${file}
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && m4 -P -Dm4_SourceFile=${file} variable_type.m4 > ${CMAKE_CURRENT_BINARY_DIR}/${file}
		# COMMAND chmod -w ${file}
		)
	list(APPEND AMITK_ROI_VARIABLE_C_TARGET ${file})
endforeach()
add_custom_target(do_amitk_roi_variable_c DEPENDS ${AMITK_ROI_VARIABLE_C_TARGET})
add_dependencies(amide do_amitk_roi_variable_c)

set(AMITK_ROI_VARIABLE_H
	amitk_roi_ELLIPSOID.h
	amitk_roi_CYLINDER.h
	amitk_roi_BOX.h
	amitk_roi_ISOCONTOUR_2D.h
	amitk_roi_ISOCONTOUR_3D.h
	amitk_roi_FREEHAND_2D.h
	amitk_roi_FREEHAND_3D.h
)
set_source_files_properties(${AMITK_ROI_VARIABLE_H} PROPERTIES GENERATED TRUE)
set(AMITK_ROI_VARIABLE_H_TARGET)
foreach(file ${AMITK_ROI_VARIABLE_H})
	add_custom_command(
		OUTPUT ${file}
		# COMMAND rm -f ${file}
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && m4 -P -Dm4_SourceFile=${file} variable_type.m4 > ${CMAKE_CURRENT_BINARY_DIR}/${file}
		# COMMAND chmod -w ${file}
		)
	list(APPEND AMITK_ROI_VARIABLE_H_TARGET ${file})
endforeach()
add_custom_target(do_amitk_roi_variable_h DEPENDS ${AMITK_ROI_VARIABLE_H_TARGET})
add_dependencies(amide do_amitk_roi_variable_h)


set(AMITK_RAW_DATA_VARIABLE_H amitk_raw_data_UBYTE.h amitk_raw_data_SBYTE.h amitk_raw_data_USHORT.h amitk_raw_data_SSHORT.h amitk_raw_data_UINT.h amitk_raw_data_SINT.h amitk_raw_data_FLOAT.h amitk_raw_data_DOUBLE.h)
set_source_files_properties(${AMITK_RAW_DATA_VARIABLE_H} PROPERTIES GENERATED TRUE)
set(AMITK_RAW_DATA_VARIABLE_H_TARGET)
foreach(file ${AMITK_RAW_DATA_VARIABLE_H})
	add_custom_command(
		OUTPUT ${file}
		# COMMAND rm -f ${file}
		COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && m4 -P -Dm4_SourceFile=${file} variable_type.m4 > ${CMAKE_CURRENT_BINARY_DIR}/${file}
		# COMMAND chmod -w ${file}
		)
	list(APPEND AMITK_RAW_DATA_VARIABLE_H_TARGET ${file})
endforeach()
add_custom_target(do_amitk_raw_data_variable_h DEPENDS ${AMITK_RAW_DATA_VARIABLE_H_TARGET})
add_dependencies(amide do_amitk_raw_data_variable_h)

set(AMITK_RAW_DATA_VARIABLE_C
	amitk_raw_data_UBYTE.c
	amitk_raw_data_SBYTE.c
	amitk_raw_data_USHORT.c
	amitk_raw_data_SSHORT.c
	amitk_raw_data_UINT.c
	amitk_raw_data_SINT.c
	amitk_raw_data_FLOAT.c
	amitk_raw_data_DOUBLE.c
)
set_source_files_properties(${AMITK_RAW_DATA_VARIABLE_C} PROPERTIES GENERATED TRUE)
set(AMITK_RAW_DATA_VARIABLE_C_TARGET)
foreach(file ${AMITK_RAW_DATA_VARIABLE_C})
	add_custom_command(
		OUTPUT ${file}
		# COMMAND rm -f ${file}
		COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && m4 -P -Dm4_SourceFile=${file} variable_type.m4 > ${CMAKE_CURRENT_BINARY_DIR}/${file}
		# COMMAND chmod -w ${file}
		)
	list(APPEND AMITK_RAW_DATA_VARIABLE_C_TARGET ${file})
endforeach()
add_custom_target(do_amitk_raw_data_variable_c DEPENDS ${AMITK_RAW_DATA_VARIABLE_C_TARGET})
add_dependencies(amide do_amitk_raw_data_variable_c)


set(AMITK_DATA_SET_VARIABLE_C
	amitk_data_set_UBYTE_0D_SCALING.c
	amitk_data_set_UBYTE_1D_SCALING.c
	amitk_data_set_UBYTE_2D_SCALING.c
	amitk_data_set_SBYTE_0D_SCALING.c
	amitk_data_set_SBYTE_1D_SCALING.c
	amitk_data_set_SBYTE_2D_SCALING.c
	amitk_data_set_USHORT_0D_SCALING.c
	amitk_data_set_USHORT_1D_SCALING.c
	amitk_data_set_USHORT_2D_SCALING.c
	amitk_data_set_SSHORT_0D_SCALING.c
	amitk_data_set_SSHORT_1D_SCALING.c
	amitk_data_set_SSHORT_2D_SCALING.c
	amitk_data_set_UINT_0D_SCALING.c
	amitk_data_set_UINT_1D_SCALING.c
	amitk_data_set_UINT_2D_SCALING.c
	amitk_data_set_SINT_0D_SCALING.c
	amitk_data_set_SINT_1D_SCALING.c
	amitk_data_set_SINT_2D_SCALING.c
	amitk_data_set_FLOAT_0D_SCALING.c
	amitk_data_set_FLOAT_1D_SCALING.c
	amitk_data_set_FLOAT_2D_SCALING.c
	amitk_data_set_DOUBLE_0D_SCALING.c
	amitk_data_set_DOUBLE_1D_SCALING.c
	amitk_data_set_DOUBLE_2D_SCALING.c
	amitk_data_set_UBYTE_0D_SCALING_INTERCEPT.c
	amitk_data_set_UBYTE_1D_SCALING_INTERCEPT.c
	amitk_data_set_UBYTE_2D_SCALING_INTERCEPT.c
	amitk_data_set_SBYTE_0D_SCALING_INTERCEPT.c
	amitk_data_set_SBYTE_1D_SCALING_INTERCEPT.c
	amitk_data_set_SBYTE_2D_SCALING_INTERCEPT.c
	amitk_data_set_USHORT_0D_SCALING_INTERCEPT.c
	amitk_data_set_USHORT_1D_SCALING_INTERCEPT.c
	amitk_data_set_USHORT_2D_SCALING_INTERCEPT.c
	amitk_data_set_SSHORT_0D_SCALING_INTERCEPT.c
	amitk_data_set_SSHORT_1D_SCALING_INTERCEPT.c
	amitk_data_set_SSHORT_2D_SCALING_INTERCEPT.c
	amitk_data_set_UINT_0D_SCALING_INTERCEPT.c
	amitk_data_set_UINT_1D_SCALING_INTERCEPT.c
	amitk_data_set_UINT_2D_SCALING_INTERCEPT.c
	amitk_data_set_SINT_0D_SCALING_INTERCEPT.c
	amitk_data_set_SINT_1D_SCALING_INTERCEPT.c
	amitk_data_set_SINT_2D_SCALING_INTERCEPT.c
	amitk_data_set_FLOAT_0D_SCALING_INTERCEPT.c
	amitk_data_set_FLOAT_1D_SCALING_INTERCEPT.c
	amitk_data_set_FLOAT_2D_SCALING_INTERCEPT.c
	amitk_data_set_DOUBLE_0D_SCALING_INTERCEPT.c
	amitk_data_set_DOUBLE_1D_SCALING_INTERCEPT.c
	amitk_data_set_DOUBLE_2D_SCALING_INTERCEPT.c
)
set(AMITK_DATA_SET_VARIABLE_C_TARGET)
foreach(file ${AMITK_DATA_SET_VARIABLE_C})
	add_custom_command(
		OUTPUT ${file}
		# COMMAND rm -f ${file}
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && m4 -P -Dm4_SourceFile=${file} variable_type.m4 > ${CMAKE_CURRENT_BINARY_DIR}/${file}
		# COMMAND chmod -w ${file}
		)
	list(APPEND AMITK_DATA_SET_VARIABLE_C_TARGET ${file})
endforeach()
add_custom_target(do_amitk_data_set_variable_c DEPENDS ${AMITK_DATA_SET_VARIABLE_C_TARGET})
add_dependencies(amide do_amitk_data_set_variable_c)

set(AMITK_DATA_SET_VARIABLE_H
	amitk_data_set_UBYTE_0D_SCALING.h
	amitk_data_set_UBYTE_1D_SCALING.h
	amitk_data_set_UBYTE_2D_SCALING.h
	amitk_data_set_SBYTE_0D_SCALING.h
	amitk_data_set_SBYTE_1D_SCALING.h
	amitk_data_set_SBYTE_2D_SCALING.h
	amitk_data_set_USHORT_0D_SCALING.h
	amitk_data_set_USHORT_1D_SCALING.h
	amitk_data_set_USHORT_2D_SCALING.h
	amitk_data_set_SSHORT_0D_SCALING.h
	amitk_data_set_SSHORT_1D_SCALING.h
	amitk_data_set_SSHORT_2D_SCALING.h
	amitk_data_set_UINT_0D_SCALING.h
	amitk_data_set_UINT_1D_SCALING.h
	amitk_data_set_UINT_2D_SCALING.h
	amitk_data_set_SINT_0D_SCALING.h
	amitk_data_set_SINT_1D_SCALING.h
	amitk_data_set_SINT_2D_SCALING.h
	amitk_data_set_FLOAT_0D_SCALING.h
	amitk_data_set_FLOAT_1D_SCALING.h
	amitk_data_set_FLOAT_2D_SCALING.h
	amitk_data_set_DOUBLE_0D_SCALING.h
	amitk_data_set_DOUBLE_1D_SCALING.h
	amitk_data_set_DOUBLE_2D_SCALING.h
)
set(AMITK_DATA_SET_VARIABLE_H_TARGET)
foreach(file ${AMITK_DATA_SET_VARIABLE_H})
	add_custom_command(
		OUTPUT ${file}
		# COMMAND rm -f ${file}
		COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && m4 -P -Dm4_SourceFile=${file} variable_type.m4 > ${CMAKE_CURRENT_BINARY_DIR}/${file}
		# COMMAND chmod -w ${file}
		)
	list(APPEND AMITK_DATA_SET_VARIABLE_H_TARGET ${file})
endforeach()
add_custom_target(do_amitk_data_set_variable_h DEPENDS ${AMITK_DATA_SET_VARIABLE_H_TARGET})
add_dependencies(amide do_amitk_data_set_variable_h)

set(AMITK_MARSHAL_H_TARGET amitk_marshal.h)
add_custom_command(
	OUTPUT ${AMITK_MARSHAL_H_TARGET}
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && glib-genmarshal amitk_marshal.list --header --prefix=amitk_marshal > ${AMITK_MARSHAL_H_TARGET}
)
add_custom_target(do_amitk_marshal_h DEPENDS ${AMITK_MARSHAL_H_TARGET})
add_dependencies(amide do_amitk_marshal_h)

set(AMITK_MARSHAL_C_TARGET amitk_marshal.c)
add_custom_command(
	OUTPUT ${AMITK_MARSHAL_C_TARGET}
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && glib-genmarshal amitk_marshal.list --body --prefix=amitk_marshal > ${AMITK_MARSHAL_C_TARGET}
)
add_custom_target(do_amitk_marshal_c DEPENDS ${AMITK_MARSHAL_C_TARGET})
add_dependencies(amide do_amitk_marshal_c)

set(AMITK_H_SOURCES
	amitk_canvas.h
	amitk_canvas_object.h
	amitk_color_table.h
	amitk_color_table_menu.h
	amitk_common.h
	amitk_dial.h
	amitk_data_set.h
	amitk_fiducial_mark.h
	amitk_filter.h
	amitk_line_profile.h
	amitk_object.h
	amitk_object_dialog.h
	amitk_point.h
	amitk_preferences.h
	amitk_progress_dialog.h
	amitk_raw_data.h
	amitk_roi.h
	amitk_space_edit.h
	amitk_space.h
	amitk_study.h
	amitk_threshold.h
	amitk_tree_view.h
	amitk_type.h
	amitk_volume.h
	amitk_window_edit.h
)

set(AMITK_TYPE_BUILTINS_H_TARGET amitk_type_builtins.h)
add_custom_command(
	OUTPUT ${AMITK_TYPE_BUILTINS_H_TARGET}
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && glib-mkenums --fhead "#ifndef __AMITK_TYPE_BUILTINS_H__\\n#define\ __AMITK_TYPE_BUILTINS_H__\\n\\n#include <glib-object.h>\\n\\nG_BEGIN_DECLS\\n" --fprod "/* enumerations from \"@filename@\" */\\n" --vhead "GType @enum_name@_get_type (void);\\n#define AMITK_TYPE_@ENUMSHORT@ (@enum_name@_get_type())\\n" --ftail "G_END_DECLS\\n\\n#endif /* __AMITK_TYPE_BUILTINS_H__ */" ${AMITK_H_SOURCES}  >> xgen-atbh && cmp -s xgen-atbh amitk_type_builtins.h || cp xgen-atbh amitk_type_builtins.h && rm -f xgen-atbh && echo timestamp > stamp-amitk_type_builtins.h
	VERBATIM
)
add_custom_target(do_amitk_type_builtins_h DEPENDS ${AMITK_TYPE_BUILTINS_H_TARGET})
add_dependencies(amide do_amitk_type_builtins_h)

set(AMITK_TYPE_BUILTINS_C_TARGET amitk_type_builtins.c)
add_custom_command(
	OUTPUT ${AMITK_TYPE_BUILTINS_C_TARGET}
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && glib-mkenums --fhead "#include <gtk/gtk.h>\\n#include \"amide_config.h\"\\n#include \"amitk_common.h\"\\n#include \"amitk_canvas.h\"\\n#include \"amitk_data_set.h\"\\n#include \"amitk_filter.h\"\\n#include \"amitk_object.h\"\\n#include \"amitk_point.h\"\\n#include \"amitk_raw_data.h\"\\n#include \"amitk_roi.h\"\\n#include \"amitk_space.h\"\\n#include \"amitk_threshold.h\"\\n#include \"amitk_tree_view.h\"\\n" --fprod "\\n/* enumerations from \"@filename@\" */" --vhead "GType\\n@enum_name@_get_type (void)\\n{\\n  static GType etype = 0;\\n  if (etype == 0) {\\n    static const G@Type@Value values[] = {" --vprod "      { @VALUENAME@, \"@VALUENAME@\", \"@valuenick@\" }," --vtail "      { 0, NULL, NULL }\\n    };\\n    etype = g_@type@_register_static (\"@EnumName@\", values);\\n  }\\n  return etype;\\n}\\n" ${AMITK_H_SOURCES} > xgen-atbc && cp xgen-atbc amitk_type_builtins.c && rm -f xgen-atbc && echo timestamp > stamp-amitk_type_builtins.c
	VERBATIM
)
add_custom_target(do_amitk_type_builtins_c DEPENDS ${AMITK_TYPE_BUILTINS_C_TARGET})
add_dependencies(amide do_amitk_type_builtins_c)

target_sources(${PROJECT_NAME} PUBLIC amide.c amide_gnome.c amitk_common.c amitk_canvas.c
	amide_gconf.c
	amitk_canvas_object.c
	amitk_color_table.c
	amitk_color_table_menu.c
	amitk_data_set.c
	amitk_dial.c
	amitk_fiducial_mark.c
	amitk_filter.c
	amitk_line_profile.c
	amitk_object.c
	amitk_object_dialog.c
	amitk_point.c
	amitk_preferences.c
	amitk_progress_dialog.c
	amitk_raw_data.c
	amitk_roi.c
	amitk_space.c
	amitk_space_edit.c
	amitk_study.c
	amitk_threshold.c
	amitk_tree_view.c
	amitk_volume.c
	amitk_window_edit.c
	alignment_mutual_information.c
	alignment_procrustes.c
	analysis.c
	dcmtk_interface.cc
	fads.c
	image.c
	legacy.c
	libecat_interface.c
	libmdc_interface.c
	mpeg_encode.c
	pixmaps.c
	raw_data_import.c
	render.c
	tb_alignment.c
	tb_crop.c
	tb_distance.c
	tb_export_data_set.c
	tb_fads.c
	tb_filter.c
	tb_fly_through.c
	tb_math.c
	tb_profile.c
	tb_roi_analysis.c
	ui_common.c
	ui_gate_dialog.c
	ui_preferences_dialog.c
	ui_render.c
	ui_render_dialog.c
	ui_render_movie.c
	ui_series.c
	ui_study.c
	ui_study_cb.c
	ui_time_dialog.c
	vistaio_interface.c
	xml.c
  # ${AMITK_RAW_DATA_VARIABLE_C_TARGET} ${AMITK_DATA_SET_VARIABLE_C_TARGET} ${AMITK_ROI_VARIABLE_C_TARGET} ${AMITK_MARSHAL_C_TARGET} ${AMITK_TYPE_BUILTINS_C_TARGET}
  )
