set -e

TARGET=$1

if [ "$TARGET" = "" ]; then
    echo "Usage: build.sh <main|wasm>"
    exit 1
fi

#cd parser
#java -jar antlr-4.13.0-complete.jar -Dlanguage=Cpp *.g4 -visitor
#cd ..

if [ "$TARGET" = "main" ]; then
    mkdir -p build
    cd build
    cmake ..
    make -j4 main
    cd ..
fi

if [ "$TARGET" = "wasm" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 jejalyk_wasm
    cd ..
fi