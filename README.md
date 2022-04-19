# minishell

## EBNF
```ebnf
parser    = stmt EOF
stmt      = and_or (";" and_or)* ";"?
and_or    = pipe ("&&" pipe | "||" pipe)
pipe      = cmd ("|" cmd)*
cmd       = (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word 
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...
```
