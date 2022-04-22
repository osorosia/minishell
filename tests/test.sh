#!/bin/bash

function test() {
  input=$1

  echo $input | bash 1> ./expected/output

  echo $input | ../minishell 1> ./actual/tmp
  cat ./actual/tmp | grep -v "minishell" > ./actual/output

  diff ./expected/output ./actual/output &> /dev/null
  result=$?
  if [ $result -eq 0 ]; then
    echo "OK: $input"
  else
    echo "KO: $input"#want color
    diff ./expected/output ./actual/output > ./diff/diff
  fi
}

# init
rm -rf expected
rm -rf actual
rm -rf diff
mkdir expected
mkdir actual
mkdir diff

# basic test case
echo ---------------------------------------
test "ls"
test "ls -l"
test "/bin/ls -l"
test "ls | cat"
test "ls -l | cat"
test "/bin/ls -l | cat"
test "/bin/ls -l | cat | echo hello"
echo ---------------------------------------