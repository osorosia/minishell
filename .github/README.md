# minishell
minishellは42tokyoの課題です。2人1組で取り組むペア課題です。

## EBNF
```ebnf
parser    = stmt EOF
stmt      = pipe_cmd ((";" | "||" | "&&") pipe_cmd)* ";"?
pipe_cmd  = bracket ("|" bracket)*
bracket   = "(" stmt ")"
          | cmd
cmd       = (word | redir_in | redir_out)*
redir_in  = ("<" | "<<") word 
redir_out = (">" | ">>") word
word      = (e.g.) "ls", "-l", "file", ...
```
