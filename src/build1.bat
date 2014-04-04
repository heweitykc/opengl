echo off
DEL test1.exe

cl test1.c /MDd /I ../libs/glut/include /link ../libs/glut/lib/glut32.lib ../libs/glut/lib/glew32d.lib

test1.exe