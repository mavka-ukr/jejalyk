set -e
set -x

TARGET=$1

if [ "$TARGET" = "wclean" ]; then
    rm -rf ./build
fi

./build.sh Oall

cp -a ./build/optimized_jejalyk_node.js ./dist/optimized_jejalyk_node.js
cp -a ./build/optimized_jejalyk_node.wasm ./dist/optimized_jejalyk_node.wasm

cp -a ./build/optimized_jejalyk_web.js ./dist/optimized_jejalyk_web.js
cp -a ./build/optimized_jejalyk_web.wasm ./dist/optimized_jejalyk_web.wasm