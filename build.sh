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
    exit 0
fi

MAVKA_HEAD_JS=$(cat голова.js)
#MAVKA_HEAD_JS=$(./node_modules/.bin/uglifyjs голова.js)
MAVKA_HEAD_M=$(cat голова.м)

echo "std::string MAVKA_HEAD_JS = R\"($MAVKA_HEAD_JS)\";
std::string MAVKA_HEAD_M = R\"($MAVKA_HEAD_M)\";
" >head.h

if [ "$TARGET" = "bin" ] || [ "$TARGET" = "all" ]; then
    mkdir -p build-bin
    cd build-bin
    cmake ..
    make -j4 jejalyk
    cd ..
fi

if [ "$TARGET" = "node" ] || [ "$TARGET" = "all" ]; then
    mkdir -p build-node
    cd build-node
    emcmake cmake ..
    emmake make -j4 jejalyk_node
    cd ..
fi

if [ "$TARGET" = "web" ] || [ "$TARGET" = "all" ]; then
    mkdir -p build-web
    cd build-web
    emcmake cmake ..
    emmake make -j4 jejalyk_web
    cd ..
fi

if [ "$TARGET" = "Obin" ] || [ "$TARGET" = "Oall" ]; then
    mkdir -p build-Obin
    cd build-Obin
    cmake ..
    make -j4 optimized_jejalyk
    cd ..
fi

if [ "$TARGET" = "Onode" ] || [ "$TARGET" = "Oall" ]; then
    mkdir -p build-Onode
    cd build-Onode
    emcmake cmake ..
    emmake make -j4 optimized_jejalyk_node
    cd ..
fi

if [ "$TARGET" = "Oweb" ] || [ "$TARGET" = "Oall" ]; then
    mkdir -p build-Oweb
    cd build-Oweb
    emcmake cmake ..
    emmake make -j4 optimized_jejalyk_web
    cd ..
fi