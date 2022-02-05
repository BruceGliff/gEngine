# Goto binary directory
BuildType=Debug
mkdir -p build
cd build

#Generate solution for different OS'es. <..> because CMakeLists.txt in project/ but project will be created in project/build/
cmake -DCMAKE_BUILD_TYPE=$BuildType ..

#Build solution. <.> becuse project in project/build/
cmake --build . --config $BuildType -j ${nproc}

cd ..
