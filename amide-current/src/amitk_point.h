/* amitk_point.h
 *
 * Part of amide - Amide's a Medical Image Dataset Examiner
 * Copyright (C) 2000-2002 Andy Loening
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

#ifndef __AMITK_POINT_H__
#define __AMITK_POINT_H__

#include <glib-object.h>
#define _GNU_SOURCE /* use GNU extensions, i.e. NaN */
#include <math.h>
#include "amide.h"
#include "xml.h"

G_BEGIN_DECLS

typedef enum {
  AMITK_VIEW_TRANSVERSE, 
  AMITK_VIEW_CORONAL, 
  AMITK_VIEW_SAGITTAL, 
  AMITK_VIEW_NUM
} AmitkView;

typedef enum {
  AMITK_AXIS_X,
  AMITK_AXIS_Y,
  AMITK_AXIS_Z,
  AMITK_AXIS_NUM
} AmitkAxis;

typedef enum {
  AMITK_DIM_X,
  AMITK_DIM_Y,
  AMITK_DIM_Z,
  AMITK_DIM_T,
  AMITK_DIM_NUM
} AmitkDim;

#define	AMITK_TYPE_POINT		(amitk_point_get_type ())
#define AMITK_TYPE_VOXEL                (amitk_voxel_get_type ())
#define AMITK_TYPE_PIXEL                (amitk_pixel_get_type ())
#define AMITK_TYPE_CANVAS_POINT         (amitk_canvas_point_get_type ())
#define AMITK_TYPE_AXES                 (amitk_axes_get_type ())

typedef struct _AmitkPoint AmitkPoint;
typedef struct _AmitkVoxel AmitkVoxel;
typedef struct _AmitkPixel AmitkPixel;
typedef struct _AmitkCanvasPoint AmitkCanvasPoint;


/* realpoint is a point in real (float) 3D space */
struct _AmitkPoint {
  amide_real_t x;
  amide_real_t y;
  amide_real_t z;
};

GType              amitk_point_get_type (void);
AmitkPoint *       amitk_point_copy(const AmitkPoint * point);
void               amitk_point_free (AmitkPoint * point);
AmitkPoint         amitk_point_read_xml(xmlNodePtr nodes, gchar * descriptor);
void               amitk_point_write_xml(xmlNodePtr node, gchar * descriptor, AmitkPoint point);


/* voxel point is a point in voxel (integer) 4D space */
struct _AmitkVoxel {
  amide_intpoint_t x;
  amide_intpoint_t y;
  amide_intpoint_t z;
  amide_intpoint_t t;
};

GType              amitk_voxel_get_type (void);
AmitkVoxel *       amitk_voxel_copy(const AmitkVoxel * voxel);
void               amitk_voxel_free (AmitkVoxel * voxel);
AmitkVoxel         amitk_voxel_read_xml(xmlNodePtr nodes, gchar * descriptor);
void               amitk_voxel_write_xml(xmlNodePtr node, gchar * descriptor, AmitkVoxel voxel);


/* pixel point is a point in pixel (integer) 2D space */
struct _AmitkPixel {
  amide_intpoint_t x;
  amide_intpoint_t y;
};

GType              amitk_pixel_get_type (void);
AmitkPixel *       amitk_pixel_copy(const AmitkPixel * pixel);
void               amitk_pixel_free (AmitkPixel * pixel);


/* canvas point is a point in canvas (real) 2D space */
struct _AmitkCanvasPoint {
  amide_real_t x;
  amide_real_t y;
};

GType              amitk_canvas_point_get_type (void);
AmitkCanvasPoint * amitk_canvas_point_copy(const AmitkCanvasPoint * point);
void               amitk_canvas_point_free (AmitkCanvasPoint * point);

/* axes is an orthogonal set of axes in 3D space */
typedef AmitkPoint AmitkAxes[AMITK_AXIS_NUM];

GType              amitk_axes_get_type(void);
AmitkAxes *        amitk_axes_copy(const AmitkAxes * axes);
void               amitk_axes_free (AmitkAxes * axes);
void               amitk_axes_copy_in_place(AmitkAxes dest_axes, const AmitkAxes src_axes);
void               amitk_axes_transpose(AmitkAxes axes);
void               amitk_axes_mult(const AmitkAxes const_axes1, const AmitkAxes const_axes2, AmitkAxes dest_axes);
void               amitk_axes_make_orthonormal(AmitkAxes axes);
void               amitk_axes_rotate_on_vector(AmitkAxes axes, AmitkPoint vector, amide_real_t theta);
AmitkPoint         amitk_axes_get_orthogonal_axis(const AmitkAxes axes,
						  const AmitkView which_view,
						  const AmitkLayout which_layout,
						  const AmitkAxis which_axis);
