Getting started!
================================================

-----------
Installing
-----------

To install Clever is easy, just run the make. In this stage, you can
help the Clever Team also by running make run-tests and reporting to us
if you get some failures!

-----------------
Native data types
-----------------

::

  Int i = 10;
  Double j = 1.2;
  String str = "foo";
  Bool is = true;
  Array<Int> arr;
  Map<Int, String> map;

Native data types in Clever are first-class object. This means that you
can do::

  "hello world!".toUpper()

----------------
const qualifier
----------------

You can mark a variable to not be changed along your code. Just use the
const qualifier. ::

  const Int i = 10;

-------------
Control flow
-------------

##############
if statements
##############

::

  if (bar()) {
  }

###############
for statements
###############

::

  for (Int i = 0; i < 10; ++i) {
  }

#################
Function syntax
#################

::

  Int foo(Int bar) {
    return bar;
  }

#################
Importing module
#################

::

  import std.io;
  import std.regex as re;
