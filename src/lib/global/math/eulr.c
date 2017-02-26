#include "eulr.h"

Quat
engineer_math_eulr_to_quat(Eulr input)
{
   Sclr cosr, cosp, cosy, sinr, sinp, siny, cpcy, spsy;
   Vec2 buffer;
   Quat output;

   // calculate trig identities
   buffer = SINCOS(input.roll);
   cosr = DIVD(buffer.x, 2);
   sinr = DIVD(buffer.y, 2);

   buffer = SINCOS(input.pitch);
   cosp = DIVD(buffer.x, 2);
   sinp = DIVD(buffer.y, 2);

   buffer = SINCOS(input.yaw);
   cosy = DIVD(buffer.x, 2);
   siny = DIVD(buffer.y, 2);

   cpcy = MULT(cosp, cosy);
   spsy = MULT(sinp, siny);

   output.w = MULT(cosr, cpcy) + MULT(sinr, spsy);
   output.x = MULT(sinr, cpcy) - MULT(cosr, spsy);
   output.y = MULT(MULT(cosr, sinp), cosy) + MULT(MULT(sinr, cosp), siny);
   output.z = MULT(MULT(cosr, cosp), siny) - MULT(MULT(sinr, sinp), cosy);

   return output;
}
