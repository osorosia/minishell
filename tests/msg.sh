#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

set -m
export BASH_SILENCE_DEPRECATION_WARNING=1

function test() {
    file="${1}.txt"

    ../minishell heredoc < ./ok/${file} &> ./actual/${file}
    bash -fi < ./ok/${file} &> ./expected/${file}.tmp

    cat ./expected/${file}.tmp \
        | sed $'s/[\x1B][\x5B][\x3F][\x31][\x30][\x33][\x34][\x68]//g' \
        | sed 's/ \r//g' \
        | sed 's/bash-3.2\$/%/g' \
        | sed 's/^bash:/minishell:/g' \
        | grep -v 'Inappropriate ioctl for devic' \
        > ./expected/${file}

    rm -rf ./expected/*.tmp*

    diff -U 0 ./actual/${file} ./expected/${file} > ./diff/${file}
    result=$?
    if [ "$result" = "0" ]; then
        echo -e "${GREEN}OK:${NC} ${1}"
    else
        echo -e "${RED}KO!!!!!!!!!!:${NC} ${1}"
        sdiff ./actual/${file} ./expected/${file}
    fi
}

echo msg

rm -rf diff
rm -rf actual
rm -rf expected
mkdir diff
mkdir actual
mkdir expected
