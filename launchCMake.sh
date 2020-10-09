# Goto binary directory
mkdir bin
cd bin

#Generate solution for different OS'es. <..> because CMakeLists.txt in project/ but project will be created in project/bin/
cmake ..

#Build solution. <.> becuse project in project/bin/
cmake --build . --config Release

cd ..