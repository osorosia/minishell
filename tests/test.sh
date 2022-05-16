#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function test() {
  file="${1}.txt"

  ../minishell < ./ok/${file} > ./actual/${file}
  bash -i < ./ok/${file} > ./expected/${file}

  diff -U 0 ./actual/${file} ./expected/${file} > ./diff/${file}
  # diff ./actual/${file} ./expected/${file}

  result=$?
  if [ "$result" = "0" ]; then
    echo -e "${GREEN}OK:${NC} ${1}"
  else
    echo -e "${RED}KO!!!!!!!!!!:${NC} ${1}"
    # cat ./diff/${file} | grep -v '^+++' | grep -v '^---'
    sdiff ./actual/${file} ./expected/${file}
  fi
}

echo test

rm -rf diff
rm -rf actual
rm -rf expected
mkdir diff
mkdir actual
mkdir expected
