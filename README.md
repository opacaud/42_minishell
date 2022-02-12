# 42_minishell

## Project 06: Replicating Bash 4.4 --posix

Run ```make``` and then ```./minishell```
</br>
**Update**: I have been told that compilation can fail on other OS than the one the program has been developed on (Linux - Xubuntu), possibly because of the global variable that is the return value or the rl_replace_line function. They can be removed throughout the program but functionalities will obviously disapear.
</br>
</br>
Please note that an history is available each time you launch ./minishell.

### Builtins I replicated:
- **echo** (including the -n option)
- **cd** (including without any argument, with the - and ~ options or with an absolute or relative path)
- **pwd** (without any options)
- **export** (without any options)
- **unset** (without any options)
- **env**  (without any options)
- **exit** (including followed by a number that will be the exit code)

All the **other commands** are passed as an argument to an **execve** function.

### Signals I replicated:
- Ctrl + C
- Ctrl + D
- Ctrl + \

### Redirections I replicated:
- \>
- <
- \>>
- << (heredoc does not update history)
- |

### Please note that:
- **environment variables** are translated, as well as $?, if they are not between simple quotes.
- **errors and their return values** (that can be seen with echo $? right after the command that went wrong) are handled as much as possible like Bash does.
- the environment variable **SHLVL** is updated if you launch ./minishell inside a ./minishell and so on and so forth.
- **readline** was an allowed function but it is known to create memory leaks that we were thankfully not asked to fix.
- **Bash 4.4 --posix** was my reference. Some results may differ on other versions.
