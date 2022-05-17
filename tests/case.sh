export CAT='cat -e'
export LS='ls -a'

rm -rf tmp*
mkdir tmpdir
#folder用意等のテストの方がみやすいものに関してはこっちに足す

test 'temptest'
exit
test 'exec'

# parser
test 'pipe'
test 'parser_error'

# expander
test 'quote'

# builtin
test 'builtin_echo'
test 'builtin_cd'
test 'builtin_pwd'
test 'builtin_export'
test 'builtin_unset'
test 'builtin_env'
test 'builtin_exit'

# redirect
test 'redirect_heredoc'
##redirectあと3つ分類
#redirect_out
#redirect_in
#redirect_append


# status
test 'status'
test 'status1'
test 'status_()'


