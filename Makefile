# Keep this Makefile intentionally simple.
# This Makefile targets nmake + MSVC.

RAYLIB_ROOT = raylib\raylib-5.5_win64_msvc16
RAYGUI_ROOT = raylib\raygui-4.0
RPNG_ROOT = raylib\rpng-1.5
RRES_ROOT = raylib\rres-1.2.0

CXX = cl
APP = build\game.exe
SRCS = src\main.cpp src\game.cpp

CXXFLAGS = /nologo /std:c++17 /W4 /EHsc /MD /I"$(RAYLIB_ROOT)\include" /I"$(RAYGUI_ROOT)\src" /I"$(RPNG_ROOT)\src" /I"$(RRES_ROOT)\src"
LDFLAGS = /link /LIBPATH:"$(RAYLIB_ROOT)\lib" raylibdll.lib opengl32.lib gdi32.lib winmm.lib user32.lib shell32.lib

all: $(APP)

$(APP): $(SRCS)
	if not exist build mkdir build
	$(CXX) $(CXXFLAGS) /Fo"build\\" $(SRCS) /Fe:$(APP) $(LDFLAGS)
	if exist "$(RAYLIB_ROOT)\lib\raylib.dll" copy /Y "$(RAYLIB_ROOT)\lib\raylib.dll" "build\raylib.dll" >NUL

run: $(APP)
	set "PATH=%CD%\$(RAYLIB_ROOT)\lib;%PATH%" && $(APP)

clean:
	if exist build rmdir /s /q build
	if exist *.obj del /q *.obj
