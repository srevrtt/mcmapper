import os
import sys
import pathlib

INCLUDE_DIRS = "-Idependencies -Idependencies/glfw/include -Idependencies/cglm/include"
LIB_DIRS = "-Lbuild/dependencies"
LIBS = "-lglfw3 -luser32 -lgdi32 -lopengl32 -lcglm"


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


path = pathlib.Path("src")
tmp_files = list(path.rglob("*"))
files = []

for f in tmp_files:
    filename = ""
    for part in f.parts:
        filename += part

        if not part.endswith(".c") and not part.endswith(".h"):
            filename += "/"

    filename.removesuffix("/")
    files.append(filename)

if len(sys.argv) == 1:
    prnt('Error: Please provide either "debug" or "release".', "red")

if not os.path.isdir("build"):
    os.mkdir("build")

if not os.path.isdir("build/objs"):
    os.mkdir("build/objs")

if not os.path.isdir("build/objs/ui"):
    os.mkdir("build/objs/ui")

if sys.argv[1] == "debug":
    if not os.path.isdir("build/debug"):
        os.mkdir("build/debug")

    for f in files:
        if f.endswith(".c"):
            obj_name = f[4:-2]
            obj_name += ".o"

            prnt('Building "' + f + '"', "blue")
            if (
                os.system(
                    "gcc -c " + f + " -o build/objs/" + obj_name + " " + INCLUDE_DIRS
                )
                == 1
            ):
                prnt("Error: Failed to build " + f + '"!', "red")

    prnt('Building "dependencies/glad/glad.c"', "blue")
    os.system("gcc -c dependencies/glad/glad.c -o build/objs/glad.o " + INCLUDE_DIRS)

    prnt("Linking build/debug/MCMapper", "blue")
    if (
        os.system(
            "gcc build/objs/*.o build/objs/ui/*.o -o build/debug/MCMapper "
            + LIB_DIRS
            + " "
            + LIBS
        )
        == 1
    ):
        prnt('Error: Failed to link "build/debug/MCMapper"!', "red")

    prnt("Successfully built a debug build!", "green")

if sys.argv[1] == "release":
    if not os.path.isdir("build/release"):
        os.mkdir("build/release")

    for f in files:
        if f.endswith(".c"):
            obj_name = f[4:-2]
            obj_name += ".o"

            prnt('Building "' + f + '"', "blue")
            if os.system("gcc -c " + f + " -o build/objs/" + obj_name + " -Ofast") == 1:
                prnt('Error: Failed to build "' + f + '"!', "red")

    prnt('Building "dependencies/glad/glad.c"', "blue")
    os.system(
        "gcc -c dependencies/glad/glad.c -o build/objs/glad.o -Ofast " + INCLUDE_DIRS
    )

    prnt("Linking build/release/MCMapper", "blue")
    if (
        os.system(
            "gcc build/objs/*.o build/objs/ui/*.o -o build/release/MCMapper "
            + LIB_DIRS
            + " "
            + LIBS
        )
        == 1
    ):
        prnt('Error: Failed to link "build/release/MCMapper"!', "red")

    prnt("Successfully built a release build!", "green")
