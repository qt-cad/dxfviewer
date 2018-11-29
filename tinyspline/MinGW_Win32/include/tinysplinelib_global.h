#ifndef TINYSPLINELIB_GLOBAL_H
#define TINYSPLINELIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TINYSPLINELIB_LIBRARY)
#  define TINYSPLINE_EXPORT Q_DECL_EXPORT
#else
#  define TINYSPLINE_EXPORT Q_DECL_IMPORT
#endif


/******************************************************************************
*                                                                             *
* :: System Dependent Configuration                                           *
*                                                                             *
* The following configuration values must be adapted to your system. Some of  *
* them may be configured with preprocessor definitions. The default values    *
* should be fine for most modern hardware, such as x86, x86_64, and arm.      *
*                                                                             *
******************************************************************************/
#ifdef TINYSPLINE_FLOAT_PRECISION
typedef float tsReal;
#else
typedef double tsReal;
#endif

#define FLT_MAX_ABS_ERROR 1e-5
#define FLT_MAX_REL_ERROR 1e-8



/******************************************************************************
*                                                                             *
* :: Data Types                                                               *
*                                                                             *
* The following section defines all data types available in TinySpline.       *
*                                                                             *
******************************************************************************/
/**
 * Defines the error codes used by various functions to indicate different
 * types of errors. The following code snippet shows how to handle errors:
 *
 *      tsError err = ...                  // any function call here
 *      if (err) {                         // or use err != TS_SUCCESS
 *          printf("we got an error!");
 *          return err;                    // you may want to reuse error codes
 *      }
 */
typedef enum
{
        /* No error. */
        TS_SUCCESS = 0,

        /* Unable to allocate memory (using malloc/realloc). */
        TS_MALLOC = -1,

        /* The dimension of the control points are 0. */
        TS_DIM_ZERO = -2,

        /* Degree of spline >= number of control points. */
        TS_DEG_GE_NCTRLP = -3,

        /* Spline is not defined at knot value u. */
        TS_U_UNDEFINED = -4,

        /* Multiplicity of a knot (s) > order of spline.  */
        TS_MULTIPLICITY = -5,

        /* Decreasing knot vector. */
        TS_KNOTS_DECR = -6,

        /* Unexpected number of knots. */
        TS_NUM_KNOTS = -7,

        /* Spline is not derivable */
        TS_UNDERIVABLE = -8,

        /* len_control_points % dim != 0 */
        TS_LCTRLP_DIM_MISMATCH = -10,

        /* An error occurred while reading/writing a file. */
        TS_IO_ERROR = -11,

        /* An error occurred while parsing a serialized spline. */
        TS_PARSE_ERROR = -12
} tsError;

/**
 * Describes the structure of the knot vector of a NURBS/B-Spline. For more
 * details, see:
 *
 *     www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/B-spline/bspline-curve.html
 */
typedef enum
{
        /* Not available/Undefined. */
        TS_NONE = 0,

        /* Uniformly spaced knot vector. */
        TS_OPENED = 1,

        /* Uniformly spaced knot vector with clamped end knots. */
        TS_CLAMPED = 2,

        /* Uniformly spaced knot vector with s(u) = order of spline. */
        TS_BEZIERS = 3
} tsBSplineType;

/**
 * Represents a B-Spline which may also be used for NURBS, Bezier curves,
 * lines, and points. NURBS are represented by homogeneous coordinates where
 * the last component of a control point stores the weight of this control
 * point. Bezier curves are B-Splines with 'num_control_points == order' and a
 * clamped knot vector, therefore passing through their first and last control
 * point (a property which does not necessarily apply to B-Splines and NURBS).
 * If a Bezier curve consists of two control points only, we call it a line.
 * Points, ultimately, are just very short lines consisting of a single control
 * point.
 *
 * Two dimensional control points are stored as follows:
 *
 *     [x_0, y_0, x_1, y_1, ..., x_n-1, y_n-1]
 *
 * Tree dimensional control points are stored as follows:
 *
 *     [x_0, y_0, z_0, x_1, y_1, z_1, ..., x_n-1, y_n-1, z_n-1]
 *
 * ... and so on. NURBS are represented by homogeneous coordinates. For
 * example, let's say we have a NURBS in 2D consisting of 11 control points
 * where 'w_i' is the weight of the i'th control point. Then, the corresponding
 * control points are stored as follows:
 *
 *     [x_0*w_0, y_0*w_0, w_0, x_1*w_1, y_1*w_1, w_1, ..., x_10*w_10, y_10*w_10, w_10]
 */
