const workerpool = require('workerpool');
const native = require('../native');

workerpool.worker({
  normalMethod: () => {
    console.log('normalMethod', native.normalMethod());
  },
  crashMethod: () => {
    console.log('crashMethod', native.crashMethod());
  }
});