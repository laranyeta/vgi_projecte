//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** EQUIP SOLAR SPRINT

#version 430 core

#define MaxLights 8

// Estructuras de luz y material
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

// Variables IN
in vec3 vertexPosWorld;   // Posición del vértice en espacio de mundo
in vec3 vertexNormalWorld; // Normal del fragmento en espacio de mundo
in vec2 vertexTexCoord;    // Coordenadas de la textura
in vec4 vertexColor;       // Color pasado desde el VAO

// Variables OUT
out vec4 FragColor;

// Variables UNIFORM
uniform sampler2D texture0;  // Textura de la escena
uniform bool textur;          // Si se debe aplicar la textura
uniform bool sw_material;     // Activación de material

uniform Light LightSource[MaxLights];  // Fuentes de luz
uniform Material material;             // Material del objeto

uniform vec3 posSol;      // Posición del Sol en espacio de mundo
uniform float radiSol;    // Radio del Sol
uniform float glowRadius; // Radio del glow del Sol
uniform float bloomStrength; // Fuerza del efecto bloom

void main() {
    // Normal del fragmento en espacio de mundo
    vec3 N = normalize(vertexNormalWorld);

    // Vector desde el fragmento hacia la luz (Sol) en espacio de mundo
    vec3 L = normalize(LightSource[0].position.xyz - vertexPosWorld);

    // Iluminación ambiente
    vec3 ambient = LightSource[0].ambient.rgb * material.ambient.rgb;

    // Iluminación difusa (no depende de la cámara, solo del ángulo entre N y L)
    float diffuseFactor = max(dot(N, L), 0.0);
    vec3 diffuse = LightSource[0].diffuse.rgb * material.diffuse.rgb * diffuseFactor;

    // Color final sin efectos
    vec3 finalColor = ambient + diffuse;

    // Glow del Sol
    float distanceFromSun = length(vertexPosWorld - posSol);
    float glowIntensity = 1.0 - smoothstep(radiSol, radiSol + glowRadius, distanceFromSun);
    vec4 glowColor = vec4(1.0, 0.6, 0.0, glowIntensity); // Glow en color naranja

    // El color base se combina con el glow del Sol
    vec4 baseColor = vec4(finalColor, 1.0);
    baseColor = mix(baseColor, glowColor, glowIntensity);

    // Aplicar la textura si está habilitada
    vec4 texColor = texture(texture0, vertexTexCoord);
    if (textur) {
        FragColor = baseColor * texColor;  // Aplicar la textura sobre el color base
    } else {
        FragColor = baseColor;  // Usar solo el color base sin textura
    }

    // Mantener la transparencia del glow
    FragColor.a = max(FragColor.a, glowIntensity);

    // Aplicar el efecto de bloom (fuerza de glow sobre la escena)
    FragColor.rgb += glowColor.rgb * bloomStrength; // Combina el glow con la escena
}

