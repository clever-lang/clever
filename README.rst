Make you code more clever!
==========================

Clever is a general purpose programming language written in C++. It aims to
have a small footprint and supply an useful set of features, many seen in
other languages.

Want to know more?
==================

The main source of knowledge is our website_ and our `mailing list`_. Oh and
we love IRC, you will surely find someone online on #clever @
irc.freenode.net.


Feeling like getting your hands dirty?
======================================

If you don't know how to contribute, but know how to code, it'd be nice if
you could implement one of the ideas from our wishlist_. If you don't know
how to code, but think you know enough about Clever, you can help us
writting or fixing the documentation_.


Coding Standards
----------------

We mostly code based on the `Google C++ Style Guide`_, which seems sane
enough. `The LLVM`_ one is also quite nice.

Use the `.cc` extension for C++ source files and `.h` for C++ headers,
hopefully your compiler is smart enough to identify C++ source inside a `.h`
(don't worry, GCC and Clang are!). Oh, I almost forgot, please use *tabs
instead of spaces*, UTF-8 file encoding and UNIX file endings (Line feed
a.k.a. `\n`).


Useful links
~~~~~~~~~~~~

Git help:

        - http://help.github.com/fork-a-repo/
        - http://help.github.com/send-pull-requests/

reStructuredText help:

        - http://docutils.sourceforge.net/rst.html
        - http://www.siafoo.net/help/reST

.. _mailing list: http://groups.google.com/group/clever-lang
.. _website: http://clever-lang.org/
.. _wishlist: https://github.com/clever-lang/clever/wiki/TODO-List-&-Ideas
.. _documentation: https://github.com/clever-lang/clever-doc

.. _Google C++ Style Guide: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
.. _The LLVM: http://llvm.org/docs/CodingStandards.html
