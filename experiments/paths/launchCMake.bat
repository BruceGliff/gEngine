:: Goto binary directory
mkdir build
cd build

:: Generate solution for different OS'es. <..> because CMakeLists.txt in project/ but project will be created in project/build/
cmake ..

:: Build solution. <.> becuse project in project/build/
cmake --build . --config Release

cd ..