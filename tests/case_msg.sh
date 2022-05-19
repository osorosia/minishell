# lexer

# parser
test 'pipe'
test 'parser_error'

# expander
test 'quote'
test 'wildcard'

# exec
test 'exec'
test 'exec_error'

# builtin
test 'builtin_echo'
test 'builtin_cd'
test 'builtin_pwd'
test 'builtin_export'
test 'builtin_unset'
test 'builtin_env'
test 'builtin_exit'

# env
test 'env_pwd_oldpwd'

# redirect
test 'redirect_heredoc'
test 'redirect_in'
# test 'redirect_out'
test 'redirect_permission'
test 'redirect_directory'

# status
test 'status'
test 'status1'
test 'status_()'

#path
test 'path'
