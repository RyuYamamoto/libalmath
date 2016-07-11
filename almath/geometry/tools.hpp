/**
 * Copyright 2016 Aldebaran. All rights reserved.
 */

#ifndef _LIBALMATH_ALMATH_GEOMETRY_TOOLS_HPP_
#define _LIBALMATH_ALMATH_GEOMETRY_TOOLS_HPP_

#include <qi/geometry/geometry.hpp>

namespace qi
{
namespace geometry
{
Vector3 makeVector3(double x, double y, double z);

Quaternion makeQuaternion(double x, double y, double z, double w);

// Check if the quaternion made out of x, y, z, w is normalized, and
// throw if it is not the case.
Quaternion makeNormalizedQuaternion(double x, double y, double z, double w);

Transform makeTransform(const Quaternion &rotation, const Vector3 &translation);

bool isNear(const Transform &lhs, const Transform &rhs, double epsilon);

Transform operator*(const Transform &lhs, const Transform &rhs);

Transform inverse(const Transform &tf);

double norm(const Quaternion &r);

void normalize(Quaternion &r);

Quaternion normalized(const Quaternion &r);

inline std::ostream& operator<<(std::ostream &o, const Quaternion &r)
{
  return o << "Quaternion(" << r.x << ", " << r.y << ", " << r.z << ", "
           << r.w << ")";
}

inline std::ostream& operator<<(std::ostream &o, const Vector3 &t)
{
  return o << "Vector3(" << t.x << ", " << t.y << ", " << t.z << ")";
}

inline std::ostream& operator<<(std::ostream &o, const Transform &tf)
{
  return o << "Transform(" << tf.rotation << ", " << tf.translation << ")";
}
}
}

#endif
