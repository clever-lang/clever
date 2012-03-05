Reflection
================================================

-----------------------
ReflectionPackage class
-----------------------

**Methods**

* String **getName()**:
   Returns a String containing the package name. ::

     ReflectionPackage pkg("std");
     println(pkg.getName("std)); // displays 'std'

* Array<String> **getModules()**:
   Returns an Array<String> containing the packages' module. ::

     ReflectionPackage pkg("std");
     println(pkg.getModules()); // displays '[math, io, etc]'

------------------------
ReflectionFunction class
------------------------

**Methods**

* Bool **isInternal()**:
   Returns a Bool indicating if the function is internal.

* Bool **isUserDefined()**:
   Returns a Bool indicating if the function is user-defined.

* String **getReturnType()**:
   Returns a String representing the name of return type. ::

     ReflectionFunction func("getcwd");
     println(pkg.getReturnType(); // displays 'String'

* Int **getNumRequiredArgs()**:
   Returns an Int representing the number of required arguments. ::

     ReflectionFunction func("max");
     println(pkg.getNumRequiredArgs(); // displays '2'

* Array<String> **getArgs()**:
   Returns an Array<String> containing the type name of arguments.
