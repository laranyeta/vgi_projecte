//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn bàsic VS2022 amb interfície MFC/GLFW i Status Bar
//******** Enric Marti (Setembre 2023)

//LCR -- implemetació shader Solar System .vert

#version 430 core

#define MaxLights 8

struct Light {
    bool sw_light;
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 attenuation;
    bool restricted;
    vec3 spotDirection;
    float spotCosCutoff;
    float spotExponent;
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
out vec3 vertexPV;
out vec3 vertexNormalPV;
out vec2 vertexTexCoord;
out vec4 vertexColor;
out vec3 fragPosition;

// variables UNIFORM
uniform mat4 normalMatrix;    
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform sampler2D texture0;
uniform bool textur;
uniform bool flag_invert_y;

void main() {
    vertexPV = vec3(viewMatrix * modelMatrix * vec4(in_Vertex, 1.0));
    vertexNormalPV = normalize(vec3(normalMatrix * vec4(in_Normal, 1.0)));

    //calcular iluminacio a vista mon
    fragPosition = vec3(modelMatrix * vec4(in_Vertex, 1.0));

    vertexTexCoord = flag_invert_y ? vec2(in_TexCoord.x, 1.0 - in_TexCoord.y) : in_TexCoord;
    vertexColor = in_Color;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Vertex, 1.0);
}
