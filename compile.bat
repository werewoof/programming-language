nasm -f win64 -o out.obj out.asm
link "out.obj" /subsystem:console /entry:main /defaultlib:ucrt.lib /defaultlib:msvcrt.lib /defaultlib:legacy_stdio_definitions.lib /defaultlib:Kernel32.lib /nologo /incremental:no  /opt:ref /out:"out.exe"
out