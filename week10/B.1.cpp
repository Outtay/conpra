// compute a convex hull through a graham scan

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

// constatns we need for ccw function later
#define CCW_LEFT_TURN 1
#define CCW_RIGHT_TURN -1
#define CCW_COLINEAR 0

typedef pair<int, int> point_t;

ostream &
operator<< (ostream &out, const point_t &p)
{
	out << "(" << p.first << ", " << p.second << ") ";	
	return out;
}

double
dist (const point_t &a, const point_t &b);

void
set_p0 (vector<point_t> &points);

int
ccw (const point_t &a, const point_t &b, const point_t &origin);

void
graham_scan (vector<point_t>& points, vector<point_t> &chull);

void
dprint (const string mess, const vector<point_t>& points);

int
main (void)
{
	int x, y;
	vector<point_t> points, chull;

	cout << "Reading points ...";

	while (cin >> x >> y) {
		points.push_back (make_pair (x, y));	
	}

	cout << "done.  " << points.size () << " points read in." << endl;

	graham_scan (points, chull);

	cout << chull.size () << " points on the convex hull." << endl;
	dprint ("Convex Hull points:", chull);

	return 0;
}

/*
 * point_angle_comp_p
 *     functor for determining ordering of the points
 *     p0 is our reference point.  by default set to  (0,0)
 *         should be set by constructor.
 *
 *     Two points, a and b, are compared.  a is "less than" b
 *       if b is to the left of the line segment p0 a.
 *       this means that a makes a smaller
 *       angle relative to p0 than b does.
 *
 *     "to the left of" can be determined with the ccw function.
 *
 *     if there's a tie, then the tie is broken by distance (further
 *       point is >)  Note that for a graham scan, we should really
 *        remove all but the furtherest point if two or more of the
 *        are collinear.  this will work itself out later.
 */
struct point_angle_comp_p {
	point_t p0;

	point_angle_comp_p () : p0 (0, 0) { } 
	point_angle_comp_p (const point_t &p) : p0 (p) { } 

	bool operator() (const point_t &a, const point_t &b) 
	{
		int res;

		res = ccw (a, b, p0);

		if (res == CCW_LEFT_TURN)
			return true;
		else if (res == CCW_COLINEAR) {
			double da, db;

			da = dist (p0, a);
			db = dist (p0, b);

			if (da < db)
				return true;
		}

		return false;
	}
};


/*
 * Graham Scan
 *
 *   Pick lowest, leftmost point as P0
 *   sort points relative to their angles with P0
 *         angle will be [0, pi]
 *         can be done using cross products rather than
 *               expensive trig functions
 *   push P0, P1 onto chull
 *   for i = 2 to # points;  do
 *       while (chull.next-to-last-point, chull.last-point, and P_i form
                  a non-left turn)
	     pop chull

	 push P_i onto chull
 *
 *   when finished, chull will have the points of the convex hull.
 *
 *   running time = O (n log n), where n = # points.  most expensive
 *     operation is the sort.
 *
 *   chull is usually a stack.  note, however, that the STL stack class
 *    does not support a "next-to-last" operation.  So, we'll use
 *    a vector instead.
 *
 *   Issues of concern: What if identical points are present?
 *     What if some points make the same angle with P0?
 *     Do we need a check at end?
 *
 *   Most of these issues are automatically taken care of if the
 *     sorting is done correctly.
 *
 *   Identical points are not a problem because they will cause 
 *     the algorithm to think we have colinear points and one will get
 *     removed from the hull.  e.g., assume Pi and Pj are the last two
 *     points on the hull.  Let next point we're considering be Pk
 *     and Pk = Pj.  ccw will report that Pk is colinear with
 *     Pi and Pj.  (2 points always define a line...)  So, the alg.
 *     will take Pj off and put Pk on.  So, we will obtain only one
 *     of identical points.
 *
 *   Points with the same angle will also be handled for much the same
 *     as identical points.  The sorting rule says that ties are
 *     broken according to distance.  Let Pi and Pj be on the stack.
 *     Pk is the point we're considering.  Pk and Pj make the same angle
 *     to P0, but Pk != Pj. By the sorting rule, Pk is "further out" than
 *     Pj.  So, Pk is to the right of the line formed by Pi and Pj.  That
 *     means Pj is popped and Pk pushed on.  The point further out will
 *     considered for the hull (which is what we want).  
 *
 *  Finally, do we need a check at the end to ensure that the last two
 *     do not make a right turn back to P0?  The answer is, probably not,
 *     but I'm not 100% sure.  Let Pi and Pj be the last two points on
 *     the stack.  We could get a right turn back to P0 if Pj is below
 *     P0, but that can't happen because we specifically chose P0 to
 *     be the lowest point.  if Pj is to the left of P0, there is no problem
 *     because we make a left turn to get from Pj to P0.  Can Pj be
 *     to the right of P0?  No.  We assumed that Pj was the last point
 *     to be considered for the hull.  If Pj is to the right of P0, then
 *     Pj will make a smaller angle than Pi.  That is, Pj would have been
 *     considered for inclusion on the hull before Pi.  So Pj can't be
 *     to the right of P0.  The only case left is if Pj is colinear with
 *     Pi and Pj.  This can't happen either because, by the sorting, 
 *     Pj would have to be at a larger distance than Pi.  that would cause
 *     a right turn so that Pi would have been removed.  So it seems
 *     like we don't need a check at the end.
 *
 */
