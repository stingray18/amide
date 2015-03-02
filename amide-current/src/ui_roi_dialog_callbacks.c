/* ui_roi_dialog_callbacks.c
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

#include "config.h"
#include <gnome.h>
#include <math.h>
#include "amide.h"
#include "study.h"
#include "image.h"
#include "ui_threshold.h"
#include "ui_series.h"
#include "ui_roi.h"
#include "ui_volume.h"
#include "ui_study.h"
#include "ui_roi_dialog.h"
#include "ui_roi_dialog_callbacks.h"

/* function called when the name of the roi has been changed */
void ui_roi_dialog_callbacks_change_name(GtkWidget * widget, gpointer data) {

  roi_t * roi_new_info = data;
  gchar * new_name;
  GtkWidget * roi_dialog;

  /* get the contents of the name entry box and save it */
  new_name = gtk_editable_get_chars(GTK_EDITABLE(widget), 0, -1);
  roi_set_name(roi_new_info, new_name);
  g_free(new_name);

  /* tell the roi_dialog that we've changed */
  roi_dialog =  gtk_object_get_data(GTK_OBJECT(widget), "roi_dialog");
  gnome_property_box_changed(GNOME_PROPERTY_BOX(roi_dialog));

  return;
}

/* function called when a numerical entry of the roi has been changed, 
   used for the coordinate frame offset, axis, and the roi's corner*/
void ui_roi_dialog_callbacks_change_entry(GtkWidget * widget, gpointer data) {

  roi_t * roi_new_info = data;
  gchar * str;
  gint error;
  gdouble temp_val;
  which_entry_widget_t which_widget;
  realpoint_t temp_center;
  realpoint_t temp_dim;
  realspace_t temp_coord_frame;
  realpoint_t temp;
  axis_t i_axis;
  GtkWidget * roi_dialog;

  /* initialize the center and dimension variables based on the old roi info */
  temp_center = roi_calculate_center(roi_new_info); /* in real coords */
  temp_dim = roi_new_info->corner; /* in roi's coords */
  for (i_axis=0;i_axis<NUM_AXIS;i_axis++)
    temp_coord_frame.axis[i_axis] = roi_new_info->coord_frame.axis[i_axis];
  temp_coord_frame.offset = realpoint_init;

  /* figure out which widget this is */
  which_widget = GPOINTER_TO_INT(gtk_object_get_data(GTK_OBJECT(widget), "type")); 
  
  /* get the contents of the name entry box */
  str = gtk_editable_get_chars(GTK_EDITABLE(widget), 0, -1);

  /* convert to a floating point */
  error = sscanf(str, "%lf", &temp_val);
  g_free(str);

  if (error == EOF)  /* make sure it's a valid number */
    return;
  
  /* and save the value until it's applied to the actual roi */
  switch(which_widget) {
  case CENTER_X:
    temp_center.x = temp_val;
    break;
  case CENTER_Y:
    temp_center.y = temp_val;
    break;
  case CENTER_Z:
    temp_center.z = temp_val;
    break;
  case DIM_X:
    temp_dim.x = fabs(temp_val);
    break;
  case DIM_Y:
    temp_dim.y = fabs(temp_val);
    break;
  case DIM_Z:
    temp_dim.z = fabs(temp_val);
    break;
  case AXIS_X_X:
    temp_coord_frame.axis[XAXIS].x = temp_val;
    break;
  case AXIS_X_Y:
    temp_coord_frame.axis[XAXIS].y = temp_val;
    break;
  case AXIS_X_Z:
    temp_coord_frame.axis[XAXIS].z = temp_val;
    break;
  case AXIS_Y_X:
    temp_coord_frame.axis[YAXIS].x = temp_val;
    break;
  case AXIS_Y_Y:
    temp_coord_frame.axis[YAXIS].y = temp_val;
    break;
  case AXIS_Y_Z:
    temp_coord_frame.axis[YAXIS].z = temp_val;
    break;
  case AXIS_Z_X:
    temp_coord_frame.axis[ZAXIS].x = temp_val;
    break;
  case AXIS_Z_Y:
    temp_coord_frame.axis[ZAXIS].y = temp_val;
    break;
  case AXIS_Z_Z:
    temp_coord_frame.axis[ZAXIS].z = temp_val;
    break;
  default:
    break; /* do nothing */
  }
  

  /* recalculate the roi's offset based on the new dimensions/center/and axis */
  temp = realspace_alt_dim_to_base(temp_dim, temp_coord_frame);
  REALPOINT_MADD(-0.5,temp,1,temp_center,temp_coord_frame.offset);

  /* reset the far corner based on the new coord frame */
  roi_new_info->corner = realspace_alt_dim_to_alt(temp_dim, 
						  roi_new_info->coord_frame,
						  temp_coord_frame);

  /* and save any changes to the coord frame */
  roi_new_info->coord_frame = temp_coord_frame;

  /* now tell the roi_dialog that we've changed */
  roi_dialog =  gtk_object_get_data(GTK_OBJECT(widget), "roi_dialog");
  gnome_property_box_changed(GNOME_PROPERTY_BOX(roi_dialog));

  return;
}



