Lisp Style REPL
===============

Simple lisp style command line interpreter (REPL) especially for embedded system.

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "NOT RECOMMENDED",  "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](http://tools.ietf.org/html/rfc2119).

Version number SHALL be compatible with [Semantic Versioning](http://semver.org/).

## Acronym used in documents and source files
- **REPL**: Read Evaluate Print & Loop
- **CLI**: Command Line Interface

## How to use
```scheme
;; Command MUST in one line
;; Nested parentheses SHALL NOT be used
(command arg0 arg1 ...)
```

### C APIs
**standard**: C99

All extern function or variable SHALL in the namespace 'lsr\_', 'Lsr\_' OR 'LSR\_' which is short for Lisp Style Repl.

The C APIs SHALL NOT reentrant. Which means it is not thread-safe.

#### Built-in command
```scheme
;; All built-in command SHALL return 0 if success or 1 if fail.
;; Except ($?) will return the same value as the last command
;; 
;; Show last command return value
($?)
;; Show all commands and a brief introduction.
(help)
;; Show manual of a specific command.
(man command)
;; + - * / (TODO)
(+ num0 num1 ...)
(- num0 num1 ...) ; num0 - num1 - num2 - ...
(* num0 num1 ...)
(/ num0 num1 ...) ; num0 / num1 / num2 / ...
```

#### Initialize and add your own command
You will get a example in [test/](https://github.com/jks-liu/lisp-style-repl/tree/master/test) directory.

A command named "copyright" MUST be implemented.

A command including built-in command which return non-zero SHALL be considered a error, So the ($?) will return a error even it executed successfully.

Command return value MUST in range \[0, 256\), this range is [POSIX-compatible](http://en.wikipedia.org/wiki/Exit_status).

#### Use C++ ?
There are something wrong c++
 - C++ did not define `restrict' 
 - C++ had [different semantics with compound literals](http://gcc.gnu.org/onlinedocs/gcc/Compound-Literals.html)

 Please refer [test-cpp/](https://github.com/jks-liu/lisp-style-repl/tree/master/test-cpp) for details to fix errors. 

### Authentication 
TODO

## License 
Copyright 2013 [jks Liu](http://jks-liu.github.io/). Some right reserved.

**License**: BSD.

