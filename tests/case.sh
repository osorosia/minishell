export CAT='cat -e'
export LS='ls -a'

rm -rf tmpdir
mkdir tmpdir

test 'exec'
test 'echo'
test 'echo_opt'

test 'quote'

# builtin
# test 'builtin_echo'
test 'builtin_cd'
test 'builtin_pwd'
test 'builtin_export'
test 'builtin_unset'
test 'builtin_env'
test 'builtin_exit'

# status
test 'status'
test 'status1'
test 'status_()'
