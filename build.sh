set -e

#cd parser
#java -jar antlr-4.13.0-complete.jar -Dlanguage=Cpp *.g4 -visitor
#cd ..

mkdir -p build
cd build
cmake ..
make -j4
cd ..