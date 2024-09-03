#Platforms [Windows, Xbox, Android]
#Engine Type can be Static | Dynamic
#build type can be Editor | Sandbox
#RenderingAPI can be OpenGL | DirectX

Platform=Windows
Configuration =Debug
EngineType = Dynamic
BuildType = Sandbox
RenderingAPI = DirectX

#Names of the output files
ENGINE_TARGET_NAME = MetamorphicEngine
SANDBOX_TARGET_NAME = SandboxApp
EDITOR_TARGET_NAME = MetamorphicEditor

#Create and destroy files/folders
RM      = rm -r 
RF      = rd /s /q
MF 		= mkdir -p

#REGION COMPILERS
#Compilers, Linkers, File Creators and Destroyers
CC      = cl
LINKER	= link
LIBRARY_CREATOR = lib

#Include Flag
IF =/I
#Define Flag
DF =/D
#Define Lib Path Flag
LPF = /LibPath:
#Output Flag
OUTPUT_FLAG = /out:
#ENDOF COMPILERS

#	--- Start of Output and Int folders ---
ENGINE_OUTPUT_DIR = bin/Engine/$(Platform)/$(Configuration)-$(EngineType)/
ENGINE_INT_DIR = bin-int/Engine/$(Platform)/$(Configuration)-$(EngineType)/

ENGINE_OBJ_DIRS = $(ENGINE_INT_DIR)

SANDBOX_OUTPUT_DIR = bin/SandboxApp/$(Platform)/$(Configuration)-$(EngineType)/
SANDBOX_INT_DIR = bin-int/SandboxApp/$(Platform)/$(Configuration)-$(EngineType)/

EDITOR_OUTPUT_DIR = bin/Editor/$(Platform)/$(Configuration)-$(EngineType)/
EDITOR_INT_DIR = bin-int/Editor/$(Platform)/$(Configuration)-$(EngineType)/
#	--- End of output and int folders	---

ENGINE_SRC = src/Engine/
MORPHIC_SRC = $(ENGINE_SRC)Metamorphic/
PLATFORMS_SRC = $(ENGINE_SRC)Platforms/
EDITOR_SRC = src/Editor/
INCLUDE_DIRS = 

DEFINES =$(DF)WINDOWS_IGNORE_PACKING_MISMATCH 
LIBS =
CFLAGS = /std:c++17
LFLAGS =
ENGINE_PCH_NAME = mmafx
EDITOR_PCH_NAME = mmepch
DEFINES +=$(DF)METAMORPHIC_PLATFORM=WINDOWS
CRT = /MD
PROGRAM_ARGS = 
INCLUDE_DIRS += $(IF)libs/spdlog/include

ENGINE_FILES =
ENGINE_DEFINES =$(DF)METAMORPHIC_ENGINE_BUILD
EDITOR_DEFINES =$(DF)METAMORPHIC_EDITOR_BUILD

ifeq ($(Configuration), Debug)
DEFINES +=$(DF)METAMORPHIC_ENGINE_BUILD_DEBUG
CFLAGS +=  /Zi /Od
LFLAGS +=  /INCREMENTAL
else ifeq ($(Configuration), Release)
DEFINES +=$(DF)METAMORPHIC_ENGINE_BUILD_RELEASE
CFLAGS += /GR- /O2 /GL /Ot
LFLAGS +=  /INCREMENTAL
else
DEFINES +=$(DF)METAMORPHIC_ENGINE_BUILD_DIST
CFLAGS += /GR- /O2 /GL /Ot
LFLAGS += /LTCG /OPT:REF
endif

#core files
ENGINE_FILES += $(MORPHIC_SRC)/Application.cpp $(MORPHIC_SRC)/Logger.cpp $(MORPHIC_SRC)/Objects/Component/Component.cpp $(MORPHIC_SRC)/Objects/GameObject.cpp $(MORPHIC_SRC)Time.cpp
ENGINE_FILES += $(MORPHIC_SRC)/Scene/Scene.cpp $(MORPHIC_SRC)/Scene/SceneManager.cpp
EDITOR_FILES += $(EDITOR_SRC)/Main.cpp
SANDBOX_FILES += src/SandboxApp/SandboxApp.cpp

