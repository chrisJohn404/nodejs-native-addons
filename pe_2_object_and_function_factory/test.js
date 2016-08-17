

// test.js
const addon = require('./build/Release/addon');

var myAddon = addon();

// Execute a function
console.log('Executed myFunction:', myAddon.myFunction());


// Execute a function w/ a callback
console.log('Executing myFunctionCB:');
myAddon.myFunctionCB((res) => {
	console.log('  - myFunctionCB result', res);
});

// Execute the "add" function
console.log('Executing add:');
myAddon.add(3, 4, (res) => {
	console.log('  - The result should be 7:', res);
});