# minishell

## EBNF
```ebnf
parser    = stmt ";"? EOF
stmt      = pipe_cmd ((";" | "||" | "&&") pipe_cmd)*
pipe_cmd  = cmd ("|" cmd)*
cmd       = (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word 
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...
```
