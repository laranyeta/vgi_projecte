//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** EQUIP SOLAR SPRINT

#version 430 core

#define MaxLights 8

struct Light {
    bool sw_light;
    vec4 position;   // posición en espacio de mundo
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 attenuation;
};

struct Material {
    vec4 emission;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

// variables IN
layout (location = 0) in vec3 in_Vertex;
layout (location = 1) in vec4 in_Color;
layout (location = 2) in vec3 in_Normal;
layout (location = 3) in vec2 in_TexCoord;

// variables OUT
out vec3 vertexPosWorld;   // Posición del fragmento en espacio de mundo
out vec3 vertexNormalWorld;// Normal del fragmento en espacio de mundo
out vec2 vertexTexCoord;
out vec4 vertexColor;

// variables UNIFORM
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;  // inverse(transpose(modelMatrix))
uniform bool flag_invert_y;

void main() {
    // Posición del vértice en espacio de mundo (NO incluir viewMatrix)
    vec4 posWorld = modelMatrix * vec4(in_Vertex, 1.0);
    vertexPosWorld = posWorld.xyz;

    // Normal en espacio de mundo
    vertexNormalWorld = normalize((normalMatrix * vec4(in_Normal, 0.0)).xyz);

    // Coordenadas de textura
    vertexTexCoord = flag_invert_y ? vec2(in_TexCoord.x, 1.0 - in_TexCoord.y) : in_TexCoord;
    vertexColor = in_Color;

    // Transformación final para rasterizado
    gl_Position = projectionMatrix * viewMatrix * posWorld;
}
