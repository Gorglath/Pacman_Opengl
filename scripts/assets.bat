set buildDir=%~dp0..\build
set assetsDir=%~dp0..\assets
set extDir=%~dp0..\external

:: Copy dependencies
if not exist %buildDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.12\lib\x64\SDL2.dll %buildDir%
if not exist %buildDir%\SDL2_image.dll xcopy /y %extDir%\SDL2_image-2.0.5\lib\x64\SDL2_image.dll %buildDir%
if not exist %buildDir%\libjpeg-9.dll xcopy /y %extDir%\SDL2_image-2.0.5\lib\x64\libjpeg-9.dll %buildDir%
if not exist %buildDir%\libpng16-16.dll xcopy /y %extDir%\SDL2_image-2.0.5\lib\x64\libpng16-16.dll %buildDir%
if not exist %buildDir%\zlib1.dll xcopy /y %extDir%\SDL2_image-2.0.5\lib\x64\zlib1.dll %buildDir%
if not exist %buildDir%\glew32.dll xcopy /y %extDir%\glew-2.1.0\bin\Release\x64\glew32.dll %buildDir%
if not exist %buildDir%\libFLAC-8.dll xcopy /y %extDir%\SDL2_mixer-2.0.4\lib\x64\libFLAC-8.dll %buildDir%
if not exist %buildDir%\libmodplug-1.dll xcopy /y %extDir%\SDL2_mixer-2.0.4\lib\x64\libmodplug-1.dll %buildDir%
if not exist %buildDir%\libmpg123-0.dll xcopy /y %extDir%\SDL2_mixer-2.0.4\lib\x64\libmpg123-0.dll %buildDir%
if not exist %buildDir%\libogg-0.dll xcopy /y %extDir%\SDL2_mixer-2.0.4\lib\x64\libogg-0.dll %buildDir%
if not exist %buildDir%\libopus-0.dll xcopy /y %extDir%\SDL2_mixer-2.0.4\lib\x64\libopus-0.dll %buildDir%
if not exist %buildDir%\libopusfile-0.dll xcopy /y %extDir%\SDL2_mixer-2.0.4\lib\x64\libopusfile-0.dll %buildDir%
if not exist %buildDir%\liborbis-0.dll xcopy /y %extDir%\SDL2_mixer-2.0.4\lib\x64\liborbis-0.dll %buildDir%
if not exist %buildDir%\liborbisfile-0.dll xcopy /y %extDir%\SDL2_mixer-2.0.4\lib\x64\liborbisfile-0.dll %buildDir%
if not exist %buildDir%\SDL2_mixer.dll xcopy /y %extDir%\SDL2_mixer-2.0.4\lib\x64\SDL2_mixer.dll %buildDir%
if not exist %buildDir%\SDL2_ttf.dll xcopy /y %extDir%\SDL2_ttf-2.0.15\lib\x64\SDL2_ttf.dll %buildDir%
if not exist %buildDir%\libfreetype-6.dll xcopy /y %extDir%\SDL2_ttf-2.0.15\lib\x64\libfreetype-6.dll %buildDir%

:: Copy assets
if not exist %buildDir%\assets mkdir %buildDir%\assets
xcopy /y /s %assetsDir% %buildDir%\assets