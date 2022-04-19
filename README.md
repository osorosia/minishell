# minishell

## EBNF
```ebnf
parser    = stmt* pipe? EOF
stmt      = pipe ";"
pipe      = cmd ("|" cmd)*
cmd       = (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word 
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...
```