ifeq ($(Platform), Windows)
DEFINES += /DMETAMORPHIC_PLATFORM=Windows /DMETAMORPHIC_USE_SPDLOG
LIBS+=GDI32.lib Shell32.lib kernel32.lib User32.lib
ENGINE_LFLAGS += /MACHINE:X64
ENGINE_FILES += $(ENGINE_SRC)Platforms/DesktopInput.cpp

ifeq ($(RenderingAPI), OpenGL)
DEFINES += $(DF)GLEW_STATIC $(DF)METAMORPHIC_USE_OPENGL
EDITOR_INCLUDES += $(IF)libs/GLFW3.4/x64/include $(IF)libs/glew-2.2.0/include $(IF)libs/spdlog/include
EDITOR_LIB_PATHS += /LIBPATH:"libs/GLFW3.4/x64/lib-vc2022" /LIBPATH:"libs/glew-2.2.0/libs/x64"
EDITOR_LIBS += glfw3.lib glew32s.lib opengl32.lib

ENGINE_FILES += $(PLATFORMS_SRC)GLFWWindow.cpp $(PLATFORMS_SRC)GLFWRenderAPI.cpp
ENGINE_INCLUDES += $(IF)libs/GLFW3.4/x64/include $(IF)libs/glew-2.2.0/include $(IF)libs/spdlog/include
ENGINE_LIB_PATHS += /LIBPATH:"libs/GLFW3.4/x64/lib-vc2022" /LIBPATH:"libs/glew-2.2.0/libs/x64"
ENGINE_LIBS += glfw3.lib glew32s.lib opengl32.lib
else ifeq ($(RenderingAPI), DirectX)
DEFINES += $(DF)METAMORPHIC_USE_DIRECTX
ENGINE_FILES += $(PLATFORMS_SRC)DirectXWindow.cpp $(PLATFORMS_SRC)DirectXRenderAPI.cpp
ENGINE_LIBS += D3d12.lib dxgi.lib

else
$(error Windows Invalid Rendering API)
endif
ifeq ($(Configuration), Dist)
LFLAGS += /SUBSYSTEM:WINDOWS
endif
else ifeq ($(Platform), Xbox)
$(error XBOX NOT SUPPORTED YET)
else ifeq ($(Platform), Android)
$(error Android NOT SUPPORTED YET)
else
$(error unspecified or invalid platform, got ($(Platform)))
endif

ifeq ($(EngineType), Dynamic)
ENGINE_DEFINES += $(DF)METAMORPHIC_ENGINE_EXPORTS
ENGINE_LFLAGS += /DLL
LIBRARY_CREATOR = $(LINKER)
ENGINE_LIBRARY_OUTPUT_EXT = dll
else ifeq ($(EngineType), Static)
ENGINE_DEFINES += $(DF)METAMORPHIC_ENGINE_STATIC
LIBRARY_CREATOR = lib
ENGINE_LIBRARY_OUTPUT_EXT = lib
SANDBOX_DEFINES += $(DF)METAMORPHIC_ENGINE_STATIC
else
$(error invalid Engine Type specified)
endif

ifeq ($(BuildType), Editor)
	FILE_NAME = $(EDITOR_OUTPUT_DIR)$(EDITOR_TARGET_NAME)
	DLL_OUTPUT_DIR = $(EDITOR_OUTPUT_DIR)
else
	FILE_NAME = $(SANDBOX_OUTPUT_DIR)$(SANDBOX_TARGET_NAME)
	DLL_OUTPUT_DIR = $(SANDBOX_OUTPUT_DIR)
endif
default: build_all

full_clean:
	$(RM) bin-int
	$(RM) bin
clean:
	$(RM) "bin-int"
define f_make_folders
	$(MF) "$(ENGINE_OUTPUT_DIR)"
	$(MF) "$(ENGINE_INT_DIR)"
	$(MF) "$(SANDBOX_OUTPUT_DIR)"
	$(MF) "$(SANDBOX_INT_DIR)"
	$(MF) "$(EDITOR_OUTPUT_DIR)"
	$(MF) "$(EDITOR_INT_DIR)"
endef
define f_build_engine_pch
	$(CC) $(CRT) $(INCLUDE_DIRS) /c /Yc$(ENGINE_PCH_NAME).h /Fp$(ENGINE_INT_DIR)$(ENGINE_PCH_NAME).pch /Fo$(ENGINE_INT_DIR) src/Engine/$(ENGINE_PCH_NAME).cpp $(DEFINES) $(CFLAGS) $(ENGINE_DEFINES) $(ENGINE_INCLUDES)
