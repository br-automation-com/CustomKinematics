#include <McPathGen.h>
#include <bur/plctypes.h>
#include <math.h>

#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "CusMechSca.h"
#ifdef __cplusplus
	};
#endif

#ifndef DBL_EPSILON
#define DBL_EPSILON 2.2204460492503131E-16      /* precision of double */
#endif

/* comparisons to precision of double */
#define IS_DBL_ZERO(a)         (fabs(a) <= DBL_EPSILON) /* argument should be evaluated only once - f() */
#define IS_DBL_EQUAL(a, b)     IS_DBL_ZERO((a) - (b)) /* arguments should be evaluated only once - f() */
#define IS_DBL_POSITIVE(a)     ((a) > DBL_EPSILON)
#define IS_DBL_GREATER(a, b)   IS_DBL_POSITIVE((a) - (b))

plcbit Rz(double a, double* M)
{
	double cosA = cos(a),
	sinA = sin(a);

	M[0] = cosA;  M[1] = -sinA;  M[2] = 0.0;
	M[3] = sinA;  M[4] =  cosA;  M[5] = 0.0;
	M[6] = 0.0;   M[7] =   0.0;  M[8] = 1.0;
	
	return 1;
}

plcbit Mat33Vec3Multiply(double* A, double* v, double* w)
{
	w[0] = A[0] * v[0] + A[1] * v[1] + A[2] * v[2];
	w[1] = A[3] * v[0] + A[4] * v[1] + A[5] * v[2];
	w[2] = A[6] * v[0] + A[7] * v[1] + A[8] * v[2];
	
	return 1;
} 

unsigned long RphiAplusRpsiBequalC(double a1, double a2, double b1, double b2, double c1, double c2, double* phi1, double* psi1, double* phi2, double* psi2)
{
	double  l1, l2, l3,                  /* lengths of [a1,a2]~, [b1,b2]~, [c1,c2]~, respectively */
	l1angle, l2angle, l3angle,   /* angles of vectors l1, l2, l3 */
	alpha,                       /* angle between vector (a1, a2) and (b1, b2) */
	chi, eta;                    /* angles defined in Kinematic_Transformations_E_xy.pdf */

	/* The left side of this equation is nothing more than a sum of two vectors in 2D, where each vector is a rotated
	* vector (first one by the angle phi, second one by the angle psi). Therefore it is easy to see that if we take
	* care only about the lengths of these vectors, then the solution exists iff |l1-l2| <= l3 <= l1+l2, and that if
	* one of these inequations becomes equality, then there is one solution (otherwise there are two solutions, which will
	* be considered to be distinct).
	*/

	/* test of the number of solutions - cosine theorem (the law of cosines) a^2 = b^2 + c^2 -2bc*cos(alpha) */
	l1 = sqrt(a1*a1 + a2*a2);
	l2 = sqrt(b1*b1 + b2*b2);
	l3 = sqrt(c1*c1 + c2*c2);

	/* attention - the following values should be used only in case that the corresponding vectors lengths are not equal to zero (up to epsilon) */
	l1angle = atan2(a2, a1);
	l2angle = atan2(b2, b1);
	l3angle = atan2(c2, c1);

	if (IS_DBL_ZERO(l1))
	{
		if (IS_DBL_ZERO(l2))
		{
			/* l1 = 0, l2 = 0 */

			if (IS_DBL_ZERO(l3))
			{
				/* every (phi, psi) is the solution */
				return 255;
			}

			/* there is no solution */
			return 0;
		}

		/* l1 = 0, l2 <> 0 */

		if (IS_DBL_ZERO(l3))
		{
			/* there is no solution */
			return 0;
		}

		/* l1 = 0, l2 <> 0, l3 <> 0 */

		if (IS_DBL_EQUAL(l2, l3))
		{
			/* there exist a solution, phi is arbitrary */

			*psi1 = *psi2 = Mod2pi(l3angle - l2angle);

			return 254;
		}

		/* there is no solution - l3 <> 0, but l2 != l3 */
		return 0;
	}

	if (IS_DBL_ZERO(l2))
	{
		/* l1 <> 0, l2 = 0 */

		if (IS_DBL_ZERO(l3))
		{
			/* there is no solution */
			return 0;
		}

		if (IS_DBL_EQUAL(l1, l3))
		{
			/* there exist a solution, psi is arbitrary */

			*phi1 = *phi2 = Mod2pi(l3angle - l1angle);

			return 253;
		}

		/* there is no solution - l3 <> 0, but l2 != l3 */
		return 0;
	}

	if (IS_DBL_ZERO(l3))
	{
		/* l1 <> 0, l2 <> 0, l3 = 0 */

		if (IS_DBL_EQUAL(l1, l2))
		{
			/* phi is arbitrary, psi = phi + PI - alpha */
			return 252;
		}

		/* there is no solution - l1 != l2 */
		return 0;
	}

	/* l1 <> 0, l2 <> 0 l3 <> 0 */

	alpha = l2angle - l1angle;

	if (IS_DBL_EQUAL(fabs(l1 - l2), l3))
	{
		/* l1 > l2 */

		*phi1 = *phi2 = Mod2pi(l3angle - l1angle);
		*psi1 = *psi2 = Mod2pi(*phi1 + M_PI - alpha);

		if (l1 < l2)
		{
			*phi1 = *phi2 = Mod2pi(*phi1 + M_PI);
			*psi1 = *psi2 = Mod2pi(*psi1 + M_PI);
		}

		return 1;
	}

	if (IS_DBL_EQUAL(l3, l1 + l2))
	{
		/* there is only one solution, both vectors have the same direction */

		*phi1 = *phi2 = Mod2pi(l3angle - l1angle);
		*psi1 = *psi2 = Mod2pi(*phi1 - alpha);

		return 1;
	}

	if (IS_DBL_GREATER(fabs(l1 - l2), l3) || IS_DBL_GREATER(l3, (l1 + l2)))
	{
		/* there is no solution */
		return 0;
	}

	/* regular case - there are two distinct solutions */

	chi = acos((l3*l3 - l1*l1 - l2*l2) / (2.0 * l1 * l2)); /* in (0; PI) */
	eta = acos((l1*l1 + l3*l3 - l2*l2) / (2.0 * l1 * l3)); /* in (0; PI), eta < chi */

	*phi1 = Mod2pi(l3angle - eta - l1angle);
	*psi1 = Mod2pi(*phi1 + chi - alpha);

	*phi2 = Mod2pi(l3angle + eta - l1angle);
	*psi2 = Mod2pi(*phi2 - chi - alpha);

	return 2;
}

