#!/bin/bash

function check() {
  cmd="$1"
  echo "\"$cmd\""

  echo $cmd > tmp 
  bash < tmp
  echo
}

check "echo a1 || echo a2 || echo a3"
check "echo a1 && echo a2 && echo a3"

check "echo a1 || echo a2 && echo a3"
check "echo a1 && echo a2 || echo a3"

check "echo a1 | cat || echo a2 && echo a3"
check "echo a1 | cat && echo a2 || echo a3"

check "a1 || a2 && a3"
check "a1 && a2 || a3"