endef

define f_build_engine
	$(CC) $(ENGINE_FILES) $(DEFINES) $(CRT) /c /Fo$(ENGINE_INT_DIR) $(IF)$(ENGINE_SRC) $(ENGINE_DEFINES) $(INCLUDE_DIRS) $(ENGINE_INCLUDES)
	
	$(LIBRARY_CREATOR) $(LFLAGS) $(OUTPUT_FLAG)$(ENGINE_OUTPUT_DIR)$(ENGINE_TARGET_NAME).$(ENGINE_LIBRARY_OUTPUT_EXT) $(ENGINE_INT_DIR)/*.obj $(ENGINE_LIB_PATHS) $(ENGINE_LIBS) $(LIB_DIRS) $(LIBS) $(ENGINE_LFLAGS)

	@if [ "$(EngineType)" = "Dynamic" ]; then \
		cp -f $(ENGINE_OUTPUT_DIR)$(ENGINE_TARGET_NAME).dll $(DLL_OUTPUT_DIR)$(ENGINE_TARGET_NAME).dll; \
	fi
endef

define f_build_editor_pch
	$(CC) $(CRT) $(INCLUDE_DIRS) /c /Yc$(EDITOR_PCH_NAME).h /Fp$(EDITOR_INT_DIR)$(EDITOR_PCH_NAME).pch /Fo$(EDITOR_INT_DIR) $(EDITOR_SRC)/$(EDITOR_PCH_NAME).cpp $(DEFINES) $(CFLAGS) $(EDITOR_DEFINES) $(EDITOR_INCLUDES)
endef

define f_build_editor
	$(CC) $(EDITOR_FILES) $(CRT) /c /Fo$(EDITOR_INT_DIR) $(IF)src/Engine $(DEFINES) $(EDITOR_DEFINES) $(INCLUDE_DIRS) $(EDITOR_INCLUDES)
	$(LINKER) $(LFLAGS) $(OUTPUT_FLAG)$(EDITOR_OUTPUT_DIR)$(EDITOR_TARGET_NAME).exe $(EDITOR_INT_DIR)/*.obj $(EDITOR_LIB_PATHS) $(EDITOR_LIBS) $(LIB_DIRS) $(LIBS) $(EDITOR_LFLAGS)  /LIBPATH:$(ENGINE_OUTPUT_DIR) $(ENGINE_TARGET_NAME).lib
endef
define f_build_sandbox 
	$(CC) $(SANDBOX_FILES) $(CRT) /c /Fo$(SANDBOX_INT_DIR) $(IF)src/Engine $(IF)src/SandboxApp $(INCLUDE_DIRS) $(SANDBOX_DEFINES) $(DEFINES)
	$(LINKER) $(OUTPUT_FLAG)$(SANDBOX_OUTPUT_DIR)/$(SANDBOX_TARGET_NAME).exe $(SANDBOX_INT_DIR)/*.obj $(LIB_DIRS) $(LIBS) $(LFLAGS) /LIBPATH:$(ENGINE_OUTPUT_DIR) $(ENGINE_TARGET_NAME).lib
endef

define f_build_engine_all
	$(call f_make_folders)
	$(call f_build_engine_pch)
	$(call f_build_engine)
endef

define f_rebuild_all:
	$(call clean)
	$(call f_build_all)
endef
push:
	push.bat
copy_engine_dll:
	cp -f $(ENGINE_OUTPUT_DIR)$(ENGINE_TARGET_NAME).dll $(DLL_OUTPUT_DIR)$(ENGINE_TARGET_NAME).dll;
make_folders:
	$(call f_make_folders)
rebuild_all:
	$(call f_rebuild_all)
build_engine_all:
	$(call f_build_engine_all)
build_engine_pch:
	$(call f_build_engine_pch)
build_engine:
	$(call f_build_engine)
build_sandbox:
	$(call f_build_sandbox)

run:
ifneq ($(Configuration), Dist)
	gdb -ex run -ex quit -ex "set args $(PROGRAM_ARGS)" $(FILE_NAME).exe
else
	$(FILE_NAME)
endif

help:
	@echo -- make make_folders
	@echo -- make push
	@echo -- make run
	@echo -- make rebuild_all

	@echo Engine specific

	@echo -- make build_engine_pch
	@echo -- make build_engine
	@echo -- make build_engine_all

	@echo Sandbox Specific
	@echo -- make build_sandbox