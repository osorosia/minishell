#!/bin/bash

function test() {
  file="${1}.txt"

  valgrind --log-file="./log/${file}" --leak-check=full ../minishell < ./ok/${file} > /dev/null
  result=$?
  
  cat ./log/${file} | grep ERROR | grep -v " 0 errors " > /dev/null
  result=$?
  if [ "$result" = "0" ]; then
    echo "KO!!!!!!!!!!: ${1}"
  else
    echo "OK: ${1}"
  fi
}

echo leak

rm -rf log
mkdir log
