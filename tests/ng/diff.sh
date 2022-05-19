#!/bin/bash

function test() {
  ../../minishell < $@ > ./expected 2>/dev/null
  bash < $@ > ./actual
  diff -u expected actual > ./diff_file
  rm -rf expected actual
};

test 'echo.test'

