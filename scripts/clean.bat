@echo off
 
set buildDir=%~dp0..\build
set objDir=.\obj\
set assetDir=.\assets\
 
if exist %buildDir% (  
  pushd %buildDir%
  del /q /s *.exe *.pdb *.ilk *.dll
  rd /s /q %objDir%
  if exist %assetDir% rd /s /q %assetDir%
  popd
)