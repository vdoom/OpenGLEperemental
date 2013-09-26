#ifndef SHADERS_H
#define SHADERS_H
static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec3 colAttr;\n"
    "varying lowp vec3 col;\n"
    "uniform lowp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec3 col;\n"
    "void main() {\n"
        "   gl_FragColor = vec4(col, 1.0);;\n"//vec4(1.0, 1.0, 1.0, 1.0);\n"
    "}\n";

static const char * texturedVertexShaderSource =
        "attribute lowp vec4 position;\n"
        "attribute lowp vec2 texcoord;\n"
        "varying lowp vec2 textureCoord;\n"
        "uniform lowp mat4 modelViewProjectionMatrix;\n"
        "void main() {\n"
        "       gl_Position = modelViewProjectionMatrix * position;\n"/*vec4(position, 1.0);\n"*/
        "        textureCoord = texcoord;\n"
        "}\n";

static const char * texturedFragmentShaderSource =
        "uniform lowp sampler2D colorTexture;\n"
        "varying lowp vec2 textureCoord;\n"
        "void main() {\n"
        "        gl_FragColor = texture2D(colorTexture, textureCoord );\n"
        "}\n";

static const char * materialVertexShaderSource =
        "attribute lowp vec3 position;\n"
        "attribute lowp vec2 texcoord;\n"
        "attribute lowp vec3 normal;"
        "uniform struct Transform\n"
        "{"
        "        mat4 model;\n"
        "        mat4 viewProjection;\n"
        "        mat3 normal;\n"
        "        vec3 viewPosition;\n"
        "} transform;\n"
        "uniform struct PointLight\n"
        "{"
        "        vec4 position;\n"
        "        vec4 ambient;\n"
        "        vec4 diffuse;\n"
        "        vec4 specular;\n"
        "        vec3 attenuation;\n"
        "} light;\n"
        "varying Vertex {\n"
        "        vec2  texcoord;\n"
        "        vec3  normal;\n"
        "        vec3  lightDir;\n"
        "        vec3  viewDir;\n"
        "        float distance;\n"
        "} Vert;\n"
        "void main(void)\n"
        "{\n"
        "        vec4 vertex   = transform.model * vec4(position, 1.0);\n"
        "        vec4 lightDir = light.position - vertex;\n"
        "        Vert.texcoord = texcoord;\n"
        "        Vert.normal   = transform.normal * normal;\n"
        "        Vert.lightDir = vec3(lightDir);\n"
        "        Vert.viewDir  = transform.viewPosition - vec3(vertex);\n"
        "        Vert.distance = length(lightDir);\n"
        "        gl_Position = transform.viewProjection * vertex;\n"
        "}\n";
static const char * materialFragmentShaderSource =
        "uniform struct PointLight\n"
        "{\n"
        "        vec4 position;\n"
        "        vec4 ambient;\n"
        "        vec4 diffuse;\n"
        "        vec4 specular;\n"
        "        vec3 attenuation;\n"
        "} light;\n"
        "uniform struct Material\n"
        "{\n"
        "        sampler2D texture;\n"
        "        vec4  ambient;\n"
        "        vec4  diffuse;\n"
        "        vec4  specular;\n"
        "        vec4  emission;\n"
        "        float shininess;\n"
        "} material;\n"
        "struct Vertex\n"
        "{\n"
        "        vec2  texcoord;\n"
        "        vec3  normal;\n"
        "        vec3  lightDir;\n"
        "        vec3  viewDir;\n"
        "        float distance;\n"
        "};\n"
        "varying Vertex Vert;\n"
        "varying lowp vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "        vec3 normal   = normalize(Vert.normal);\n"
        "        vec3 lightDir = normalize(Vert.lightDir);\n"
        "        vec3 viewDir  = normalize(Vert.viewDir);\n"
        "        float attenuation = 1.0 / (light.attenuation[0] +\n"
        "                light.attenuation[1] * Vert.distance +\n"
        "                light.attenuation[2] * Vert.distance * Vert.distance);\n"
        "        color = material.emission;\n"
        "        color += material.ambient * light.ambient * attenuation;\n"
        "        float NdotL = max(dot(normal, lightDir), 0.0);\n"
        "        color += material.diffuse * light.diffuse * NdotL * attenuation;\n"
        "        float RdotVpow = max(pow(dot(reflect(-lightDir, normal), viewDir), material.shininess), 0.0);\n"
        "        color += material.specular * light.specular * RdotVpow * attenuation;\n"
        "        color *= texture(material.texture, Vert.texcoord);\n"
        "}\n";
#endif // SHADERS_H
