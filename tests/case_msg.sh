export CAT='cat -e'
export LS='ls -a'

rm -rf tmp*
mkdir tmpdir

# tmp
test 'test'

# parser
test 'parser_error'

# builtin
test 'builtin_echo'
test 'builtin_cd'
# test 'builtin_pwd'
test 'builtin_export'
# test 'builtin_unset'
test 'builtin_env'
# test 'builtin_exit'
