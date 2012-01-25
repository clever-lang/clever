Make you code more clever!
==========================

Clever is a general purpose programming language written in C++. It aims to 
have a small footprint and supply an useful set of features, many seen in 
other languages.

Want to know more?
==================

The main source of knowledge is our website http://clever-lang.github.com/ 
and our mailing list http://groups.google.com/group/clever-lang. Oh and we 
love IRC, you will surely find someone online on #clever @ irc.freenode.net.


Feeling like getting your hands dirty?
======================================

Coding Standards
----------------

We mostly code based on the Google C++ Style Guide[1], which seems sane 
enough. The LLVM[2] one is also quite nice. 

Use the `.cc` extension for C++ source files and `.h` for C++ headers, 
hopefully your compiler is smart enough to identify C++ source inside a `.h` 
(don't worry, GCC and Clang are!). Oh, I almost forgot, please use *tabs 
instead of spaces*, UTF-8 file encoding and UNIX file endings (Line feed 
a.k.a. `\n`).

If you don't know how to contribute, but know how to code, it'd be nice if 
you could implement one of the ideas from our whishlist:
https://github.com/clever-lang/clever/wiki/TODO-List-&-Ideas

Git help:
- http://help.github.com/fork-a-repo/
- http://help.github.com/send-pull-requests/

[1] - http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
[2] - http://llvm.org/docs/CodingStandards.html
