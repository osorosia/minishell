#!/bin/bash

RESET="\033[0m"
RED="\033[31m"
GREEN="\033[32m"

make -C ../ >dev/null
cp ../minishell .
chmod 755 minishell
mkdir ./diff
touch ./diff/diff

function test() {
  ACTUAL_OUTPUT=$(echo $@ | ./minishell 2>&-)
  ACTUAL_STATUS=$?
  EXPECTED_OUTPUT=$(echo $@ | bash 2>&-)
  EXPECTED_STATUS=$?
  if [ "${ACTUAL_OUTPUT}" == "${EXPECTED_OUTPUT}" ] && [ "${ACTUAL_STATUS}" == "${EXPECTED_STATUS}" ]; then
    echo -en "${GREEN}OK:${RESET}"
    else
      echo -en "${RED}KO:${RESET}"
	fi
	echo  "$@"
	if [ "${ACTUAL_OUTPUT}" != "${EXPECTED_OUTPUT}" ]; then
		printf ${RED}"actual output: \n%.20s\n${ACTUAL_OUTPUT}\n%.20s${RESET}\n" \
		"-----------------------------------------" "-----------------------------------------" \
		> ./diff/diff
		printf ${GREEN}"expected output: \n%.20s\n${EXPECTED_OUTPUT}\n%.20s${RESET}\n" \
		"-----------------------------------------" "-----------------------------------------" \
		>> ./diff/diff
	fi
	if [ "$ACTUAL_STATUS" != "$EXPECTED_STATUS" ]; then
		printf ${RED}"[actual status: ${RED}${ACTUAL_STATUS}${RESET} | "
		printf ${GREEN}"expected status : ${GREEN}${EXPECTED_STATUS}${RESET}]\n"
	fi
}

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

#echo
test 'export N='-n''
test 'echo $N hello'
test 'echo $N $N hello'
test 'echo $N$N hello'
test 'echo $$N hello'
test 'echo '$N' hello'
test 'echo $N hello $N world'

test 'export N=''-nn'''
test 'echo $N hell $N world'

#asterisk
test 'echo *'
test 'echo **'
test 'echo * * *'
test 'echo *******'
test 'echo -n ***'
test 'echo -n * -n *'
test 'echo "*"'
test 'echo '*''
