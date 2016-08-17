

// test.js
const addon = require('./build/Release/addon');

console.log('Executing the addon');
addon((msg) => {
  console.log(msg); // 'hello world'
});
