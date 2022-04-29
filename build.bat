IF EXIST %~dp0build RMDIR  /S /Q %~dp0build

mkdir build && cd build
cmake -G "MinGW Makefiles" ..

cd ../build
mingw32-make