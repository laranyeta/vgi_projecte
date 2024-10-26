//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn bàsic VS2022 amb interfície MFC/GLFW i Status Bar
//******** Enric Marti (Setembre 2023)

//LCR -- implemetació shader Solar System .frag

#version 430 core

#define MaxLights 8

struct Light {
    bool sw_light;
    vec4 position;
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
in vec3 vertexPV;
in vec3 vertexNormalPV;
in vec2 vertexTexCoord;
in vec4 vertexColor;
in vec3 fragPosition;

// variables OUT
out vec4 FragColor;

// variables UNIFORM
uniform sampler2D texture0;
uniform bool textur;
uniform bool sw_material;
uniform bvec4 sw_intensity;

uniform Light LightSource[MaxLights];
uniform Material material;

uniform vec3 posSol; //PLANETES[0].getPosicio()
uniform float radiSol; //PLANETES[0].getRadi()
uniform float glowRadius;

void main() {
    vec3 N = normalize(vertexNormalPV);
    vec3 V = normalize(-vertexPV);

    vec3 L = normalize(posSol - fragPosition);

    //llum AMBIENT
    vec3 ambient = LightSource[0].ambient.rgb * material.ambient.rgb;

    //llum DIFUSA
    float diffuseFactor = max(dot(N, L), 0.0);
    vec3 diffuse = LightSource[0].diffuse.rgb * material.diffuse.rgb * diffuseFactor;

    //llum ESPECULAR
    vec3 R = reflect(-L, N);
    float specularFactor = pow(max(dot(R, V), 0.0), material.shininess);
    vec3 specular = LightSource[0].specular.rgb * material.specular.rgb * specularFactor;

    vec3 finalColor = ambient + diffuse + specular;

    //GLOW
    float distanceFromSun = length(fragPosition - posSol);
    float glowIntensity = 1.0 - smoothstep(radiSol, radiSol + glowRadius, distanceFromSun);

    float alphaGlow = glowIntensity;
    vec4 glowColor = vec4(1.0, 0.6, 0.0, alphaGlow);  //afegim transparecia

    vec4 baseColor = vec4(finalColor, 1.0);
    baseColor = mix(baseColor, glowColor, glowIntensity);

    vec4 texColor = texture(texture0, vertexTexCoord);
    if (textur) {
        FragColor = baseColor * texColor;
    } else {
        FragColor = baseColor;
    }

    FragColor.a = max(FragColor.a, alphaGlow);
}
