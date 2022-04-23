#!/bin/bash

RESET="\033[0m"
RED="\033[31m"
GREEN="\033[32m"
CYAN="\033[36m"

make -C ../ >dev/null
cp ../minishell .
chmod 755 minishell
mkdir ./diff
touch ./diff/diff

function tester() {
  INPUT=$(echo $@ "; exit" | ./minishell 2>&-)
  ES_ACTUAL=$?  OUTPUT=$(echo $@ "; exit" | bash 2>&-)
  ES_EXPECTED=$?
  if [ "$INPUT" == "$OUTPUT" ] && [ "$ES_ACTUAL" == "$ES_EXPECTED" ]; then
    echo -en "${GREEN}OK:${RESET}"
    else
      echo -en "${RED}KO:${RESET}"
	fi
	echo  "$@ "
	if [ "$INPUT" != "$OUTPUT" ]; then
		printf $RED"actual output: \n%.20s\n$INPUT\n%.20s$RESET\n" \
		"-----------------------------------------" "-----------------------------------------" \
		> ./diff/diff
		printf $GREEN"expected output: \n%.20s\n$OUTPUT\n%.20s$RESET\n" \
		"-----------------------------------------" "-----------------------------------------" \
		>> ./diff/diff
	fi
	if [ "$ES_ACTUAL" != "$ES_EXPECTED" ]; then
	  echo
		printf $RED"actual status: $RED$ES_ACTUAL$RESET\n"
		printf $GREEN"expected status : $GREEN$ES_EXPECTED$RESET\n"

	fi
}

tester 'ls'
tester '/bin/ls'
tester 'env'
#grepを使って違いを見つける-vオプションを使う
#env | grep -v ~ | sort #->env&export系はsortする
#tester 'exit -2'
#tester '/bin/ls -l'
#tester 'echo hello|cat -e|cat -e|cat -e'
tester "echo a\"\"b"
tester "echo a \"  \" b"
tester "echo [a       \"     \"    b]"
tester "echo -n hello"
tester 'echo $PWD'