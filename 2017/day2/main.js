const fs = require("fs");
const readline = require("readline");

let MaxArray = new Array();
let MinArray = new Array();
let difArray = new Array();

async function part1() {
  const fileStream = fs.createReadStream("input.txt");

  const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity,
  });

  for await (const line of rl) {
    let myArrays = line.trim().split(/\s+/);
    for (let i = 0; i < myArrays.length; i++) {
      myArrays[i] = Number(myArrays[i]);
    }

    if (myArrays.length > 0) {
      const maxValue = Math.max(...myArrays);
      const minValue = Math.min(...myArrays);
      console.log(`MAX: ${maxValue}`);
      console.log(`MIN: ${minValue}`);
      MaxArray.push(maxValue);
      MinArray.push(minValue);
    } else {
      console.log(`No valid numbers found`);
    }
  }
  if (MaxArray.length === MinArray.length) {
    for (let i = 0; i < MaxArray.length; i++) {
      difArray[i] = MaxArray[i] - MinArray[i];
    }
  } else {
    console.log("ERROR!");
  }

  let result = 0;
  difArray.map((e) => (result += e));
  console.log(`result = ${result}`);
}

async function part2() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });
  
    let totalSum = 0;
  
    for await (const line of rl) {
      let numbers = line.trim().split(/\s+/).map(Number);
  
      for (let i = 0; i < numbers.length; i++) {
        for (let j = 0; j < numbers.length; j++) {
          if (i !== j && numbers[i] % numbers[j] === 0) {
            totalSum += numbers[i] / numbers[j];
            break;
          }
        }
      }
    }
  
    console.log(`results = ${totalSum}`);
  }

part1();
part2();