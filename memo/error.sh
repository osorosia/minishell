#!/bin/bash

function check() {
  cmd="$1"
  echo $cmd > tmp 
  bash < tmp 2>/dev/null
  # bash < tmp
  
  sts=$?
  echo "$cmd => $sts"
}

check "aaaa"
check ";"
