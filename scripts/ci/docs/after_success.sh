#!/bin/bash
set -ev
echo "Publishing docs."
# if [[ $TRAVIS_PULL_REQUEST == "false" ]]; then
git config --global user.name "Travis-CI"
git config --global user.email ${GIT_EMAIL}

echo "ofxAddon documentation publishing"

# rm -rf gh-pages || exit 0;
git clone --branch=gh-pages https://github.com/${TRAVIS_REPO_SLUG}.git gh-pages

echo "Here ..."

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

echo "Publishing done"
# else
#     echo "Skipping document generation since this is a pull request.";
# fi
