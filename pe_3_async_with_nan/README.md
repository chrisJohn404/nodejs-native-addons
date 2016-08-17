#Simple Arguments (Function arguments) native-module
This example native-module exposes a function called "add" that has two arguments.
These arguments are added together and the result is returned.  As per the node.js documentation, "The following example illustrates how to read function arguments passed from JavaScript and how to return a result".

The running the "test.js" file aka "node test.js", prints the text:
"This should be eight: 8".

#Reference:
Node.js (Function arguments)[https://nodejs.org/api/addons.html#addons_function_arguments] native-module example on the Node.js (C/C++ Addons docs)[https://nodejs.org/api/addons.html] page.

#To build and run:
1. Execute "node-gyp configure" to (on Windows) create a vcxproj file or (on Unix platforms) a Makefile in the build/ directory.
code:
node-gyp configure

2. Execute "node-gyp build" to build the project.  For this project/configuration, this will create a addon.node file in the ./build/Release directory.  
code:
node-gyp build

3. Execute the "test.js" file:
code:
node test.js