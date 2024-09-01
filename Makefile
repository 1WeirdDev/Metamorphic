CC      = cl
LINKER	= link
LIBRARY_CREATOR = lib
RM      = rm -r 
RF      = rd /s /q
MF 		= mkdir -p

#Include Flag
IF =/I
#Define Flag
DF =/D
#Define Lib Path Flag
LPF = /LibPath:
#Output Flag
OUTPUT_FLAG = /out:

#Platforms Can be Windows, Console, or UWP
#Engine Type can be Static | Dynamic
#build type can be Editor | Sandbox
#RenderingAPI can be OpenGL | DirectX

Platform=Windows
CONFIGURATION =Release
EngineType = Static
BuildType = Sandbox
RenderingAPI = DirectX

ENGINE_TARGET_NAME = MetamorphicEngine
SANDBOX_TARGET_NAME = SandboxApp
EDITOR_TARGET_NAME = MetamorphicEditor


#	--- Start of Output and Int folders ---
ENGINE_OUTPUT_DIR = bin/Engine/$(Platform)/$(CONFIGURATION)-$(EngineType)/
ENGINE_INT_DIR = bin-int/Engine/$(Platform)/$(CONFIGURATION)-$(EngineType)/
SANDBOX_OUTPUT_DIR = bin/SandboxApp/$(CONFIGURATION)-$(EngineType)/
SANDBOX_INT_DIR = bin-int/SandboxApp/$(CONFIGURATION)-$(EngineType)/
EDITOR_OUTPUT_DIR = bin/Editor/$(CONFIGURATION)-$(EngineType)/
EDITOR_INT_DIR = bin-int/Editor/$(CONFIGURATION)-$(EngineType)/
#	--- End of output and int folders	---

ENGINE_SRC = src/Engine/
MORPHIC_SRC = $(ENGINE_SRC)Metamorphic/
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
SUBSYSTEM =
INCLUDE_DIRS += $(IF)libs/spdlog/include

ENGINE_FILES =
ENGINE_DEFINES =$(DF)METAMORPHIC_ENGINE_BUILD
EDITOR_DEFINES =$(DF)METAMORPHIC_EDITOR_BUILD

ifeq ($(CONFIGURATION), Debug)
DEFINES +=$(DF)METAMORPHIC_ENGINE_BUILD_DEBUG
CFLAGS +=  /Zi /Od
else ifeq ($(CONFIGURATION), Release)
DEFINES +=$(DF)METAMORPHIC_ENGINE_BUILD_RELEASE
CFLAGS += /GR- /O2 /GL /Ot
LFLAGS += /LTCG
else
DEFINES +=$(DF)METAMORPHIC_ENGINE_BUILD_DIST
CFLAGS += /GR- /O2 /GL /Ot
LFLAGS += /LTCG /OPT:REF
SUBSYSTEM = /SUBSYSTEM:WINDOWS
endif

#core files
ENGINE_FILES += $(MORPHIC_SRC)/Application.cpp $(MORPHIC_SRC)/Logger.cpp $(MORPHIC_SRC)/Objects/Component/Component.cpp $(MORPHIC_SRC)/Objects/GameObject.cpp
ENGINE_FILES += $(MORPHIC_SRC)/Scene/Scene.cpp $(MORPHIC_SRC)/Scene/SceneManager.cpp
EDITOR_FILES += $(EDITOR_SRC)/Main.cpp
SANDBOX_FILES += src/SandboxApp/SandboxApp.cpp

ifeq ($(Platform), Windows)
DEFINES += /DMETAMORPHIC_PLATFORM=Windows
LIBS+=GDI32.lib Shell32.lib kernel32.lib User32.lib
ENGINE_LFLAGS += /MACHINE:X64
ENGINE_FILES += $(ENGINE_SRC)Platforms/DesktopInput.cpp

ifeq ($(RenderingAPI), OpenGL)
EDITOR_DEFINES +=$(DF)GLEW_STATIC $(DF)METAMORPHIC_USE_OPENGL
EDITOR_INCLUDES += $(IF)libs/GLFW3.4/x64/include $(IF)libs/glew-2.2.0/include $(IF)libs/spdlog/include
EDITOR_LIB_PATHS += /LIBPATH:"libs/GLFW3.4/x64/lib-vc2022" /LIBPATH:"libs/glew-2.2.0/libs/x64"
EDITOR_LIBS += glfw3.lib glew32s.lib opengl32.lib

ENGINE_FILES += src/Engine/Platforms/GLFWWindow.cpp
ENGINE_DEFINES += $(DF)GLEW_STATIC $(DF)METAMORPHIC_USE_OPENGL
ENGINE_INCLUDES += $(IF)libs/GLFW3.4/x64/include $(IF)libs/glew-2.2.0/include $(IF)libs/spdlog/include
ENGINE_LIB_PATHS += /LIBPATH:"libs/GLFW3.4/x64/lib-vc2022" /LIBPATH:"libs/glew-2.2.0/libs/x64"
ENGINE_LIBS += glfw3.lib glew32s.lib opengl32.lib
else ifeq ($(RenderingAPI), DirectX)
ENGINE_DEFINES += $(DF)METAMORPHIC_USE_DIRECTX
ENGINE_FILES += $(ENGINE_SRC)Platforms/DirectXWindow.cpp