/* function to change an roi's type */
void ui_roi_dialog_callbacks_change_type(GtkWidget * widget, gpointer data) {

  roi_t * roi_new_info = data;
  roi_type_t i_roi_type;
  GtkWidget * roi_dialog;

  /* figure out which menu item called me */
  i_roi_type = GPOINTER_TO_INT(gtk_object_get_data(GTK_OBJECT(widget),"roi_type"));
  roi_new_info->type = i_roi_type;  /* save the new roi_type until it's applied */

  /* now tell the roi_dialog that we've changed */
  roi_dialog =  gtk_object_get_data(GTK_OBJECT(widget), "roi_dialog");
  gnome_property_box_changed(GNOME_PROPERTY_BOX(roi_dialog));

  return;
}

/* function to change the grain size used to calculate an roi's statistics */
void ui_roi_dialog_callbacks_change_grain(GtkWidget * widget, gpointer data) {

  roi_t * roi_new_info = data;
  roi_grain_t i_grain;
  GtkWidget * roi_dialog;

  /* figure out which menu item called me */
  i_grain = GPOINTER_TO_INT(gtk_object_get_data(GTK_OBJECT(widget),"grain_size"));
  roi_new_info->grain = i_grain;  /* save the new grain size until it's applied */

  /* now tell the roi_dialog that we've changed */
  roi_dialog =  gtk_object_get_data(GTK_OBJECT(widget), "roi_dialog");
  gnome_property_box_changed(GNOME_PROPERTY_BOX(roi_dialog));

  return;
}









/* function called when rotating the roi around an axis */
void ui_roi_dialog_callbacks_change_axis(GtkAdjustment * adjustment, gpointer data) {

  ui_study_t * ui_study;
  roi_t * roi_new_info = data;
  view_t i_view;
  axis_t which_axis;
  floatpoint_t rotation;
  GtkWidget * roi_dialog;
  realpoint_t center, temp;

  /* we need the current view_axis so that we know what we're rotating around */
  ui_study = gtk_object_get_data(GTK_OBJECT(adjustment), "ui_study"); 

  /* saving the center, as we're rotating the roi around it's own center */
  center = roi_calculate_center(roi_new_info); 

  /* figure out which scale widget called me */
  i_view= GPOINTER_TO_INT(gtk_object_get_data(GTK_OBJECT(adjustment),"view"));
  rotation = (adjustment->value/180)*M_PI; /* get rotation in radians */
  which_axis = realspace_get_orthogonal_which_axis(i_view);
  roi_new_info->coord_frame.axis[XAXIS] = 
    realspace_rotate_on_axis(&roi_new_info->coord_frame.axis[XAXIS],
			     &study_coord_frame_axis(ui_study->study, which_axis),
			     rotation);
  roi_new_info->coord_frame.axis[YAXIS] = 
    realspace_rotate_on_axis(&roi_new_info->coord_frame.axis[YAXIS],
			     &study_coord_frame_axis(ui_study->study, which_axis),
			     rotation);
  roi_new_info->coord_frame.axis[ZAXIS] = 
    realspace_rotate_on_axis(&roi_new_info->coord_frame.axis[ZAXIS],
			     &study_coord_frame_axis(ui_study->study, which_axis),
			     rotation);
  realspace_make_orthonormal(roi_new_info->coord_frame.axis); /* orthonormalize*/

  
  /* recalculate the offset of this roi based on the center we stored */
  REALPOINT_CMULT(-0.5,roi_new_info->corner,temp);
  roi_new_info->coord_frame.offset = center;
  roi_new_info->coord_frame.offset = 
    realspace_alt_coord_to_base(temp, roi_new_info->coord_frame);

  /* return adjustment back to normal */
  adjustment->value = 0.0;
  gtk_adjustment_changed(adjustment);


  /* now tell the roi_dialog that we've changed */
  roi_dialog =  gtk_object_get_data(GTK_OBJECT(adjustment), "roi_dialog");
  ui_roi_dialog_set_axis_display(roi_dialog);
  gnome_property_box_changed(GNOME_PROPERTY_BOX(roi_dialog));

  return;
}

/* function to reset the roi's axis back to the default coords */
void ui_roi_dialog_callbacks_reset_axis(GtkWidget* widget, gpointer data) {

  roi_t * roi_new_info = data;
  axis_t i_axis;
  GtkWidget * roi_dialog;
  realpoint_t center, temp;

  /* saving the center, as we're rotating the roi around it's own center */
  center = roi_calculate_center(roi_new_info); 

  /* reset the axis */
  for (i_axis=0;i_axis<NUM_AXIS;i_axis++) {
    roi_new_info->coord_frame.axis[i_axis] = default_axis[i_axis];
  }

  /* recalculate the offset of this roi based on the center we stored */
  REALPOINT_CMULT(-0.5,roi_new_info->corner,temp);
  roi_new_info->coord_frame.offset = center;
  roi_new_info->coord_frame.offset = 
    realspace_alt_coord_to_base(temp, roi_new_info->coord_frame);

  /* now tell the roi_dialog that we've changed */
  roi_dialog =  gtk_object_get_data(GTK_OBJECT(widget), "roi_dialog");
  ui_roi_dialog_set_axis_display(roi_dialog);
  gnome_property_box_changed(GNOME_PROPERTY_BOX(roi_dialog));
  
  return;
}






