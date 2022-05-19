#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

set -m

function test() {
    file="${1}.txt"

    ../minishell < ./msg/${file} &> ./actual/${file}
    bash -i < ./msg/${file} &> ./expected/${file}.tmp

    cat ./expected/${file}.tmp | grep 'The default interactive shell is now zsh.' > /dev/null
    if [ "$?" = 0 ]; then
        cat ./expected/${file}.tmp | awk 'NR>4' > ./expected/${file}.tmp2
    else
        cat ./expected/${file}.tmp > ./expected/${file}.tmp2
    fi

    cat ./expected/${file}.tmp2 \
        | sed 's/^.*bash-3.2\$/%/g' \
        | sed 's/^bash:/minishell:/g' \
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
