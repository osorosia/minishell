#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function test() {
  input=$1

  echo $input | bash 1> ./expected/output

  echo $input | ../minishell 1> ./actual/tmp
  cat ./actual/tmp | grep -v "minishell" > ./actual/output

  diff ./expected/output ./actual/output &> /dev/null
  result=$?
  if [ $result -eq 0 ]; then
    echo -e ${GREEN}"OK:${input}"${NC}
  else
    echo -e ${RED}"KO:${input}" ${NC}
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

#random testcase
test 'ls'
test '/bin/ls'
test '/bin/ls -l'
test 'env'
test 'cmd'
test 'bash'
test 'bash -x'
test 'echo $PWD'
test 'echo "$PWD"'
test 'echo -n hello'
test 'echo -n "HOGE"'
test 'echo -n ls"'
test 'echo -nn hello'
test 'exit 42'
test 'exit -42'
test 'echo a a a "b"'
test 'echo \"a      \"   \"     b\"'
test 'echo hello|cat -e'
test 'echo hello|cat -e|cat -e'
test 'echo hello | cat -e | cat -e'
test 'ls | ls'
test 'ls| ls'
test 'ls |ls'
test 'ls|ls'
test 'export N=''-n'''
test 'echo $N hello'
test 'echo $N $N hello'
test 'echo $N$N hello'
test 'echo $$N hello'
test 'echo ''$N'' hello'
test 'echo $N hello $N world'
test 'export N=-n'
test 'echo $N hell $N world'
test 'echo *'
test 'echo **'
test 'echo * * *'
test 'echo *******'
test 'echo -n ***'
test 'echo -n * -n *'
test 'echo "*"'
test 'echo '*''