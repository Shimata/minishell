# minishell
A basic shell by [jalvaro](https://github.com/VDmdm) and me.

### Built-in functions implemented:
- echo
- cd
- pwd
- env
- export
- unset
- exit

For any other binaries, the $PATH variable is searched.
Assuming there was a match, the binary will be executed.

### Parser features:
- Plain text parsing
- Single and double quote recognition
- Multiline commands
- environment variable substitution

### bash syntax implemented:
- Truncation >
- Appending >>
- File reading <
- Pipes |
- Semicolons ;

To run our minishell paste this into your command line:<br>

`git clone https://github.com/Shimata/minishell.git && cd minishell && make && ./minishell`
