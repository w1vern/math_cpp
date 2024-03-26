rmdir /s /q export
mkdir export
mkdir export\include
xcopy build\*.dll export
xcopy build\*.a export
xcopy build\*.lib export
xcopy include export\include
