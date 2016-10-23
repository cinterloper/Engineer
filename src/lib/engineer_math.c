#include "engineer_math.h"

static void
eng_quat_multiply(const EngQuat& q1, const EngQuat& q2)
{
     Quat quaternion;
     quaternion.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
     quaternion.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
     quaternion.y = q1.w*q2.y + q1.y*q2.w + q1.z*q2.x - q1.x*q2.z; // x<>z Switched!
     quaternion.z = q1.w*q2.z + q1.z*q2.w + q1.x*q2.y - q1.y*q2.x;
     return quaternion;
}

static EngQuat
eng_quat_normalize(const Quat& q)
{
     EngQuat quaternion;
     float sq = q.x * q.x;
     sq += q.y * q.y;
     sq += q.z * q.z;
     sq += q.w * q.w;
     //detect badness
     assert(sq > 0.1f);
     float inv = 1.0f / sqrt(sq);
     quaternion.x = q.x * inv;
     quaternion.y = q.y * inv;
     quaternion.z = q.z * inv;
     quaternion.w = q.w * inv;
     return quaternion;
}

static EngMatrix
eng_quat_matrixify(const EngQuat &q)
{
     EngMatrix matrix;

     // Helper quantities, we calculate these up front to avoid redundancies.
     float xSq  = q.x * q.x,  ySq  = q.y * q.y,  zSq  = q.z * q.z,  wSq = q.w * q.w;
     float twoX = 2.0f * q.x, twoY = 2.0f * q.y, twoW = 2.0f * q.w;
     float xy   = twoX * q.y, xz   = twoX * q.z, yz   = twoY * q.z;
     float wx   = twoW * q.x, wy   = twoW * q.y, wz   = twoW * q.z;

     // Fill in the first row.
     matrix.cell00 = wSq + xSq - ySq - zSq;
     matrix.cell01 = xy - wz;
     matrix.cell02 = xz + wy;
     // Fill in the second row.
     matrix.cell10 = xy + wz;
     matrix.cell11 = wSq - xSq + ySq - zSq;
     matrix.cell12 = yz - wx;
     // Fill in the third row.
     matrix.cell20 = xz - wy;
     matrix.cell21 = yz + wx;
     matrix.cell22 = wSq - xSq - ySq + zSq;

     return matrix;
}
