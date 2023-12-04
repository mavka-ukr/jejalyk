set -e

TARGET=$1

if [ "$TARGET" = "" ]; then
    echo "Usage: build.sh <antlr4|wasm>"
    exit 1
fi

if [ "$TARGET" = "antlr4" ]; then
    cd parser
    java -jar antlr-4.13.0-complete.jar -Dlanguage=Cpp *.g4 -visitor
    cd ..
fi

if [ "$TARGET" = "wasm" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 jejalyk_wasm
    cd ..
fi