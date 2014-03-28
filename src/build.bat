echo off
cl main.c /I ../libs/glut/include /MTd /TC /link ../libs/glut/lib/glut.lib ../libs/glut/lib/glut32.lib
@if ERRORLEVEL == 0 (
   goto good
)

@if ERRORLEVEL != 0 (
   goto bad
)

:good
   echo "clean compile"
   echo %ERRORLEVEL%
   goto end

:bad
   echo "error or warning"
   echo %ERRORLEVEL%
   goto end

:end