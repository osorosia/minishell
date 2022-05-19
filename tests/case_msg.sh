export CAT='cat -e'
export LS='ls -a'

rm -rf tmp*
mkdir tmpdir

test 'exec'

# parser
# test 'pipe'
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
# test 'redirect_heredoc'

# status
# test 'status'
# test 'status1'
# test 'status_()'
