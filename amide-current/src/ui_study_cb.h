/* ui_study_cb.h
 *
 * Part of amide - Amide's a Medical Image Dataset Examiner
 * Copyright (C) 2001 Andy Loening
 *
 * Author: Andy Loening <loening@ucla.edu>
 */

/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.
*/


/* external functions */
void ui_study_cb_new_study(GtkWidget * button, gpointer data);
void ui_study_cb_open_study(GtkWidget * button, gpointer data);
void ui_study_cb_save_as(GtkWidget * widget, gpointer data);
void ui_study_cb_import(GtkWidget * widget, gpointer data);
void ui_study_cb_export(GtkWidget * widget, gpointer data);
gboolean ui_study_cb_update_help_info(GtkWidget * widget, GdkEventCrossing * event, gpointer data);
gboolean ui_study_cb_canvas_event(GtkWidget* widget, GdkEvent * event, gpointer data);
void ui_study_cb_plane_change(GtkObject * adjustment, gpointer data);
void ui_study_cb_zoom(GtkObject * adjustment, gpointer data);
void ui_study_cb_time_pressed(GtkWidget * combo, gpointer data);
void ui_study_cb_thickness(GtkObject * adjustment, gpointer data);
void ui_study_cb_series(GtkWidget * widget, gpointer ui_study_p);
#ifdef AMIDE_LIBVOLPACK_SUPPORT
void ui_study_cb_rendering_nearest_neighbor(GtkWidget * widget, gpointer data);
void ui_study_cb_rendering_trilinear(GtkWidget * widget, gpointer data);
#endif
void ui_study_cb_threshold_changed(GtkWidget * widget, gpointer data);
void ui_study_cb_color_changed(GtkWidget * widget, gpointer data);
void ui_study_cb_threshold_pressed(GtkWidget * button, gpointer data);
void ui_study_cb_scaling(GtkWidget * adjustment, gpointer data);
void ui_study_cb_entry_name(gchar * entry_string, gpointer data);
void ui_study_cb_add_roi_type(GtkWidget * widget, gpointer data);
void ui_study_cb_tree_leaf_clicked(GtkWidget * leaf, GdkEventButton * event, gpointer data);
void ui_study_cb_tree_clicked(GtkWidget * leaf, GdkEventButton * event, gpointer data);
void ui_study_cb_new_roi_ellipsoid(GtkWidget * widget, gpointer data);
void ui_study_cb_new_roi_cylinder(GtkWidget * widget, gpointer data);
void ui_study_cb_new_roi_box(GtkWidget * widget, gpointer data);
void ui_study_cb_edit_objects(GtkWidget * button, gpointer data);
void ui_study_cb_delete_objects(GtkWidget * button, gpointer data);
void ui_study_cb_interpolation(GtkWidget * widget, gpointer data);
void ui_study_cb_close(GtkWidget* widget, gpointer data);
void ui_study_cb_delete_event(GtkWidget* widget, GdkEvent * event, gpointer data);







