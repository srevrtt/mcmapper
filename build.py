import os
import sys

INCLUDE_DIRS = "-Idependencies -Idependencies/glfw/include -Idependencies/cglm/include"
LIB_DIRS = "-Lbuild/dependencies"
LIBS = "-lglfw3 -lopengl32 -lcglm"


def prnt(msg: str, color: str):
    if os.name == "nt":
        if color == "green":
            os.system('powershell Write-Host "' + msg + '" -ForegroundColor Green')
        elif color == "red":
            os.system('powershell Write-Host "' + msg + '" -ForegroundColor Red')
            exit(1)
        elif color == "blue":
            os.system('powershell Write-Host "' + msg + '" -ForegroundColor Blue')

    if os.name == "posix":
        if color == "blue":
            os.system('printf \\033[0;32m"' + msg + "\\033[0m")
        elif color == "red":
            os.system('printf \\033[0;32m"' + msg + "\\033[0m")
            exit(1)
        else:
            os.system('printf \\033[0;31m"' + msg + "\\033[0m")


files = os.listdir("src")

if len(sys.argv) == 1:
    prnt('Error: Please provide either "debug" or "release".', "red")

if not os.path.isdir("build"):
    os.mkdir("build")

if not os.path.isdir("build/objs"):
    os.mkdir("build/objs")

if sys.argv[1] == "debug":
    if not os.path.isdir("build/debug"):
        os.mkdir("build/debug")

    for f in files:
        if f.endswith(".c"):
            obj_name = f[:-2]
            obj_name += ".o"

            prnt('Building "src/' + f + '"', "blue")
            if os.system("gcc -c src/" + f + " -o build/objs/" + obj_name) == 1:
                prnt('Error: Failed to build "src/' + f + '"!', "red")

    prnt('Building "dependencies/glad/glad.c"', "blue")
    os.system("gcc -c dependencies/glad/glad.c -o build/objs/glad.o " + INCLUDE_DIRS)

    prnt("Linking build/debug/MCMapper", "blue")
    if (
        os.system("gcc build/objs/*.o -o build/debug/MCMapper " + LIB_DIRS + " " + LIBS)
        == 1
    ):
        prnt('Error: Failed to link "build/debug/MCMapper"!', "red")

    prnt("Successfully built a debug build!", "green")

if sys.argv[1] == "release":
    if not os.path.isdir("build/release"):
        os.mkdir("build/release")

    for f in files:
        if f.endswith(".c"):
            obj_name = f[:-2]
            obj_name += ".o"

            prnt('Building "src/' + f + '"', "blue")
            if (
                os.system("gcc -c src/" + f + " -o build/objs/" + obj_name + " -Ofast")
                == 1
            ):
                prnt('Error: Failed to build "src/' + f + '"!', "red")

    prnt('Building "dependencies/glad/glad.c"', "blue")
    os.system(
        "gcc -c dependencies/glad/glad.c -o build/objs/glad.o -Ofast " + INCLUDE_DIRS
    )

    prnt("Linking build/release/MCMapper", "blue")
    if (
        os.system(
            "gcc build/objs/*.o -o build/release/MCMapper " + LIB_DIRS + " " + LIBS
        )
        == 1
    ):
        prnt('Error: Failed to link "build/release/MCMapper"!', "red")

    prnt("Successfully built a release build!", "green")
