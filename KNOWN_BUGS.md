# Known bugs
This is a list of the known bugs in matlab2r. Feel free to add on to this list.

* Empty function declarations cause the visitors to hang. This is a simple grammar fix, I just have to get around to doing it.
* Single-quote escapes don't parse correctly, this needs some lexer magic