double Mod2pi(double alpha)
{
	alpha = fmod(alpha, 2*M_PI);
	if (alpha <= -M_PI) alpha += 2*M_PI;
	if (alpha > M_PI) alpha -= 2*M_PI;
	return alpha;
}

double GoToWith2kpi(double alpha, double beta)
{
    return (beta + Mod2pi(alpha - beta));
}

plcbit MatVecMultiply(double* A, double* v, unsigned long dimension, double* w)
{
	unsigned long  i, j;

	for (i = 0; i < dimension; i++)
	{
		w[i] = 0.0;
		for (j = 0; j < dimension; j++) w[i] += A[i * dimension + j] * v[j];
	}
}

plcbit invertMatrix44(double* matrix, double* inverseMatrix)
{
	double inv[16], det;
	int i;

	inv[0] = matrix[5]  * matrix[10] * matrix[15] - 
		matrix[5]  * matrix[11] * matrix[14] - 
		matrix[9]  * matrix[6]  * matrix[15] + 
		matrix[9]  * matrix[7]  * matrix[14] +
		matrix[13] * matrix[6]  * matrix[11] - 
		matrix[13] * matrix[7]  * matrix[10];

	inv[4] = -matrix[4]  * matrix[10] * matrix[15] + 
		matrix[4]  * matrix[11] * matrix[14] + 
		matrix[8]  * matrix[6]  * matrix[15] - 
		matrix[8]  * matrix[7]  * matrix[14] - 
		matrix[12] * matrix[6]  * matrix[11] + 
		matrix[12] * matrix[7]  * matrix[10];

	inv[8] = matrix[4]  * matrix[9] * matrix[15] - 
		matrix[4]  * matrix[11] * matrix[13] - 
		matrix[8]  * matrix[5] * matrix[15] + 
		matrix[8]  * matrix[7] * matrix[13] + 
		matrix[12] * matrix[5] * matrix[11] - 
		matrix[12] * matrix[7] * matrix[9];

	inv[12] = -matrix[4]  * matrix[9] * matrix[14] + 
		matrix[4]  * matrix[10] * matrix[13] +
		matrix[8]  * matrix[5] * matrix[14] - 
		matrix[8]  * matrix[6] * matrix[13] - 
		matrix[12] * matrix[5] * matrix[10] + 
		matrix[12] * matrix[6] * matrix[9];

	inv[1] = -matrix[1]  * matrix[10] * matrix[15] + 
		matrix[1]  * matrix[11] * matrix[14] + 
		matrix[9]  * matrix[2] * matrix[15] - 
		matrix[9]  * matrix[3] * matrix[14] - 
		matrix[13] * matrix[2] * matrix[11] + 
		matrix[13] * matrix[3] * matrix[10];

	inv[5] = matrix[0]  * matrix[10] * matrix[15] - 
		matrix[0]  * matrix[11] * matrix[14] - 
		matrix[8]  * matrix[2] * matrix[15] + 
		matrix[8]  * matrix[3] * matrix[14] + 
		matrix[12] * matrix[2] * matrix[11] - 
		matrix[12] * matrix[3] * matrix[10];

	inv[9] = -matrix[0]  * matrix[9] * matrix[15] + 
		matrix[0]  * matrix[11] * matrix[13] + 
		matrix[8]  * matrix[1] * matrix[15] - 
		matrix[8]  * matrix[3] * matrix[13] - 
		matrix[12] * matrix[1] * matrix[11] + 
		matrix[12] * matrix[3] * matrix[9];

	inv[13] = matrix[0]  * matrix[9] * matrix[14] - 
		matrix[0]  * matrix[10] * matrix[13] - 
		matrix[8]  * matrix[1] * matrix[14] + 
		matrix[8]  * matrix[2] * matrix[13] + 
		matrix[12] * matrix[1] * matrix[10] - 
		matrix[12] * matrix[2] * matrix[9];

	inv[2] = matrix[1]  * matrix[6] * matrix[15] - 
		matrix[1]  * matrix[7] * matrix[14] - 
		matrix[5]  * matrix[2] * matrix[15] + 
		matrix[5]  * matrix[3] * matrix[14] + 
		matrix[13] * matrix[2] * matrix[7] - 
		matrix[13] * matrix[3] * matrix[6];

	inv[6] = -matrix[0]  * matrix[6] * matrix[15] + 
		matrix[0]  * matrix[7] * matrix[14] + 
		matrix[4]  * matrix[2] * matrix[15] - 
		matrix[4]  * matrix[3] * matrix[14] - 
		matrix[12] * matrix[2] * matrix[7] + 
		matrix[12] * matrix[3] * matrix[6];

	inv[10] = matrix[0]  * matrix[5] * matrix[15] - 
		matrix[0]  * matrix[7] * matrix[13] - 
		matrix[4]  * matrix[1] * matrix[15] + 
		matrix[4]  * matrix[3] * matrix[13] + 
		matrix[12] * matrix[1] * matrix[7] - 
		matrix[12] * matrix[3] * matrix[5];

	inv[14] = -matrix[0]  * matrix[5] * matrix[14] + 
		matrix[0]  * matrix[6] * matrix[13] + 
		matrix[4]  * matrix[1] * matrix[14] - 
		matrix[4]  * matrix[2] * matrix[13] - 
		matrix[12] * matrix[1] * matrix[6] + 
		matrix[12] * matrix[2] * matrix[5];

	inv[3] = -matrix[1] * matrix[6] * matrix[11] + 
		matrix[1] * matrix[7] * matrix[10] + 
		matrix[5] * matrix[2] * matrix[11] - 
		matrix[5] * matrix[3] * matrix[10] - 
		matrix[9] * matrix[2] * matrix[7] + 
		matrix[9] * matrix[3] * matrix[6];

	inv[7] = matrix[0] * matrix[6] * matrix[11] - 
		matrix[0] * matrix[7] * matrix[10] - 
		matrix[4] * matrix[2] * matrix[11] + 
		matrix[4] * matrix[3] * matrix[10] + 
		matrix[8] * matrix[2] * matrix[7] - 
		matrix[8] * matrix[3] * matrix[6];

	inv[11] = -matrix[0] * matrix[5] * matrix[11] + 
		matrix[0] * matrix[7] * matrix[9] + 
		matrix[4] * matrix[1] * matrix[11] - 
		matrix[4] * matrix[3] * matrix[9] - 
		matrix[8] * matrix[1] * matrix[7] + 
		matrix[8] * matrix[3] * matrix[5];

	inv[15] = matrix[0] * matrix[5] * matrix[10] - 
		matrix[0] * matrix[6] * matrix[9] - 
		matrix[4] * matrix[1] * matrix[10] + 
		matrix[4] * matrix[2] * matrix[9] + 
		matrix[8] * matrix[1] * matrix[6] - 
		matrix[8] * matrix[2] * matrix[5];

	det = matrix[0] * inv[0] + matrix[1] * inv[4] + matrix[2] * inv[8] + matrix[3] * inv[12];

	if (det == 0)
		return 0;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
	{
		inverseMatrix[i] = inv[i] * det;
	}
		
	return 1;
}
