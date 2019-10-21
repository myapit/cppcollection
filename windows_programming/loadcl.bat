@echo off
REM %comspec% /c ""C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86 && cl.exe %*"
"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86

REM "Change path to your vcvarall.bat path. (hint: use search to locate exact path)"