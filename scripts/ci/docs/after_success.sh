#!/bin/bash
set -ev
echo "Publishing docs."

if [[ $TRAVIS_PULL_REQUEST == "false" ]]; then

# Generate doxygen files.
cd docs/;
doxygen Doxyfile;

ls -la

# Publish html.
git config --global user.name "Travis-CI"
git config --global user.email ${GIT_EMAIL}

# rm -rf gh-pages || exit 0;
git clone --branch=gh-pages https://github.com/${TRAVIS_REPO_SLUG}.git gh-pages

ls -la
ls -la html/

cp -R html/* gh-pages/
(
	cd gh-pages;
	git add --all .;
	git commit -m "Travis ofxAddon documentation generation.";
	git remote set-url origin "https://${GIT_TOKEN}@github.com/${TRAVIS_REPO_SLUG}.git"
	git push -fq origin gh-pages > /dev/null 2>&1
)

cd ..

else
    echo "Skipping document generation since this is a pull request.";
fi
