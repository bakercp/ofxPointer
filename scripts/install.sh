#!/usr/bin/env bash
set -e

if [ "$CI" = true ];
then
  OF_ROOT=~/openFrameworks
  OF_ADDONS_DIR=$OF_ROOT/addons

  THIS_ADDON_NAME=${TRAVIS_REPO_SLUG#*/}
  THIS_ADDON_DIR=$TRAVIS_BUILD_DIR
  THIS_USERNAME=${TRAVIS_REPO_SLUG%/*}
  THIS_BRANCH=$TRAVIS_BRANCH
else
  OF_ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )/../../../.." && pwd )
  OF_ADDONS_DIR=$OF_ROOT/addons

  THIS_ADDON_NAME=$(basename $( cd "$( dirname "${BASH_SOURCE[0]}")/../.."  && pwd ))
  THIS_ADDON_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}")/../.."  && pwd )
  THIS_USERNAME=$(whoami)
  THIS_BRANCH=`git rev-parse --abbrev-ref HEAD`
fi

echo "        OF_ROOT: ${OF_ROOT}"
echo "  OF_ADDONS_DIR: ${OF_ADDONS_DIR}"
echo "THIS_ADDON_NAME: ${THIS_ADDON_NAME}"
echo " THIS_ADDON_DIR: ${THIS_ADDON_DIR}"
echo "  THIS_USERNAME: ${THIS_USERNAME}"
echo "    THIS_BRANCH: ${THIS_BRANCH}"

extract_required_addons()
{
  if [ -z "$1" ]; then
    echo "Usage: extract_addons <path_to_addon>"
    return 1
  fi
  # Extract ADDON_DEPENDENCIES from THIS ADDON's addon_config.mk file.
  if [ -f ${1}/addon_config.mk ]; then
    REQUIRED_ADDONS=""
    while read line; do
      if [[ $line == ADDON_DEPENDENCIES* ]] ;
      then
        line=${line#*=}
        IFS=' ' read -ra ADDR <<< "$line"
        for i in "${ADDR[@]}"; do
          REQUIRED_ADDONS="${REQUIRED_ADDONS} ${i}"
        done
      fi
    done < ${1}/addon_config.mk
    echo $REQUIRED_ADDONS
  fi
  return 0
}

download_required_addons()
{
  if [ -z "$1" ]; then
    echo "Usage: List of addons to download."
    return 1
  fi

  for addon in "$@"
  do
    if [ ! -d ${OF_ADDONS_DIR}/${addon} ]; then
      echo "Installing: ${OF_ADDONS_DIR}/${addon}"
      git clone --depth=1 -b ${THIS_BRANCH} https://github.com/${THIS_USERNAME}/${addon}.git ${OF_ADDONS_DIR}/${addon}

      REQUIRED_ADDONS=$(extract_required_addons ${OF_ADDONS_DIR}/${addon})

      for required_addon in $REQUIRED_ADDONS
      do
        if [ ! -d ${OF_ADDONS_DIR}/${required_addon} ]; then
          download_required_addons ${required_addon}
        else
          echo "Dependency satisfied: ${required_addon}"
        fi
      done
    fi
  done
  return 0
}


# Gather required addons for THIS_ADDON.
REQUIRED_ADDONS=$(extract_required_addons ${THIS_ADDON_DIR})

# Gather required addons from all examples.
for addons_make in ${THIS_ADDON_DIR}/example*/addons.make; do
  while read addon; do
    if [ ${addon} != ${THIS_ADDON_NAME} ] ;
    then
      REQUIRED_ADDONS="${REQUIRED_ADDONS} ${addon}"
    fi
  done < $addons_make
done

REQUIRED_ADDONS=$(echo ${REQUIRED_ADDONS} | tr ' ' '\n' | sort -u | tr '\n' ' ')

download_required_addons $REQUIRED_ADDONS
