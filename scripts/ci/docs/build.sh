#!/bin/bash
set -ev
echo "Building OF documentation"
ROOT=${TRAVIS_BUILD_DIR:-"$( cd "$(dirname "$0")/../../.." ; pwd -P )"}
# cd $ROOT/scripts/ofDocGenerator

echo $ROOT


# npm run start



#
# git config --global user.name "Travis-CI"
# git config --global user.email ${GIT_EMAIL}
# cd docs/; doxygen Doxyfile; cd ..
#
# echo "Start ofDoc publishing"
#
# rm -rf ghpages || exit 0;
# git clone --branch=gh-pages https://github.com/HalfdanJ/ofDocGenerator.git ghpages
# cp -R output/* ghpages/
# (
# 	cd ghpages;
# 	git add --all .;
# 	git commit -m "Travis auto ofDoc generation";
# 	git remote set-url origin "https://${GIT_TOKEN}@github.com/HalfdanJ/ofDocGenerator.git"
# 	git push -fq origin gh-pages  > /dev/null 2>&1
# )
#
# echo "Publishing done"
