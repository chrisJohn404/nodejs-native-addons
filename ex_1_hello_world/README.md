#Hello World native-module

#Reference:
Node.js (C/C++ Addons docs)[https://nodejs.org/api/addons.html] page.

#To build:
1. Execute "node-gyp configure" to (on Windows) create a vcxproj file or (on Unix platforms) a Makefile in the build/ directory.
code:
node-gyp configure

2. Execute "node-gyp build" to build the project.  For this project/configuration, this will create a addon.node file in the ./build/Release directory.  
code:
node-gyp build

3. Import/Execute with node.  Call "require('./build/Release/addon')", look at the hello.js file for more details.
code:
var addon = require('./build/Release/addon');

// The addon function "hello" returns the string "world".
console.log('hello', addon.hello());