/* amitk_canvas.h
 *
 * Part of amide - Amide's a Medical Image Dataset Examiner
 * Copyright (C) 2002-2003 Andy Loening
 *
 * Author: Andy Loening <loening@alum.mit.edu>
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


#ifndef __AMITK_CANVAS_H__
#define __AMITK_CANVAS_H__

/* includes we always need with this widget */
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <libgnomecanvas/libgnomecanvas.h>
#include "amitk_study.h"

G_BEGIN_DECLS

#define AMITK_TYPE_CANVAS            (amitk_canvas_get_type ())
#define AMITK_CANVAS(obj)            (GTK_CHECK_CAST ((obj), AMITK_TYPE_CANVAS, AmitkCanvas))
#define AMITK_CANVAS_CLASS(klass)    (GTK_CHECK_CLASS_CAST ((klass), AMITK_TYPE_CANVAS, AmitkCanvasClass))
#define AMITK_IS_CANVAS(obj)         (GTK_CHECK_TYPE ((obj), AMITK_TYPE_CANVAS))
#define AMITK_IS_CANVAS_CLASS(klass) (GTK_CHECK_CLASS_TYPE ((klass), AMITK_TYPE_CANVAS))

#define AMITK_CANVAS_VIEW(obj)       (AMITK_CANVAS(obj)->view)
#define AMITK_CANVAS_VIEW_MODE(obj)  (AMITK_CANVAS(obj)->view_mode)
#define AMITK_CANVAS_PIXBUF(obj)     (AMITK_CANVAS(obj)->pixbuf)


typedef enum {
  AMITK_CANVAS_TARGET_ACTION_HIDE,
  AMITK_CANVAS_TARGET_ACTION_SHOW,
  AMITK_CANVAS_TARGET_ACTION_LEAVE
} AmitkCanvasTargetAction;

typedef struct _AmitkCanvas             AmitkCanvas;
typedef struct _AmitkCanvasClass        AmitkCanvasClass;


struct _AmitkCanvas
{
  GtkVBox vbox;

  GtkWidget * canvas;
  GtkWidget * label;
  GtkWidget * scrollbar;
  GtkObject * scrollbar_adjustment;
  GnomeCanvasItem * arrows[4];
  gboolean with_arrows;

  AmitkVolume * volume; /* the volume that this canvas slice displays */
  AmitkPoint center; /* in base coordinate space */

  AmitkView view;
  AmitkViewMode view_mode;
  AmitkLayout layout;
  gint roi_width;
  GdkLineStyle line_style;
  AmitkObject * active_object;
  gboolean maintain_size;
  gint target_empty_area;

  GList * slices;
  GList * slice_cache;
  gint pixbuf_width, pixbuf_height;
  GnomeCanvasItem * image;
  GdkPixbuf * pixbuf;

  AmitkStudy * study;
  GList * undrawn_rois;
  GList * object_items;

  GList * cursor_stack;

  guint next_update;
  guint idle_handler_id;
  GList * next_update_objects;

  /* target stuff */
  GnomeCanvasItem * target[8];
  AmitkCanvasTargetAction next_target_action;
  AmitkPoint next_target_center;
  amide_real_t next_target_thickness;

};

struct _AmitkCanvasClass
{
  GtkVBoxClass parent_class;
  
  void (* help_event)                (AmitkCanvas *Canvas,
				      AmitkHelpInfo which_help,
				      AmitkPoint *position,
				      amide_data_t value);
  void (* view_changing)             (AmitkCanvas *Canvas,
				      AmitkPoint *position,
				      amide_real_t thickness);
  void (* view_changed)              (AmitkCanvas *Canvas,
				      AmitkPoint *position,
				      amide_real_t thickness);
  void (* erase_volume)              (AmitkCanvas *Canvas,
				      AmitkRoi *roi,
				      gboolean outside);
  void (* new_object)                (AmitkCanvas *Canvas,
				      AmitkObject * parent,
				      AmitkObjectType type,
				      AmitkPoint *position);
};  


GType         amitk_canvas_get_type             (void);
GtkWidget *   amitk_canvas_new                  (AmitkView view, 
						 AmitkViewMode view_mode,
						 AmitkLayout layout, 
						 GdkLineStyle line_style,
						 gint roi_width,
						 gboolean with_arrows,
						 gboolean maintain_size,
						 gint target_empty_area);
void          amitk_canvas_set_study            (AmitkCanvas * canvas, 
						 AmitkStudy * study);
void          amitk_canvas_set_layout           (AmitkCanvas * canvas, 
						 AmitkLayout new_layout);
void          amitk_canvas_set_general_properties(AmitkCanvas * canvas, 
						  gboolean maintain_size);
void          amitk_canvas_set_target_properties(AmitkCanvas * canvas, 
						 gint target_empty_area);
void          amitk_canvas_set_active_object    (AmitkCanvas * canvas, 
						 AmitkObject * active_object);
void          amitk_canvas_set_line_style       (AmitkCanvas * canvas, 
						 GdkLineStyle new_line_style);
void          amitk_canvas_set_roi_width        (AmitkCanvas * canvas, 
						 gint new_roi_width);
void          amitk_canvas_update_target        (AmitkCanvas * canvas, 
						 AmitkCanvasTargetAction action, 
						 AmitkPoint center, 
						 amide_real_t thickness);

gint          amitk_canvas_get_width            (AmitkCanvas * canvas);
gint          amitk_canvas_get_height           (AmitkCanvas * canvas);

G_END_DECLS


#endif /* __AMITK_CANVAS_H__ */

