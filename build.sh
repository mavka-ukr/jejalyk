set -e

TARGET=$1

if [ "$TARGET" = "" ]; then
    echo "Usage: build.sh <antlr4|bin|node|web|all|Obin|Onode|Oweb|Oall>"
    exit 1
fi

if [ "$TARGET" = "antlr4" ]; then
    cd syntax
    java -jar antlr-4.13.0-complete.jar -Dlanguage=Cpp *.g4 -visitor
    cd ..
fi

if [ "$TARGET" = "bin" ] || [ "$TARGET" = "all" ]; then
    mkdir -p build
    cd build
    cmake ..
    make -j4 jejalyk
    cd ..
fi

if [ "$TARGET" = "node" ] || [ "$TARGET" = "all" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 jejalyk_node
    cd ..
fi

if [ "$TARGET" = "web" ] || [ "$TARGET" = "all" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 jejalyk_web
    cd ..
fi

if [ "$TARGET" = "Obin" ] || [ "$TARGET" = "Oall" ]; then
    mkdir -p build
    cd build
    cmake ..
    make -j4 optimized_jejalyk
    cd ..
fi

if [ "$TARGET" = "Onode" ] || [ "$TARGET" = "Oall" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 optimized_jejalyk_node
    cd ..
fi

if [ "$TARGET" = "Oweb" ] || [ "$TARGET" = "Oall" ]; then
    mkdir -p build
    cd build
    emcmake cmake ..
    emmake make -j4 optimized_jejalyk_web
    cd ..
fi