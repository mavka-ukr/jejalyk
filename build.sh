set -e

TARGET=$1

if [ "$TARGET" = "" ]; then
    echo "Usage: build.sh <antlr4|node|web|Onode|Oweb>"
    exit 1
fi

if [ "$TARGET" = "antlr4" ]; then
    cd parser
    java -jar antlr-4.13.0-complete.jar -Dlanguage=Cpp *.g4 -visitor
    cd ..
fi

if [ "$TARGET" = "node" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 jejalyk_node
    cd ..
fi

if [ "$TARGET" = "web" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 jejalyk_web
    cd ..
fi

if [ "$TARGET" = "Onode" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 optimized_jejalyk_node
    cd ..
fi

if [ "$TARGET" = "Oweb" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 optimized_jejalyk_web
    cd ..
fi