void
graham_scan (vector<point_t>& points, vector<point_t> &chull)
{
	int i;
	bool done;
	point_t next2last, last;

	set_p0 (points);

	cout << "P0 = " << points [0] << endl;

	// notice the + 1
	sort (points.begin () + 1, points.end (),
		point_angle_comp_p (points [0]));

	dprint ("Sorted points:", points);

	chull.push_back (points [0]);
	chull.push_back (points [1]);

	for (i = 2; i < points.size (); i++) {
		done = false;

		while (!done && chull.size () > 1) {
			last = chull.back ();
			next2last = chull [chull.size () - 2];

			/* careful here of the calling order.
			 * origin is next2last, not last!
			 * we're asking if points [i] is left or right
			 *   side of line determined by next2last and last
			 */
			if (ccw (last, points [i], next2last) != CCW_LEFT_TURN)
				chull.pop_back ();
			else
				done = true;
		}

		chull.push_back (points [i]);
	}
}


/*
 * set_p0
 *
 *    runs through the points vector to find the lowest, left-most point.
 *    lowest,left-most is lowest point (decided by y).  ties
 *      are broken using x.
 *
 *    this point will be placed into points [0].  Note that this
 *    means points will change...
 */
void
set_p0 (vector<point_t> &points)
{
	int i;

	for (i = 1; i < points.size (); i++) {
		if (points [i].second < points [0].second)
			swap (points [0], points [i]);
		else if (points [i].second == points [0].second
		       && points [i].first < points [0].first)
			swap (points [0], points [i]);
	}
}



/*
 * ccw
 *
 *   CounterClockWise function.  Returns 
 * 
 *       CCW_LEFT_TURN if a to b is a left turn (relative to origin)
 *       CCW_RIGHT_TURN if a to b is a right turn (relative to origin)
 *       CCW_COLINEAR if a and b are colinear
 *
 *   computing cross product of a and b (relative to origin) 
 *      and taking the z component
 */
int
ccw (const point_t &a, const point_t &b, const point_t &origin)
{
	point_t v1, v2;
	int cp_z;

	v1 = make_pair (a.first - origin.first, a.second - origin.second);
	v2 = make_pair (b.first - origin.first, b.second - origin.second);


	cp_z = v1.first * v2.second - v1.second * v2.first;

	if (cp_z > 0)  // cross product points out of plane, so left
		return CCW_LEFT_TURN;
	else if (cp_z < 0)
		return CCW_RIGHT_TURN;

	return CCW_COLINEAR;
}

/*
 * dist
 *    returns the distance between two points.  simple euclidean dist.
 */
double
dist (const point_t &a, const point_t &b)
{
	int x, y;

	x = a.first - b.first;
	y = a.second - b.second;

	return (sqrt (double (x *x + y * y)));
}

/*
 * dprint
 *      debug print.  dumps out list of points.
 */
void
dprint (const string mess, const vector<point_t>& points)
{
	cout << mess << endl;

	for (int i = 0; i < points.size (); i++) {
		cout << points [i];

		if (!((i + 1) % 8))
			cout << endl;
	}

	cout << endl;
}