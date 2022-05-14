#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function test() {
  file="${1}.txt"

  valgrind --log-file="./log/${file}" --leak-check=full ../minishell < ./ok/${file} > /dev/null
  result=$?
  
  cat ./log/${file} | grep ERROR | grep -v " 0 errors " > /dev/null
  result=$?
  if [ "$result" = "0" ]; then
    echo -e "${RED}KO!!!!!!!!!!:${NC} ${1}"
  else
    echo -e "${GREEN}OK:${NC} ${1}"
  fi
}

echo leak

rm -rf log
mkdir log
