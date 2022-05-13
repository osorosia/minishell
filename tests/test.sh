#!/bin/bash

function test() {
  file="${1}.txt"

  ../minishell < ./ok/${file} > ./actual/${file}
  bash < ./ok/${file} > ./expected/${file}

  diff -U 0 ./actual/${file} ./expected/${file} > ./diff/${file}
  # diff ./actual/${file} ./expected/${file}

  result=$?
  if [ "$result" = "0" ]; then
    echo "OK: ${1}"
  else
    echo "KO!!!!!!!!!!: ${1}"
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
