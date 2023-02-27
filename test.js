/**
 * init array
 */
console.log("generating array...");

const ARRL_LENGTH = 500000;
const arr = new Array(ARRL_LENGTH)
  .fill(null)
  .map((_) => Math.round(Math.random() * ARRL_LENGTH));
const arrCopy = arr.concat([]);

console.log("array generated");

/**
 * JS sort
 */
function bubbleSort(array) {
  const len = array.length;
  const ret = array.concat([]);
  for (let i = len - 1; i > 0; --i) {
    for (let j = 0; j < i; ++j) {
      if (ret[j] > ret[j + 1]) {
        const tmp = ret[j];
        ret[j] = ret[j + 1];
        ret[j + 1] = tmp;
      }
    }
  }
  return ret;
}

console.log("JS sort...");

const jsStartTime = Date.now();
const jsRes = bubbleSort(arr);
const jsEndTime = Date.now();

console.log("JS sort result:", jsRes.slice(0, 10));
console.log("time use:", jsEndTime - jsStartTime);

/**
 * C++ sort
 */
var addon = require("bindings")("sort.node");

console.log("C++ sort...");

const cppStartTime = Date.now();
const cppRes = addon.sort(arrCopy);
const cppEndTime = Date.now();

console.log("C++ sort result:", cppRes.slice(0, 10));
console.log("time use:", cppEndTime - cppStartTime);
