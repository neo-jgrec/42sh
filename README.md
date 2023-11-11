# 42sh

The project consist to write a Unix SHELL.

It have two sections to achieve:

- a mandatory section, which MUST be completed: display a prompt, parse and execute some commands (see below),
- an optional section, which will only be evaluated if the mandatory section is fully functionnal.

Authorized functions: all functions included in the libC nor the ncurses library.

The `42sh` is a shell that mimic the tcsh shell in it's behavior. For example, it followed the sames errors messages and parsing rules.
(We're using tcsh version tcsh 6.24.07 (Astron) 2022-12-21)

## Requirements of the project

### Mandatory section

This section must be COMPLETELY FUNCTIONAL, otherwise the project will be considered non functional and will receive a 0 grade.

- [x] spaces and tabs,
- [x] $PATH and environment,
- [x] errors and return value,
- [x] redirections (‘<’, ‘>’, ‘<<’ and ‘>>’),
- [x] pipes (‘|’),
- [x] builtins: cd, echo, exit, setenv, unsetenv,
- [x] separators: ‘;’, ‘&&’, ‘||’.

For instance, you should be able to execute the following command:

```bash
∼/B-PSU-210> ./42sh
42sh> cd ; </etc/hosts od -c | grep xx | wc >> /tmp/z -l ; cd - && echo “OK”
```

### Optional section

The most of your points you can get for the project are from this section.
This project is free-rein and can do what you want. However, the entire project’s coherence will be taken into
consideration.
Once more, stability will be much more important that quantity. An option that will cause a problem for the rest of the program (especially for the mandatory section!) will make you lose a lot of points.

Here is a list of desired extras:

- [x] inhibitors (‘\’),
- [x] globbings (‘*’, ‘?’, ‘[’, ’]’),
- [ ] job control (‘&’, fg),
- [ ] backticks ("\`"),
- [x] parentheses (‘(’ and ‘)’),
- [x] variables (local and env),
- [ ] special variables (term, precmd, cwdcmd, cwd, ignoreof for instance),
- [x] history (‘!’),
- [x] aliases,
- [x] line edition (multiline, dynamic rebinding, auto-completion dynamic),
- [ ] scripting (a bit harsh though).

These extras are not bonuses! Bonuses will be evaluated only after every item on this list have been correctly implemented.

## Needed packages to compile the project

* gcc
* make

## How to compile the project

* Clone the repository
* Run `make` in the root of the repository
* Run `./42sh`
* Enjoy

## How to use the shell

* Run `./42sh`
* Type a command
* Poof magic

## Dependencies

[![RepoCard](https://github-readme-stats.vercel.app/api/pin/?username=neo-jgrec&repo=mars-lib&theme=dark&border_radius=8&hide_border=true)](https://github.com/neo-jgrec/mars-lib)
