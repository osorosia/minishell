#!/bin/bash

function test() {
  ../../minishell < $@ > expected 2>/dev/null
  bash < $@ > actual
  diff expected actual >> ./diff_file
  rm -rf expected actual
  echo ---------------------------------
};

test 'cd.test'
test 'echo.test'
test 'env.test'
test 'exit.test'
test 'export.test'
test 'heredoc.test'
test 'parser.test'
test 'path.test'
test 'permission.test'
test 'pipe.test'
test 'postscript.test'
test 'pwd.test'
test 'redirect.test'
