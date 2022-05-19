#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

set -m

function test() {
    file="${1}.txt"

    ../minishell < ./ok/${file} &> ./actual/${file}
    bash -i < ./ok/${file} &> ./expected/${file}.tmp

    cat ./expected/${file}.tmp | grep 'The default interactive shell is now zsh.' > /dev/null
    if [ "$?" = 0 ]; then
        cat ./expected/${file}.tmp \
            | awk 'NR>4' \
            | sed $'s/[\x1B][\x5B][\x3F][\x31][\x30][\x33][\x34][\x68]//g' \
            > ./expected/${file}.tmp2
    else
        cat ./expected/${file}.tmp > ./expected/${file}.tmp2
    fi

    cat ./expected/${file}.tmp2 \
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
