#kawamatsu issues
test 'kawa_matsu'

# lexer

# parser
test 'pipe'
test 'parser'
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

# builtin error
test 'builtin_export_error'

# env
test 'env_pwd_oldpwd'
test 'env_path'

# redirect
test 'redirect_heredoc'
test 'redirect_in'
test 'redirect_out'
test 'redirect_append'
test 'redirect_permission'
test 'redirect_permission2'
test 'redirect_directory'
test 'redirect_in_mix'
test 'redirect_out_mix'
test 'redirect_all'

# status
test 'status'
test 'status1'
test 'status_()'

#path
test 'path'

