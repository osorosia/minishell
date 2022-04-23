#!/bin/bash

RED='\033[0;31m'
BLUE='\033[32m'
NC='\033[0m'

function test() {
  input=$1

  echo $input | bash 1> ./expected/output

  echo $input | ../minishell 1> ./actual/tmp
  cat ./actual/tmp | grep -v "minishell" > ./actual/output

  diff ./expected/output ./actual/output &> /dev/null
  result=$?
  if [ $result -eq 0 ]; then
    echo -e ${BLUE}"OK:${input}"${NC}
  else
    echo -e ${RED}"KO!!:${input}" ${NC}
    diff ./expected/output ./actual/output > ./diff/diff
  fi
}

# init
rm -rf expected
rm -rf actual
rm -rf diff
mkdir expected
mkdir actual
mkdir diff````````````````````````

# basic test case
echo ----------[basic]-----------------------------
test "ls"
test "ls -l"
test "ls -la"
test "ls -l -a"
test "ls -llllllllllllllllllllllllllllllllllllllllllllllllllllllllll"
test "/bin/ls -l"
test "ls | cat"
test "ls \"|\" cat"
test "ls -l | cat"
test "/bin/ls -l | cat"
test "/bin/ls -l | cat | echo hello"
test "echo a b"
test "echo hello > ./tmp/redirect_test"
test "echo "'$HOME'""
test 'echo '$PWD''
test 'echo "$PWD"'

echo -----------[corner]----------------------------
test "echo a\"\"b"
test "echo a \"  \" b"
test "echo a       \"     \"    b | wc -c"
test "echo -n hello"
test "xxx | ls"
test "xxx | ls | xx"
test "xxx | ls | xx | cat"
test "xxx | ls | xx | cat"