AmitkPoint         amitk_axes_get_normal_axis    (const AmitkAxes axes,
						  const AmitkView which_view);

/* corners of a box */
typedef AmitkPoint AmitkCorners[2];

GType              amitk_corners_get_type (void);
void               amitk_corners_free (AmitkCorners * corners);
AmitkCorners *     amitk_corners_copy(const AmitkCorners * corners);




/* Constants */

/* some reference values to remember when setting epsilon 
DBL_EPSILON        2.2204460492503131e-16
SQRT_DBL_EPSILON   1.4901161193847656e-08
FLT_EPSILON        1.1920928955078125e-07
SQRT_FLT_EPSILON   3.4526698300124393e-04
*/


#define EPSILON 1.4901161193847656e-08 /* what's close enough to be equal.... */
#define SMALL_DISTANCE 0.01 /* in milimeter's, used as a lower limit on some dimensions */
#define SMALL_TIME 0.0001 /* in seconds, used as a lower limit on some times */
#define EMPTY 0.0


/* Macros */

/* returns the boolean value of fp1==fp2 (within a factor of EPSILON) */
#define REAL_EQUAL(x,y) (fabs(x-y)/MAX(MAX(fabs(x),fabs(y)),DBL_MIN) < EPSILON)

#define EQUAL_ZERO(fp1) (REAL_EQUAL((fp1), 0.0))

/* returns the boolean value of point1==point2 (within a factor of CLOSE) */
#define POINT_EQUAL(point1,point2) (REAL_EQUAL(((point1).x),((point2).x)) && \
		                    REAL_EQUAL(((point1).y),((point2).y)) && \
			            REAL_EQUAL(((point1).z),((point2).z)))

#define VOXEL_EQUAL(voxel1,voxel2) (((voxel1).x == (voxel2).x) && \
				    ((voxel1).y == (voxel2).y) && \
				    ((voxel1).z == (voxel2).z) && \
				    ((voxel1).t == (voxel2).t))

/* figure out the real point that corresponds to the voxel coordinates */
#define VOXEL_TO_POINT(vox, vox_size, real) (((real).x = (((amide_real_t) (vox).x)+0.5) * (vox_size).x), \
					     ((real).y = (((amide_real_t) (vox).y)+0.5) * (vox_size).y), \
					     ((real).z = (((amide_real_t) (vox).z)+0.5) * (vox_size).z))

#define POINT_TO_VOXEL(real, vox_size, frame, vox) (((vox).x = floor((real).x/(vox_size).x)), \
						    ((vox).y = floor((real).y/(vox_size).y)), \
						    ((vox).z = floor((real).z/(vox_size).z)), \
						    ((vox).t = (frame)))

/* returned the maximum of point1 */
#define POINT_MAX(point1) (MAX( MAX((point1).x, (point1).y), (point1).z))

/* returns point1 dot point2" */
#define POINT_DOT_PRODUCT(point1,point2) ((point1).x*(point2).x+(point1).y*(point2).y+(point1).z*(point2).z)

/* returns sqrt(point1 dot point1) */
#define POINT_MAGNITUDE(point) (sqrt(POINT_DOT_PRODUCT((point), (point))))

/* returns point2 = abs(point1)" */
#define POINT_ABS(point1,point2) ((point2).x = fabs((point1).x), \
				  (point2).y = fabs((point1).y), \
				  (point2).z = fabs((point1).z)) 

/* does point3=point1+point2 for realpoint structures */
#define POINT_ADD(point1,point2,point3) (((point3).x = (point1).x+(point2).x), \
					 ((point3).y = (point1).y+(point2).y), \
					 ((point3).z = (point1).z+(point2).z))

/* does point3=point1-point2 for realpoint structures */
#define POINT_SUB(point1,point2,point3) (((point3).x = (point1).x-(point2).x), \
					 ((point3).y = (point1).y-(point2).y), \
					 ((point3).z = (point1).z-(point2).z))

/* does point3=point1.*point2 for realpoint structures */
#define POINT_MULT(point1,point2,point3) (((point3).x = (point1).x*(point2).x), \
					  ((point3).y = (point1).y*(point2).y), \
					  ((point3).z = (point1).z*(point2).z))

/* does point3=point1./point2 for realpoint structures */
#define POINT_DIV(point1,point2,point3) (((point3).x = (point1).x/(point2).x), \
					 ((point3).y = (point1).y/(point2).y), \
					 ((point3).z = (point1).z/(point2).z))


/* does point3=fabs(point1-point2) for realpoint structures */
#define POINT_DIFF(point1,point2,point3) (((point3).x = fabs((point1).x-(point2).x)), \
					  ((point3).y = fabs((point1).y-(point2).y)), \
					  ((point3).z = fabs((point1).z-(point2).z)))

