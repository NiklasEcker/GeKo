#pragma once

#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <GeKo_Graphics/Renderer/Renderer.h>
#include <GeKo_Graphics/Window.h>
#include <GeKo_Graphics/Buffer.h>
#include <GeKo_Graphics/BufferIndex.h>

#include <GeKo_Graphics/Shader/Shader.h>
#include <GeKo_Graphics/Shader/ShaderManager.h>
#include <GeKo_Graphics/Shader/FBO.h>

#include <GeKo_Graphics/Camera/Camera.h>
#include <GeKo_Graphics/Camera/Pilotview.h>
#include <GeKo_Graphics/Camera/Trackball.h>

#include <GeKo_Graphics/Material/Texture.h>

#include <GeKo_Graphics/Light/ConeLight.h>
#include <GeKo_Graphics/Light/DirectionLight.h>
#include <GeKo_Graphics/Light/PointLight.h>

#include <GeKo_Graphics/Object/Geometry.h>
#include <GeKo_Graphics/Object/Cube.h>
#include <GeKo_Graphics/Object/Teapot.h>
#include <GeKo_Graphics/Object/Rect.h>
#include <GeKo_Graphics/Object/Skybox.h>

#include <GeKo_Graphics/Scenegraph/Level.h>
#include <GeKo_Graphics/Scenegraph/Scene.h>
#include <GeKo_Graphics/Scenegraph/Node.h>
#include <GeKo_Graphics/Scenegraph/Scenegraph.h>

#include <GeKo_Gameplay/Input/InputHandler.h>
#include <GeKo_Gameplay/Input/InputMap.h>
#include <GeKo_Gameplay/Input/MapPilotview.h>
#include <GeKo_Gameplay/Input/MapTrackball.h>


#define VERTICES 0
#define NORMALS 1
#define TEXTURECOORDS 2
#define TANGENTS 3

#define COLOR_TEXTURE_UNIT GL_TEXTURE0
#define NORMAL_TEXTURE_UNIT GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT GL_TEXTURE2
#define CUBE_MAP_TEXTURE_UNIT GL_TEXTURE3

//Shader
#define VERTEX_SHADER_BIT 1
#define TESS_CONTROL_BIT 2
#define TESS_EVAL_BIT 4
#define GEOMETRY_SHADER_BIT 8
#define FRAGMENT_SHADER_BIT 16
#define COMPUTE_SHADER_BIT 32

#define MAT_AMBIENT_BIT 1
#define MAT_DIFFUSE_BIT 2
#define MAT_SPECULAR_BIT 4
#define MAT_TRANSPARENCY_BIT 8

#define NO_FOG 0
#define FOG_LINEAR 1
#define FOG_EXP 2
#define FOG_EXP2 3

//Color
#define darkgrey glm::vec3( 0.2, 0.2, 0.2)
#define gold glm::vec3( 1.0, 0.84, 0.0)
#define red glm::vec3( 1.0, 0.0, 0.0)
#define blue glm::vec3( 0.0, 0.0, 1.0)
#define bluegrey glm::vec3( 0.8, 0.8, 1.0)
#define bronze glm::vec3( 0.59, 0.35, 0.22)
#define grey glm::vec3( 0.66, 0.66, 0.66)
#define black glm::vec3( 0.0, 0.0, 0.0)
#define white glm::vec3( 1.0, 1.0, 1.0)

//FBO
#define INVALID_OGL_VALUE 0xFFFFFFFF