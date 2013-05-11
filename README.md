Lisp Style REPL
===============

Simple lisp style command line interpreter (REPL) especially for embedded system.
REPL: Read Evaluate Print & Loop

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "NOT RECOMMENDED",  "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](http://tools.ietf.org/html/rfc2119).

All extern function or variable SHALL in the namespace 'lsr\_', 'Lsr\_' OR 'LSR\_' which is short for Lisp Style Repl.

Version number SHALL be compatible with [Semantic Versioning](http://semver.org/).

## How to use
```scheme
;; A blank is REQUIRED after '(' & before ')'
;; Command MUST in one line
;; Nested parentheses SHALL NOT be used
( command arg0 arg1 ... )
```

### C APIs
The C APIs SHALL NOT reentrant. Which means it is not thread-safe.


## License 
Copyright 2013 [jks Liu](http://jks-liu.github.io/). Some right reserved.
License: BSD.

