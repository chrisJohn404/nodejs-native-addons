

// test.js
const addon = require('./build/Release/addon');

console.log('Executing the addon, this does not work :(');
// addon((msg) => {
//   console.log(msg); // 'hello world'
// });

console.log('But this does!');
addon.add(3, 4, (result) => {
	console.log('The result should be 7:', result);
});