EDITOR_DEFINES += $(DF)METAMORPHIC_USE_DIRECTX
else
$(error Invalid Rendering API)
endif

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
else
	FILE_NAME = $(SANDBOX_OUTPUT_DIR)$(SANDBOX_TARGET_NAME)
endif
default: build_all

full_clean:
	$(RM) bin-int
	$(RM) bin
clean:
	$(RM) "bin-int"
make_folders:
	$(MF) "$(ENGINE_OUTPUT_DIR)"
	$(MF) "$(ENGINE_INT_DIR)"
	$(MF) "$(SANDBOX_OUTPUT_DIR)"
	$(MF) "$(SANDBOX_INT_DIR)"
	$(MF) "$(EDITOR_OUTPUT_DIR)"
	$(MF) "$(EDITOR_INT_DIR)"
build_engine_pch:
	$(CC) $(CRT) $(INCLUDE_DIRS) /c /Yc$(ENGINE_PCH_NAME).h /Fp$(ENGINE_INT_DIR)$(ENGINE_PCH_NAME).pch /Fo$(ENGINE_INT_DIR) src/Engine/$(ENGINE_PCH_NAME).cpp $(DEFINES) $(CFLAGS) $(ENGINE_DEFINES) $(ENGINE_INCLUDES)
build_editor_pch:
	$(CC) $(CRT) $(INCLUDE_DIRS) /c /Yc$(EDITOR_PCH_NAME).h /Fp$(EDITOR_INT_DIR)$(EDITOR_PCH_NAME).pch /Fo$(EDITOR_INT_DIR) $(EDITOR_SRC)/$(EDITOR_PCH_NAME).cpp $(DEFINES) $(CFLAGS) $(EDITOR_DEFINES) $(EDITOR_INCLUDES)
build_engine:
	$(CC) $(ENGINE_FILES) $(DEFINES) $(CRT) /c /Fo$(ENGINE_INT_DIR) $(IF)src/Engine $(ENGINE_DEFINES) $(INCLUDE_DIRS) $(ENGINE_INCLUDES)
	$(LIBRARY_CREATOR) $(OUTPUT_FLAG)$(ENGINE_OUTPUT_DIR)$(ENGINE_TARGET_NAME).$(ENGINE_LIBRARY_OUTPUT_EXT) $(ENGINE_INT_DIR)/*.obj $(ENGINE_LIB_PATHS) $(ENGINE_LIBS) $(LIB_DIRS) $(LIBS) $(ENGINE_LFLAGS)

define build_editor
	$(CC) $(EDITOR_FILES) $(CRT) /c /Fo$(EDITOR_INT_DIR) $(IF)src/Engine $(DEFINES) $(EDITOR_DEFINES) $(INCLUDE_DIRS) $(EDITOR_INCLUDES)
	$(LINKER) /out:$(EDITOR_OUTPUT_DIR)$(EDITOR_TARGET_NAME).exe $(EDITOR_INT_DIR)/*.obj $(EDITOR_LIB_PATHS) $(EDITOR_LIBS) $(LIB_DIRS) $(LIBS) $(EDITOR_LFLAGS)  /LIBPATH:$(ENGINE_OUTPUT_DIR) $(ENGINE_TARGET_NAME).lib
@if [ "$(EngineType)" = "Dynamic" ]; then \
	cp $(ENGINE_OUTPUT_DIR)$(ENGINE_TARGET_NAME).dll $(EDITOR_OUTPUT_DIR)$(ENGINE_TARGET_NAME).dll; \
fi
endef

define build_sandbox
	$(CC) $(SANDBOX_FILES) $(CRT) /c /Fo$(SANDBOX_INT_DIR) $(IF)src/Engine $(IF)src/SandboxApp $(INCLUDE_DIRS) $(SANDBOX_DEFINES) $(DEFINES)
	$(LINKER) /OUT:$(SANDBOX_OUTPUT_DIR)/$(SANDBOX_TARGET_NAME).exe $(SANDBOX_INT_DIR)/*.obj $(SUBSYSTEM) $(LIB_DIRS) $(LIBS) $(LFLAGS) /LIBPATH:$(ENGINE_OUTPUT_DIR) $(ENGINE_TARGET_NAME).lib

@if [ "$(EngineType)" = "Dynamic" ]; then \
	cp $(ENGINE_OUTPUT_DIR)$(ENGINE_TARGET_NAME).dll $(SANDBOX_OUTPUT_DIR)$(ENGINE_TARGET_NAME).dll; \
fi
endef
build_all:
	$(call make_folders)
ifeq ($(BuildType), Editor)
	$(call build_editor)
else
	$(call build_sandbox)
endif
build_sandbox_all: make_folders build_engine build_sandbox
run:
ifneq ($(CONFIGURATION), Dist)
	gdb -ex run -ex quit -ex "set args $(PROGRAM_ARGS)" $(FILE_NAME).exe
else
	$(FILE_NAME)
endif
push:
	push.bat