/** @file */

#ifndef TINYSPLINE_H
#define	TINYSPLINE_H
#include "tinysplinelib_global.h"
#ifdef	__cplusplus
extern "C" {
#endif



/******************************************************************************
*                                                                             *
* :: Field Access Functions                                                   *
*                                                                             *
* The following section contains getter and setter functions for the internal *
* state of the structs listed above.                                          *
*                                                                             *
******************************************************************************/
/**
 * Returns the degree of \p spline.
 *
 * @param spline
 * 	The spline whose degree is read.
 * @return
 * 	The degree of \p spline.
 */
size_t ts_bspline_degree(const tsBSpline *spline);

/**
 * Sets the degree of \p spline.
 *
 * @param spline
 * 	The spline whose degree is set.
 * @param deg
 * 	The degree to be set.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_DEG_GE_NCTRLP
 * 	If \p degree >= ts_bspline_get_control_points(spline).
 */
tsError ts_bspline_set_degree(tsBSpline *spline, size_t deg);

/**
 * Returns the order (degree + 1) of \p spline.
 *
 * @param spline
 * 	The spline whose order is read.
 * @return
 * 	The order of \p spline.
 */
size_t ts_bspline_order(const tsBSpline *spline);

/**
 * Sets the order (degree + 1) of \p spline.
 *
 * @param spline
 * 	The spline whose order is set.
 * @param order
 * 	The order to be set.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_DEG_GE_NCTRLP
 * 	If \p order > ts_bspline_get_control_points(spline) or if \p order == 0
 * 	( due to the underflow resulting from: order - 1 => 0 - 1 => INT_MAX
 * 	which always is >= ts_bspline_get_control_points(spline) ).
 */
tsError ts_bspline_set_order(tsBSpline *spline, size_t order);

/**
 * Returns the dimension of \p spline. The dimension of a spline describes the
 * number of components for each point in ts_bspline_get_control_points(spline).
 * One-dimensional splines are possible, albeit their benefit might be
 * questionable.
 *
 * @param spline
 * 	The spline whose dimension is read.
 * @return
 * 	The dimension of \p spline.
 */
size_t ts_bspline_dimension(const tsBSpline *spline);

/**
 * Sets the dimension of \p spline. The following conditions must be satisfied:
 *
 * 	(1) dim >= 1
 * 	(2) len_control_points % dim == 0
 *
 * with _len_control_points_ being the length of the control point array of \p
 * spline. The dimension of a spline describes the number of components for
 * each point in ts_bspline_get_control_points(spline). One-dimensional splines
 * are possible, albeit their benefit might be questionable.
 *
 * @param spline
 * 	The spline whose dimension is set.
 * @param dim
 * 	The dimension to be set.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_DIM_ZERO
 * 	If \p dimension == 0.
 * @return TS_LCTRLP_DIM_MISMATCH
 * 	If len_control_points % \p dim != 0
 */
tsError ts_bspline_set_dimension(tsBSpline *spline, size_t dim);

/**
 * Returns the length of the control point array of \p spline.
 *
 * @param spline
 * 	The spline with its control point array whose length is read.
 * @return
 * 	The length of the control point array of \p spline.
 */
size_t ts_bspline_len_control_points(const tsBSpline *spline);

/**
 * Returns the number of control points of \p spline.
 *
 * @param spline
 * 	The spline whose number of control points is read.
 * @return
 * 	The number of control points of \p spline.
 */
size_t ts_bspline_num_control_points(const tsBSpline *spline);

/**
 * Returns the size of the control point array of \p spline. This function may
 * be useful when copying control points using memcpy or memmove.
 *
 * @param spline
 * 	The spline with its control point array whose size is read.
 * @return
 * 	The size of the control point array of \p spline.
 */
size_t ts_bspline_sof_control_points(const tsBSpline *spline);

/**
 * Returns a deep copy of the control points of \p spline.
 *
 * @param spline
 * 	The spline whose control points are read.
 * @param ctrlp
 * 	The output array.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_control_points(const tsBSpline *spline, tsReal **ctrlp);

/**
 * Sets the control points of \p spline. Creates a deep copy of \p ctrlp.
 *
 * @param spline
 * 	The spline whose control points are set.
 * @param ctrlp
 * 	The values to deep copy.
 * @return TS_SUCCESS
 * 	On success.
 */
tsError ts_bspline_set_control_points(tsBSpline *spline, const tsReal *ctrlp);

/**
 * Returns the number of knots of \p spline.
 *
 * @param spline
 * 	The spline whose number of knots is read.
 * @return
 * 	The number of knots of \p spline.
 */
size_t ts_bspline_num_knots(const tsBSpline *spline);

/**
 * Returns the size of the knot array of \p spline. This function may be useful
 * when copying knots using memcpy or memmove.
 *
 * @param spline
 * 	The spline with its knot array whose size is read.
 * @return TS_SUCCESS
 * 	The size of the knot array of \p spline.
 */
size_t ts_bspline_sof_knots(const tsBSpline *spline);

/**
 * Returns a deep copy of the knots of \p spline.
 *
 * @param spline
 * 	The spline whose knots are read.
 * @param knots
 * 	The output array.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_knots(const tsBSpline *spline, tsReal **knots);

/**
 * Sets the knots of \p spline. Creates a deep copy of \p knots.
 *
 * @param spline
 * 	The spline whose knots are set.
 * @param knots
 * 	The values to deep copy.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_KNOTS_DECR
 * 	If the knot vector is decreasing.
 * @return TS_MULTIPLICITY
 * 	If there is a knot with multiplicity > order
 */
tsError ts_bspline_set_knots(tsBSpline *spline, const tsReal *knots);

/* ------------------------------------------------------------------------- */

/**
 * Returns the knot (sometimes also called 'u' or 't') of \p net.
 *
 * @param net
 * 	The net whose knot is read.
 * @return
 * 	The knot of \p net.
 */
tsReal ts_deboornet_knot(const tsDeBoorNet *net);

/**
 * Returns the index [u_k, u_k+1) with u being the knot of \p net.
 *
 * @param net
 * 	The net whose index is read.
 * @return
 * 	The index [u_k, u_k+1) with u being the knot of \p net.
 */
size_t ts_deboornet_index(const tsDeBoorNet *net);

/**
 * Returns the multiplicity of the knot of \p net.
 *
 * @param net
 * 	The net whose multiplicity is read.
 * @return
 * 	The multiplicity of the knot of \p net.
 */
size_t ts_deboornet_multiplicity(const tsDeBoorNet *net);

/**
 * Returns the number of insertion that were necessary to evaluate the knot of
 * \p net.
 *
 * @param net
 * 	The net with its knot whose number of insertions is read.
 * @return
 * 	The number of insertions that were necessary to evaluate the knot of \p
 * 	net.
 */
size_t ts_deboornet_num_insertions(const tsDeBoorNet *net);

/**
 * Returns the dimension of \p net. The dimension of a net describes the number
 * of components for each point in ts_bspline_get_points(spline).
 * One-dimensional nets are possible, albeit their benefit might be
 * questionable.
 *
 * @param net
 * 	The net whose dimension is read.
 * @return
 * 	The dimension of \p net.
 */
size_t ts_deboornet_dimension(const tsDeBoorNet *net);

/**
 * Returns the length of the point array of \p net.
 *
 * @param net
 * 	The net with its point array whose length is read.
 * @return
 * 	The length of the point array of \p net.
 */
size_t ts_deboornet_len_points(const tsDeBoorNet *net);

/**
 * Returns the number of points of \p net.
 *
 * @param net
 * 	The net whose number of points is read.
 * @return
 * 	The number of points of \p net.
 */
size_t ts_deboornet_num_points(const tsDeBoorNet *net);

/**
 * Returns the size of the point array of \p net. This function may be useful
 * when copying points using memcpy or memmove.
 *
 * @param net
 * 	The net with its point array whose size is read.
 * @return
 * 	The size of the point array of \p net.
 */
size_t ts_deboornet_sof_points(const tsDeBoorNet *net);

/**
 * Returns a deep copy of the points of \p net.
 *
 * @param net
 * 	The net whose points is read.
 * @param points
 * 	The output array.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_deboornet_points(const tsDeBoorNet *net, tsReal **points);

/**
 * Returns the length of the result array of \p net.
 *
 * @param net
 * 	The net with its result array whose length is read.
 * @return
 * 	The length of the result array of \p net.
 */
size_t ts_deboornet_len_result(const tsDeBoorNet *net);

/**
 * Returns the number of points in the result array of \p net
 * (1 <= num_result <= 2).
 *
 * @param net
 * 	The net with its result array whose number of points is read.
 * @return
 * 	The number of points in the result array of \p net.
 */
size_t ts_deboornet_num_result(const tsDeBoorNet *net);

/**
 * Returns the size of the result array of \p net. This function may be useful
 * when copying results using memcpy or memmove.
 *
 * @param net
 * 	The net with its result array whose size is read.
 * @return TS_SUCCESS
 * 	The size of the result array of \p net.
 */
size_t ts_deboornet_sof_result(const tsDeBoorNet *net);

/**
 * Returns a deep copy of the result of \p net.
 *
 * @param net
 * 	The net whose result is read.
 * @param result
 * 	The output array.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_deboornet_result(const tsDeBoorNet *net, tsReal **result);



/******************************************************************************
*                                                                             *
* :: Constructors, Destructors, Copy, and Move Functions                      *
*                                                                             *
* The following section contains functions to create and delete instances of  *
* the data types listed above. Additionally, each data type has a copy and    *
* move function.                                                              *
*                                                                             *
******************************************************************************/
/**
 * Creates a new spline and stores the result in \p \_spline\_.
 *
 * @param num_control_points
 * 	The number of control points of \p \_spline\_.
 * @param dimension
 * 	The dimension of each control point of \p \_spline\_.
 * @param degree
 * 	The degree of \p \_spline\_.
 * @param type
 * 	How to setup the knot vector of \p \_spline\_.
 * @param \_spline\_
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_DIM_ZERO
 * 	If \p degree == 0.
 * @return TS_DEG_GE_NCTRLP
 * 	If \p degree >= \p num_control_points.
 * @return TS_NUM_KNOTS
 * 	If \p type == ::TS_BEZIERS and
 * 	(\p num_control_points % \p degree + 1) != 0.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_new(size_t num_control_points, size_t dimension,
       size_t degree, tsBSplineType type, tsBSpline *_spline_);

/**
 * Creates a deep copy of \p original and stores the copied values in
 * \p \_copy\_. Does nothing, if \p original == \p \_copy\_.
 *
 * @param original
 * 	The spline to deep copy.
 * @param \_copy\_
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_copy(const tsBSpline *original, tsBSpline *_copy_);

/**
 * Moves the ownership of the data of \p from to \p \_to\_. After calling this
 * function, \p from points to NULL. Does nothing, if \p from == \p \_to\_.
 * 
 * @param from
 * 	The spline whose values are moved to \p \_to\_.
 * @param \_to\_
 * 	The output parameter.
 */
void ts_bspline_move(tsBSpline *from, tsBSpline *_to_);

/**
 * Frees the dynamically allocated memory of \p \_spline\_. After calling this
 * function, \p \_spline\_ points to NULL.
 * 
 * @param \_spline\_
 * 	The spline to free.
 */
void ts_bspline_free(tsBSpline *_spline_);

/* ------------------------------------------------------------------------- */

/**
 * Creates a deep copy of \p original and stores the copied values in
 * \p \_copy\_. Does nothing, if \p original == \p \_copy\_.
 *
 * @param original
 * 	The net to deep copy.
 * @param \_copy\_
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_deboornet_copy(const tsDeBoorNet *original, tsDeBoorNet *_copy_);

/**
 * Moves the ownership of the data of \p from to \p \_to\_. After calling this
 * function, \p from points to NULL. Does nothing, if \p from == \p \_to\_.
 * 
 * @param from
 * 	The net whose values are moved to \p \_to\_.
 * @param \_to\_
 * 	The output parameter.
 */
void ts_deboornet_move(tsDeBoorNet *from, tsDeBoorNet *_to_);

/**
 * Frees the dynamically allocated memory of \p \_net\_. After calling this
 * function, \p \_net\_ points to NULL.
 * 
 * @param \_net\_
 * 	The net to free.
 */
void ts_deboornet_free(tsDeBoorNet *_net_);



/******************************************************************************
*                                                                             *
* :: Interpolation and Approximation Functions                                *
*                                                                             *
* The following section contains functions to interpolate and approximate     *
* arbitrary splines.                                                          *
*                                                                             *
******************************************************************************/
/**
 * Performs a cubic spline interpolation using the thomas algorithm, see:
 * 
 *     https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
 *     http://www.math.ucla.edu/~baker/149.1.02w/handouts/dd_splines.pdf
 *     http://www.bakoma-tex.com/doc/generic/pst-bspline/pst-bspline-doc.pdf
 *
 * The resulting spline is a sequence of bezier curves connecting each point
 * in \p points. Each bezier curve _b_ is of degree 3 with \p dim being the
 * dimension of the each control point in _b_. The total number of control
 * points is (\p n - 1) * 4.
 *
 * On error, all values of \p \_spline\_ are set to 0/NULL.
 *
 * Note: \p n is the number of points in \p points and not the length of
 * \p points. For instance, the follwing point vector yields to \p n = 4 and
 * \p dim = 2:
 * 
 *     [x0, y0, x1, y1, x2, y2, x3, y3]
 *
 * @param points
 * 	The points to interpolate.
 * @param n
 * 	The number of points in \p points.
 * @param dim
 * 	The dimension of each control point in \p \_spline\_.
 * @param \_spline\_
 * 	The output parameter storing the result of this function.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_DIM_ZERO
 * 	If \p dim == 0.
 * @return TS_DEG_GE_NCTRLP
 * 	If \p n < 2.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_interpolate_cubic(const tsReal *points, size_t n,
	size_t dim, tsBSpline *_spline_);



/******************************************************************************
*                                                                             *
* :: Query Functions                                                          *
*                                                                             *
* The following section contains functions to query splines.                  *
*                                                                             *
******************************************************************************/
/**
 * Evaluates \p spline at knot value \p u and stores the result in
 * \p \_deBoorNet\_.
 *
 * @param spline
 * 	The spline to evaluate.
 * @param u
 * 	The knot value to evaluate.
 * @param \_deBoorNet\_
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_U_UNDEFINED
 * 	If \p spline is not defined at knot value \p u.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_eval(const tsBSpline *spline, tsReal u,
	tsDeBoorNet *_deBoorNet_);



/******************************************************************************
*                                                                             *
* :: Transformation functions                                                 *
*                                                                             *
* TinySpline is a library focusing on transformations. That is, most          *
* functions are used to transform splines by modifying their state, e.g.,     *
* their number of control points, their degree, and so on. Accordingly, each  *
* transformation functions specifies an input and output parameter (along     *
* with the other parameters required to calculate the actual transformation). *
* By passing a different pointer to the output parameter, the transformation  *
* result is calculated and stored without changing the state of the input.    *
* This is in particular useful when dealing with errors as the original state *
* will never be modified. For instance, let's have a look at the following    *
* code snippet:                                                               *
*                                                                             *
*     tsBSpline in = ...    // an arbitrary spline                            *
*     tsBSpline out;        // result of transformation                       *
*                                                                             *
*     // Subdivide 'in' into sequence of bezier curves and store the result   *
*     // in 'out'. Does not change 'in' in any way.                           *
*     tsError err = ts_bspline_to_beziers(&in, &out);                         *
*     if (err != TS_SUCCESS) {                                                *
*         // fortunately, 'in' has not been changed                           *
*     }                                                                       *
*                                                                             *
* Even if 'ts_bspline_to_beziers' fails, the state of 'in' has not been       *
* changed allowing you to handle the error properly.                          *
*                                                                             *
* Unless stated otherwise, the order of the parameters for transformation     *
* functions is:                                                               *
*                                                                             *
*     function(input, [additional_input], output, [additional_output])        *
*                                                                             *
* 'additional_input' are parameters required to calculate the actual          *
* transformation. 'additional_output' are parameters storing further result.  *
*                                                                             *
* Note: None of TinySpline's transformation functions frees the memory of the *
*       output parameter. Thus, when using the same output parameter multiple *
*       times, make sure to free memory before each call. Otherwise, you will *
*       have a bad time with memory leaks:                                    *
*                                                                             *
*     tsBSpline in = ...                  // an arbitrary spline              *
*     tsBSpline out;                      // result of transformations        *
*                                                                             *
*     ts_bspline_to_beziers(&in, &out);   // first transformation             *
*     ...                                 // some code                        *
*     ts_bspline_free(&out);              // avoid memory leak.               *
*     ts_bspline_buckle(&in, &out);       // next transformation              *
*                                                                             *
* If you want to modify your input directly without having a separate output, *
* pass it as input and output at once:                                        *
*                                                                             *
*     tsBSpline s = ...                       // an arbitrary spline          *
*     tsReal *knots = ...                     // a knot vector                *
*                                                                             *
*     ts_bspline_set_knots(&s, knots, &s);    // copy 'knots' into 's'        *
*                                                                             *
* Note: If a transformation function fails *and* input != output, all fields  *
*       of the output parameter are set to 0/NULL. If input == output, your   *
*       input may have an invalid state in case of errors.                    *
*                                                                             *
******************************************************************************/
/**
 * Returns the \p n'th derivative of \p spline and stores the result in
 * \p \_derivative\_. Creates a deep copy of \p spline, if
 * \p spline != \p \_result\_. For more details, see:
 * 
 *     http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/B-spline/bspline-derv.html
 *
 * The derivative of a spline _s_ of degree _d_ (_d_ > 0) with _m_ control
 * points and _n_ knots is another spline _s'_ of degree _d-1_ with _m-1_
 * control points and _n-2_ knots, defined over _s_ as:
 * 
 * \f{eqnarray*}{
 *   s'(u) &=& \sum_{i=0}^{n-1} N_{i+1,p-1}(u) *
 * 		(P_{i+1} - P_{i}) * p / (u_{i+p+1}-u_{i+1}) \\
 *         &=& \sum_{i=1}^{n} N_{i,p-1}(u) *
 * 		(P_{i} - P_{i-1}) * p / (u_{i+p}-u_{i})
 * \f}
 * 
 * If _s_ has a clamped knot vector, it can be shown that:
 * 
 * \f{eqnarray*}{
 *   s'(u) &=& \sum_{i=0}^{n-1} N_{i,p-1}(u) *
 * 		(P_{i+1} - P_{i}) * p / (u_{i+p+1}-u_{i+1})
 * \f}
 * 
 * where the multiplicity of the first and the last knot value _u_ is _p_
 * rather than _p+1_. The derivative of a point (degree == 0) is another point
 * with coordinates 0.
 *
 * @param spline
 * 	The spline to derive.
 * @param \_derivative\_
 *	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_UNDERIVABLE
 * 	If the multiplicity of an internal knot of \p spline is greater than
 * 	the degree of \p spline. NOTE: This will be fixed in the future.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_derive(const tsBSpline *spline, size_t n,
	tsBSpline *_derivative_);

/**
 * Fills the knot vector of \p spline according to \p type with minimum knot
 * value \p min to maximum knot value \p max and stores the result in
 * \p \_result\_. Creates a deep copy of \p spline, if
 * \p spline != \p \_result\_.
 *
 * @param spline
 * 	The spline whose knot vector is filled according to \p type with
 * 	minimum knot value \p min and maximum knot value \p max.
 * @param type
 * 	How to fill the knot vector.
 * @param min
 * 	The minimum value of the knot vector.
 * @param max
 * 	The maximum value of the knot vector.
 * @param \_result\_
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_NUM_KNOTS
 * 	If \p type == TS_BEZIERS and
 * 	\p spline->n_knots % \p spline->order != 0.
 * @return TS_KNOTS_DECR
 * 	If \p min >= \p max. (::ts_fequals is used to determine whether
 * 	\p min == \p max).
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_fill_knots(const tsBSpline *spline, tsBSplineType type,
	tsReal min, tsReal max, tsBSpline *_result_);

/**
 * Inserts the knot value \p u \p n times into \p spline and stores the result
 * in \p \_result\_. Creates a deep copy of \p spline, if
 * \p spline != \p \_result\_.
 * 
 * @param spline
 * 	The spline whose knot vector is extended.
 * @param u
 * 	The knot value to insert.
 * @param n
 * 	How many times \p u should be inserted.
 * @param \_result\_
 * 	The output parameter.
 * @param \_k\_
 * 	Stores the last index of \p u in \p \_result\_.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_insert_knot(const tsBSpline *spline, tsReal u, size_t n,
	tsBSpline *_result_, size_t *_k_);

/**
 * Resizes \p spline by \p num_control_points and stores the result in
 * \p \_resized\_. Creates a deep copy of \p spline, if
 * \p spline != \p \_result\_. If \p back != 0 \p spline is resized at the
 * end. If \p back == 0 \p spline is resized at front.
 *
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_DEG_GE_NCTRLP
 * 	If the degree of \p \_resized\_ would be >= the number of control
 * 	points of \p \_resized\_.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_resize(const tsBSpline *spline, int num_control_points,
	int back, tsBSpline *_resized_);

/**
 * Splits \p spline at knot value \p u and stores the result in \p \_split\_.
 * That is, \p u is inserted _n_ times such that the multiplicity of \p u in
 * \p spline is equal to the spline's order. Creates a deep copy of \p spline,
 * if \p spline != \p \_split\_.
 * 
 * @param spline
 * 	The spline to split.
 * @param u
 * 	The split point.
 * @param \_split\_
 * 	The output parameter.
 * @param \_k\_
 * 	Stores the last index of \p u in \p \_split\_.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_U_UNDEFINED
 * 	If \p spline is not defined at knot value \p u.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_split(const tsBSpline *spline, tsReal u, tsBSpline *_split_,
	size_t *_k_);

/**
 * Buckles \p spline by \p b and stores the result in \p \_buckled\_. Creates
 * a deep copy of \p spline, if \p spline != \p \_buckled\_.
 *
 * This function is based on:
 * 
 *      Holten, Danny. "Hierarchical edge bundles: Visualization of adjacency
 *      relations in hierarchical data." Visualization and Computer Graphics,
 *      IEEE Transactions on 12.5 (2006): 741-748.
 * 
 * Holten calls it "straightening" (page 744, equation 1).
 *
 * Usually, the range of \p b is: 0.0 <= \p b <= 1.0 with 0 yielding to a line
 * connecting the first and the last control point (no buckle) and 1 keeping
 * the original shape (maximum buckle). If \b < 0 or \b > 1 the behaviour is
 * undefined, though, it will not result in an error.
 *
 * @param spline
 * 	The spline to buckle.
 * @param b
 * 	The buckle factor (usually 0.0 <= \p b <= 1.0).
 * @param \_buckled\_
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_buckle(const tsBSpline *spline, tsReal b,
	tsBSpline *_buckled_);

/**
 * Subdivides \p spline into a sequence of Bezier curves by splitting it at
 * each internal knot value. Creates a deep copy of \p spline, if
 * \p spline != \p \_beziers\_.
 * 
 * @param spline
 * 	The spline to subdivide.
 * @param \_beziers\_
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_to_beziers(const tsBSpline *spline, tsBSpline *_beziers_);



/******************************************************************************
*                                                                             *
* :: Serialization and Persistence Functions                                  *
*                                                                             *
* The following section contains functions to serialize and persist the data  *
* types listed above.                                                         *
*                                                                             *
******************************************************************************/
/**
 * Serializes \p spline to a null-terminated JSON string and stores the result
 * in \p \_json\_.
 *
 * @param spline
 * 	The spline to serialize.
 * @param json
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_to_json(const tsBSpline *spline, char **_json_);

/**
 * Parses \p json and stores the result in \p \_spline\_.
 *
 * @param json
 * 	The JSON string to parse.
 * @param _spline_
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_PARSE_ERROR
 * 	If an error occurred while parsing \p json.
 * @return TS_DIM_ZERO
 * 	If the dimension is 0.
 * @return TS_LCTRLP_DIM_MISMATCH
 * 	If the length of the control point vector modulo dimension is not 0.
 * @return TS_DEG_GE_NCTRLP
 * 	If the degree is greater or equals to the number of control points.
 * @return TS_NUM_KNOTS
 * 	If the number of knots stored in \p json does not match to the number
 * 	of control points and the degree of the spline.
 * @return TS_KNOTS_DECR
 * 	If the knot vector is decreasing.
 * @return TS_MULTIPLICITY
 * 	If there is a knot with multiplicity greater than order.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_from_json(const char *json, tsBSpline *_spline_);

/**
 * Saves \p spline as JSON ASCII file.
 *
 * @param spline
 * 	The spline to save.
 * @param path
 * 	Path of the JSON file.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_IO_ERROR
 * 	If an error occurred while saving \p spline.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_save_json(const tsBSpline *spline, const char *path);

/**
 * Loads the contents of \p path and stores the result in \p \_spline\_.
 *
 * @param path
 * 	Path of the JSON file.
 * @param _spline_
 * 	The output parameter.
 * @return TS_SUCCESS
 * 	On success.
 * @return TS_IO_ERROR
 * 	If \p path does not exist.
 * @return TS_PARSE_ERROR
 * 	If an error occurred while parsing the contents of \p path.
 * @return TS_DIM_ZERO
 * 	If the dimension is 0.
 * @return TS_LCTRLP_DIM_MISMATCH
 * 	If the length of the control point vector modulo dimension is not 0.
 * @return TS_DEG_GE_NCTRLP
 * 	If the degree is greater or equals to the number of control points.
 * @return TS_NUM_KNOTS
 * 	If the number of knots stored in \p json does not match to the number
 * 	of control points and the degree of the spline.
 * @return TS_KNOTS_DECR
 * 	If the knot vector is decreasing.
 * @return TS_MULTIPLICITY
 * 	If there is a knot with multiplicity greater than order.
 * @return TS_MALLOC
 * 	If allocating memory failed.
 */
tsError ts_bspline_load_json(const char *path, tsBSpline *_spline_);



/******************************************************************************
*                                                                             *
* :: Utility Functions                                                        *
*                                                                             *
* The following section contains utility functions used by TinySpline which   *
* also may be helpful when using this library.                                *
*                                                                             *
******************************************************************************/
/**
 * Compares the tsReal values \p x and \p y using an absolute and relative
 * epsilon environment.
 *
 * @param x
 * 	The x value to compare.
 * @param y
 * 	The y value to compare.
 * @return 1
 * 	If \p x is equals to \p y.
 * @return 0
 * 	Otherwise.
 */
int ts_fequals(tsReal x, tsReal y);

/**
 * Returns the error message associated to \p err. Returns "unknown error" if
 * \p err is no associated (indicating a bug) or is TS_SUCCESS (which is not
 * an actual error).
 */
const char* ts_enum_str(tsError err);

/**
 * Returns the error code associated to \p str or TS_SUCCESS if \p str is not
 * associated. Keep in mind that by concept "unknown error" is not associated,
 * though, TS_SUCCESS is returned.
 */
tsError ts_str_enum(const char *str);

/**
 * Fills the given array \p arr with \p val from \p arr+0 to \p arr+ \p num
 * (exclusive).
 */
void ts_arr_fill(tsReal *arr, size_t num, tsReal val);

/**
 * Returns the euclidean distance of \p x and \p y consisting of \p dim
 * components, respectively.
 *
 * @param x
 * 	The x value.
 * @param y
 * 	The y value.
 * @param dim
 * 	The dimension of \p x and \p y.
 * @return
 * 	The euclidean distanc of \p x and \p y.
 */
tsReal ts_ctrlp_dist2(const tsReal *x, const tsReal *y, size_t dim);



#ifdef	__cplusplus
}
#endif

#endif	/* TINYSPLINE_H */

