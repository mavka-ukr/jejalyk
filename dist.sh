set -e

JEJALYK_VERSION_FROM_PACKAGE=$(cat package.json | grep version | head -n 1 | cut -d '"' -f 4)
if [ -e dist ]; then
    JEJALYK_VERSION_FROM_DIST=$(cat dist/VERSION)

    if [ "$JEJALYK_VERSION_FROM_PACKAGE" == "$JEJALYK_VERSION_FROM_DIST" ]; then
        echo "Version $JEJALYK_VERSION_FROM_PACKAGE already in the dist."
        exit 1
    fi
fi

TARGET=$1

set -x

if [ "$TARGET" = "wclean" ]; then
    rm -rf ./build-wasm
fi

mkdir -p ./dist

./build.sh Onode
cp -a ./build-Onode/optimized_jejalyk_node.js ./dist/optimized_jejalyk_node.js
cp -a ./build-Onode/optimized_jejalyk_node.wasm ./dist/optimized_jejalyk_node.wasm

./build.sh Oweb
cp -a ./build-Oweb/optimized_jejalyk_web.js ./dist/optimized_jejalyk_web.js
cp -a ./build-Oweb/optimized_jejalyk_web.wasm ./dist/optimized_jejalyk_web.wasm

echo -en "$JEJALYK_VERSION_FROM_PACKAGE" >./dist/VERSION