/* does point3=cm*point1 for realpoint structures */
#define POINT_CMULT(cm,point1,point3) (((point3).x = (cm)*(point1).x), \
				       ((point3).y = (cm)*(point1).y), \
				       ((point3).z = (cm)*(point1).z))

/* does point3=cm*point1+dm*point2 for realpoint structures */
#define POINT_MADD(cm,point1,dm,point2,point3) (((point3).x = cm*(point1).x+dm*(point2).x), \
						((point3).y = cm*(point1).y+dm*(point2).y), \
						((point3).z = cm*(point1).z+dm*(point2).z)) 

/* external functions */

/* note! the equivalent defines above are faster and should be used in any time critical spots */
inline AmitkPoint point_abs(const AmitkPoint point1);
inline AmitkPoint point_neg(const AmitkPoint point1);
inline AmitkPoint point_add(const AmitkPoint point1, const AmitkPoint point2);
inline AmitkPoint point_sub(const AmitkPoint point1, const AmitkPoint point2);
inline AmitkPoint point_mult(const AmitkPoint point1, const AmitkPoint point2);
inline AmitkPoint point_div(const AmitkPoint point1, const AmitkPoint point2);
inline AmitkPoint point_diff(const AmitkPoint point1, const AmitkPoint point2);
inline AmitkPoint point_cmult(const amide_real_t cmult, const AmitkPoint point1);
inline AmitkPoint point_cross_product(const AmitkPoint point1, const AmitkPoint point2);
inline amide_real_t point_dot_product(const AmitkPoint point1, const AmitkPoint point2);
inline amide_real_t point_mag(const AmitkPoint point1);
inline amide_real_t point_min_dim(const AmitkPoint point1);
inline amide_real_t point_max_dim(const AmitkPoint point1);

inline AmitkCanvasPoint canvas_point_diff(const AmitkCanvasPoint point1,const AmitkCanvasPoint point2);
inline AmitkCanvasPoint canvas_point_sub(const AmitkCanvasPoint point1,const AmitkCanvasPoint point2);
inline AmitkCanvasPoint canvas_point_add(const AmitkCanvasPoint point1,const AmitkCanvasPoint point2);
inline amide_real_t canvas_point_dot_product(const AmitkCanvasPoint point1, const AmitkCanvasPoint point2);
inline amide_real_t canvas_point_mag(const AmitkCanvasPoint point1);
AmitkPoint canvas_point_2_point(AmitkPoint volume_corner,
				gint width, gint height,
				gdouble x_offset,gdouble y_offset,
				AmitkCanvasPoint canvas_cpoint);
AmitkCanvasPoint point_2_canvas_point(AmitkPoint volume_corner,
				      gint width,gint height,
				      gdouble x_offset, gdouble y_offset,
				      AmitkPoint canvas_point);

inline AmitkVoxel voxel_add(const AmitkVoxel voxel1,const AmitkVoxel voxel2);
inline AmitkVoxel voxel_sub(const AmitkVoxel voxel1,const AmitkVoxel voxel2);
inline gboolean voxel_equal(const AmitkVoxel voxel1, const AmitkVoxel voxel2);
inline amide_real_t voxel_max_dim(const AmitkVoxel voxel1);
void voxel_print(gchar * message, const AmitkVoxel voxel);
amide_intpoint_t voxel_get_dim(const AmitkVoxel voxel,
				const AmitkDim which_dim);
void voxel_set_dim(AmitkVoxel * voxel,
		   const AmitkDim which_dim,
		   amide_intpoint_t value);

inline gboolean point_in_box(const AmitkPoint p,
			     const AmitkPoint box_corner);
inline gboolean point_in_elliptic_cylinder(const AmitkPoint p,
					   const AmitkPoint center,
					   const amide_real_t height,
					   const AmitkPoint radius);
inline gboolean point_in_ellipsoid(const AmitkPoint p,
			    const AmitkPoint center,
			    const AmitkPoint radius);
void point_print(gchar * message, const AmitkPoint point);
AmitkPoint point_rotate_on_vector(const AmitkPoint in,
				const AmitkPoint vector,
				const amide_real_t theta);
amide_real_t point_get_component(const AmitkPoint point,
				 const AmitkAxis which_axis);

extern const AmitkPoint zero_point;
extern const AmitkPoint one_point;
extern const AmitkPoint ten_point;
extern const AmitkVoxel zero_voxel;
extern const AmitkVoxel one_voxel;

extern const AmitkAxes base_axes;

const gchar * amitk_view_get_name(const AmitkView view);
const gchar * amitk_dim_get_name(const AmitkDim dim);
const gchar * amitk_axis_get_name(const AmitkAxis axis);


G_END_DECLS

#endif /* __AMITK_POINT_H__ */
