# Intro

- Running a cmd in a terminal, is actually running a new process.

- Existing shell process is forked, as a result a new child process is spin up and
  immediately replaced with the new program correpond to the input command (for example ls, mkdir etc)
  using execvp variant of exec system calls.

- Parent process can keep on running concurrently along with forked one,
- as well as wait for change in state change of duplicate process
- When finally child process stopped, we move on finally to run other commands.

execvp never return unless there is an error
execvp expect the program name and list of args, execvp figure out program location from the path env.



## About code
- first if block - correpond to child process, quickly replace with new porgram.
- if the execvp result in returning -1,  log it let the user know about the error and then finally exited out of the child process.


second if fork was un-successfull, caught the error, log the eror, there is not handling with this error beyond letting the user know and let him decide further action (quit the shell or keep enjoying).

###  third block

- As waiting for the child program termination, or change in state of child program
- either itself terminate by calling exit
- signal from kernal killed it.