typedef struct
{
    struct tsBSplineImpl *pImpl; /**< The actual implementation. */
} tsBSpline;

/**
 * Represents the output of De Boor's algorithm. De Boor's algorithm is used to
 * evaluate a spline at given knot value 'u' by iteratively computing a net of
 * intermediate values until the result is available:
 *
 *     https://en.wikipedia.org/wiki/De_Boor%27s_algorithm
 *     https://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/de-Boor.html
 *
 * All points of a net are stored in 'points'. The resulting point is the last
 * point in 'points' and, for the sake of convenience, may be accessed with
 * 'result':
 *
 *     tsDeBoorNet net = ...    // evaluate an arbitrary spline and store
 *                              // the resulting net of points in 'net'
 *
 *     ts_deboornet_result(...) // use 'result' to access the resulting point
 *
 * Two dimensional points are stored as follows:
 *
 *     [x_0, y_0, x_1, y_1, ..., x_n-1, y_n-1]
 *
 * Tree dimensional points are stored as follows:
 *
 *     [x_0, y_0, z_0, x_1, y_1, z_1, ..., x_n-1, y_n-1, z_n-1]
 *
 * ... and so on. The output also supports homogeneous coordinates described
 * above.
 *
 * There is a special case in which the evaluation of a knot value 'u' returns
 * two results instead of one. It occurs when the multiplicity of 'u' ( s(u) )
 * is equals to a spline's order, indicating that the spline is discontinuous
 * at 'u'. This is common practice for B-Splines (and NURBS) consisting of
 * connected Bezier curves where the endpoint of curve 'c_i' is equals to the
 * start point of curve 'c_i+1'. The end point of 'c_i' and the start point of
 * 'c_i+1' may still be completely different though, yielding to a spline
 * having a (real and visible) gap at 'u'. Consequently, De Boor's algorithm
 * must return two results if 's(u) == order' in order to give access to the
 * desired points.  In such case, 'points' stores only the two resulting points
 * (there is no net to calculate) and 'result' points to the *first* point in
 * 'points'. Since having (real) gaps in splines is unusual, both points in
 * 'points' are generally equals, making it easy to handle this special case by
 * accessing 'result' as already shown above for regular cases:
 *
 *     tsDeBoorNet net = ...    // evaluate a spline which is discontinuous at
 *                              // the given knot value, yielding to a net with
 *                              // two results
 *
 *     ts_deboornet_result(...) // use 'result' to access the resulting point
 *
 * However, you can access both points if necessary:
 *
 *     tsDeBoorNet net = ...    // evaluate a spline which is discontinuous at
 *                              // the given knot value, yielding to a net with
 *                              // two results
 *
 *     ts_deboornet_result(...)[0] ...       // stores the first component of
 *                                           // the first point
 *
 *     ts_deboornet_result(...)[dim(spline)] // stores the first component of
 *                                           // the second point
 *
 * As if this wasn't complicated enough, there is an exception for this special
 * case, yielding to exactly one result (just like the regular case) even if
 * 's(u) == order'. It occurs when 'u' is the lower or upper bound of a
 * spline's domain. For instance, if 'b' is a spline with domain [0, 1] and is
 * evaluated at 'u = 0' or 'u = 1' then 'result' is *always* a single point
 * regardless of the multiplicity of 'u'. Hence, handling this exception is
 * straightforward:
 *
 *     tsDeBoorNet net = ...    // evaluate a spline at the lower or upper
 *                              // bound of its domain, for instance, 0 or 1
 *
 *     ts_deboornet_result(...) // use 'result' to access the resulting point
 *
 * In summary, we have three different types of evaluation. 1) The regular case
 * returning all points of the net we used to calculate the resulting point. 2)
 * The special case returning exactly two points which is required for splines
 * with (real) gaps. 3) The exception of 2) returning exactly one point even if
 * 's(u) == order'. All in all this looks quite complex (and actually it is)
 * but for most applications you do not have to deal with it. Just use 'result'
 * to access the outcome of De Boor's algorithm.
 */
typedef struct
{
    struct tsDeBoorNetImpl *pImpl; /**< The actual implementation. */
} tsDeBoorNet;

#endif // TINYSPLINELIB_GLOBAL_H
