set -e

mkdir -p build
cd build
emcmake cmake ..
emmake make -j4
cd ..