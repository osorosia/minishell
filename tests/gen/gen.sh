#!/bin/bash

function gen() {
  python3 ${1}.py > ../ok/gen_${1}.txt
}

rm -rf ../ok/gen_*

gen "and_or"
gen "kakko"
