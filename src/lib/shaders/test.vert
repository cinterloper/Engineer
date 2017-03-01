#ifdef GL_ES
   precision mediump float;
#endif

attribute vec4 a_position;
uniform   mat4 u_mvp_mat;

void main()
{
   gl_Position = u_mvp_mat * a_position;
}

