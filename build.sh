rm -r build
mkdir build
cd build
cmake ..
make 
./Json_finder
./tests/tests
cd ..