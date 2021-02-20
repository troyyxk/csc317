# rm build -rf
# mkdir build
# cd build
# cmake ..
# make

cd C:\Users\yxk\Documents\github\2021_winter_term\CSC317\assignments\a5\computer-graphics-meshes

rm build_release -rf
mkdir build_release
cd build_release
cmake -DCMAKE_BUILD_TYPE=Release .. 
# cmake --config Release -DCMAKE_BUILD_TYPE=Release .. 
# cmake --build {BUILD_DIR} --config Release
# cmake -DCMAKE_BUILD_TYPE=Release --no-warn-unused-cli ..
make 
