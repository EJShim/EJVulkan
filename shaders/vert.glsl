#version 450
#extension GL_ARB_separate_shader_objects : enable



layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;


layout(location = 0) out vec3 v_color;
layout(location = 1) out float v_time;

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    float in_time;
} ubo;

out gl_PerVertex {
    vec4 gl_Position;
};




void main() {
    // gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, sin(ubo.in_time+inPosition.x), 1.0);
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    v_color = inColor;
    v_time = ubo.in_time;
}
