#pragma once

/*  Core Engine */
#include "Metamorphic/Core.h"
#include "Metamorphic/Application.h"
#include "Metamorphic/Logger.h"
#include "Metamorphic/Time.h"

/* Scenes */
#include "Metamorphic/Scene/Scene.h"
#include "Metamorphic/Scene/SceneManager.h"
/* Objects */
#include "Metamorphic/Objects/Component/Component.h"
#include "Metamorphic/Objects/GameObject.h"

/*  Rendering */
#include "Metamorphic/Rendering/Mesh/BasicMesh.h"
//#ifdef METAMORPHIC_USE_OPENGL
//#include "Platforms/Rendering/OpenGL/BasicMesh.h"
//#else

//#error NO VALID RENDERING API FOR MESHES
//#endif

/* Entry Point*/
#ifndef METAMORPHIC_NO_ENTRY_POINT
#include "Metamorphic/EntryPoint.h"
#endif