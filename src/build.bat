echo off
DEL main.exe

cl main.c /I ../libs/glut/include /link ../libs/glut/lib/glut32.lib

main.exe