#!/bin/bash
set -ev
echo "Building OF documentation"
ROOT=${TRAVIS_BUILD_DIR:-"$( cd "$(dirname "$0")/../../.." ; pwd -P )"}
# cd $ROOT/scripts/ofDocGenerator
cd docs/; doxygen Doxyfile; cd ..

ls -la
