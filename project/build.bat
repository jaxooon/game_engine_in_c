set io=src\engine\io\io.c
set render=src\engine\render\render.c src\engine\render\render_init.c src\engine\render\render_util.c
set files=src\glad.c src\main.c src\engine\global.c %render% %io%
set libs=C:\Users\jackson.barr\Documents\development\C_Game_Engine_Project\lib\glfw3.lib User32.lib Gdi32.lib Shell32.lib opengl32.lib msvcrtd.lib /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrtd.lib

CL /Od /Zi /I C:\Users\jackson.barr\Documents\development\C_Game_Engine_Project\include %files% /link %libs% /OUT:mygame.exe 

start mygame.exe