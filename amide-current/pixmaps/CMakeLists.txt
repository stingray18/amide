include(CMakePrintHelpers)

set (pixmap_DATA
	align_pt.png
	amide_file_logo.png
	amide_logo.png
	fuse_type_blend.png
	fuse_type_overlay.png
	interpolation_nearest_neighbor.png
	interpolation_trilinear.png
	layout_linear.png
	layout_orthogonal.png
	panels_linear_x.png
	panels_linear_y.png
	panels_mixed.png
	roi_box.png
	roi_cylinder.png
	roi_ellipsoid.png
	roi_freehand_2d.png
	roi_freehand_3d.png
	roi_isocontour_2d.png
	roi_isocontour_3d.png
	study.png
	target.png
	three_compartment.png
	threshold_style_center_width.png
	threshold_style_min_max.png
	thresholding.png
	thresholding_global.png
	thresholding_interpolate_frames.png
	thresholding_per_frame.png
	thresholding_per_slice.png
	transfer_function.png
	two_compartment.png
	view_coronal.png
	view_linked.png
	view_linked3.png
	view_sagittal.png
	view_single.png
	view_transverse.png
	window_abdomen.png
	window_bone.png
	window_brain.png
	window_extremities.png
	window_liver.png
	window_lung.png
	window_pelvis_soft_tissue.png
	window_skull_base.png
	window_soft_tissue.png
	window_spine_a.png
	window_spine_b.png
	window_thorax_soft_tissue.png
)

set(AMITK_BUILT_SOURCES_TARGET)
foreach(file ${pixmap_DATA})
	string(REPLACE ".png" ".h" output_h ${file})
	string(REPLACE ".png" "" identifier ${file})
	add_custom_command(
		OUTPUT ${output_h}
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && gdk-pixbuf-csource --raw --extern --name=${identifier} ${file} > ${CMAKE_CURRENT_BINARY_DIR}/${output_h}
		)
  list(APPEND AMITK_BUILT_SOURCES_TARGET ${CMAKE_CURRENT_BINARY_DIR}/${output_h})
endforeach()
add_custom_target(do_build_sources DEPENDS ${AMITK_BUILT_SOURCES_TARGET})
add_dependencies(amide do_build_sources)
