### getline -

getline(input, &len, stdin)
- len - getline allocate a buffer in head to hold the input string from source(here stdin).
- the size of buffer is stored in the len parameter.
- remove the last newline char.

### strtokn - Tokenisatin

- when a string is passed, strtok maintain a pointer to the next token of the string
- on subsquent call strtok re-use the same pointer instead of re-inialzation unless u pass a string explicitly.
- this is not thread safe

### waitpid

- allow parent process to wait till the child process execute.
