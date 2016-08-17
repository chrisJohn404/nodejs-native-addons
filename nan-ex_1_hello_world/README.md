#Hello World example using Nan:
https://github.com/nodejs/nan

Basic hello world information:
1. Add NAN as a dependency in the package.json of your Node addon:
code:
npm install --save nan

2. Pull in the path to NAN in your binding.gyp file so that you can use #include <nan.h> in your .cpp files:
code:
"include_dirs": [
"<!(node -e \"require('nan')\")"
]

This tag should go inside the "targets" array of objects...