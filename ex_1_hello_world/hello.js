
// hello.js

// var bAddon = require('bindings')('./addon.node');
const addon = require('./build/Release/addon');

console.log('hello', addon.hello()); // 'world'
// console.log(bAddon.hello()); // 'world'