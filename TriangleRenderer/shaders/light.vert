uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform vec3 u_Light;
uniform vec3 u_LightColor;

attribute vec3 a_Position;
attribute vec2 a_TexCoord;
attribute vec3 a_Normal;

varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_FragPos;
varying vec3 v_Light;
varying vec3 v_LightColor;

void main()
{
  gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1);

  v_TexCoord = a_TexCoord;
  v_Normal = vec3(u_Model * vec4(a_Normal, 0));
  v_FragPos = vec3(u_Model * vec4(a_Position, 1));
  v_Light = u_Light;
  v_LightColor = u_LightColor;
}

// v_Normal = mat3(u_Model) * a_Normal;
// v_Normal = vec3(u_Model * vec4(a_Normal, 0));