/* function called when we hit the apply button */
void ui_roi_dialog_callbacks_apply(GtkWidget* widget, gint page_number, gpointer data) {
  
  ui_roi_list_t * roi_list_item = data;
  ui_study_t * ui_study;
  GdkPixmap * pixmap;
  guint8 spacing;
  roi_t * roi_new_info;
  view_t i_views;
  
  /* we'll apply all page changes at once */
  if (page_number != -1)
    return;

  /* get the new info for the roi */
  roi_new_info = gtk_object_get_data(GTK_OBJECT(roi_list_item->dialog),"roi_new_info");

  /* sanity check */
  if (roi_new_info == NULL) {
    g_printerr("%s: roi_new_info inappropriately null....\n", PACKAGE);
    return;
  }

  /* copy the new info on over */
  roi_set_name(roi_list_item->roi, roi_new_info->name);
  roi_list_item->roi->type = roi_new_info->type;
  roi_list_item->roi->coord_frame = roi_new_info->coord_frame;
  roi_list_item->roi->corner = roi_new_info->corner;
  roi_list_item->roi->parent = roi_free(roi_list_item->roi->parent);
  if (roi_new_info->parent != NULL) 
    roi_list_item->roi->parent = roi_copy(roi_new_info->parent);
  roi_list_item->roi->children = roi_list_free(roi_list_item->roi->children);
  if (roi_new_info->children != NULL) 
    roi_list_item->roi->children = roi_list_copy(roi_new_info->children);
  roi_list_item->roi->grain = roi_new_info->grain;

  /* apply any changes to the name of the widget */
  /* get the current pixmap and spacing in the line of the tree corresponding to this roi */
  gtk_ctree_node_get_pixtext(roi_list_item->tree, roi_list_item->tree_node, 0,
			     NULL, &spacing, &pixmap, NULL);
  /* reset the text in that tree line */
  gtk_ctree_node_set_pixtext(roi_list_item->tree, roi_list_item->tree_node, 0, 
			     roi_list_item->roi->name, spacing, pixmap, NULL);


  /* get a pointer to ui_study so we can redraw the roi's */
  ui_study = gtk_object_get_data(GTK_OBJECT(roi_list_item->dialog), "ui_study"); 

  /* redraw the roi */
  for (i_views=0;i_views<NUM_VIEWS;i_views++) {
    roi_list_item->canvas_roi[i_views] =
      ui_study_update_canvas_roi(ui_study,i_views,
				 roi_list_item->canvas_roi[i_views],
				 roi_list_item->roi);
  }

  return;
}

/* callback for the help button */
void ui_roi_dialog_callbacks_help(GnomePropertyBox *roi_dialog, gint page_number, gpointer data) {

  GnomeHelpMenuEntry help_ref={PACKAGE,"basics.html#ROI-DIALOG-HELP"};
  GnomeHelpMenuEntry help_ref_0 = {PACKAGE,"basics.html#ROI-DIALOG-HELP-BASIC"};
  GnomeHelpMenuEntry help_ref_1 = {PACKAGE,"basics.html#ROI-DIALOG-HELP-CENTER"};
  GnomeHelpMenuEntry help_ref_2 = {PACKAGE,"basics.html#ROI-DIALOG-HELP-DIMENSIONS"};
  GnomeHelpMenuEntry help_ref_3 = {PACKAGE,"basics.html#ROI-DIALOG-HELP-ROTATE"};


  switch (page_number) {
  case 0:
    gnome_help_display (0, &help_ref_0);
    break;
  case 1:
    gnome_help_display (0, &help_ref_1);
    break;
  case 2:
    gnome_help_display (0, &help_ref_2);
    break;
  case 3:
    gnome_help_display (0, &help_ref_3);
    break;
  default:
    gnome_help_display (0, &help_ref);
    break;
  }

  return;
}

/* function called to destroy the roi dialog */
void ui_roi_dialog_callbacks_close_event(GtkWidget* widget, gpointer data) {

  ui_roi_list_t * roi_list_item = data;
  roi_t * roi_new_info;

  /* trash collection */
  roi_new_info = gtk_object_get_data(GTK_OBJECT(widget), "roi_new_info");
  roi_new_info = roi_free(roi_new_info);

  /* destroy the widget */
  gtk_widget_destroy(GTK_WIDGET(roi_list_item->dialog));

  /* make sure the pointer in the roi_list_item is nulled */
  roi_list_item->dialog = NULL;

  return;
}


