function captchaSolution1(input) {
    let sum = 0;
    const length = input.length;

    for (let i = 0; i < length; i++) {
        const currentDigit = parseInt(input[i], 10);
        const nextDigit = parseInt(input[(i + 1) % length], 10);

        if (currentDigit === nextDigit) {
            sum += currentDigit;
        }
    }

    return sum;
}

// Test cases
console.log(captchaSolution1("1122")); // Output: 3
console.log(captchaSolution1("1111")); // Output: 4
console.log(captchaSolution1("1234")); // Output: 0
console.log(captchaSolution1("91212129")); // Output: 9

//part1
const fs = require('node:fs')
fs.readFile('input.txt', 'utf8', (err, data) => {
  if (err) {
    console.error(err);
    return;
  }
  console.log(captchaSolution1(data)); // Output: 1119
});

function captchaSolution2(input) {
    let sum = 0;
    const length = input.length;
    const halfway = length / 2;

    for (let i = 0; i < length; i++) {
        const currentDigit = parseInt(input[i], 10);
        const matchDigit = parseInt(input[(i + halfway) % length], 10);

        if (currentDigit === matchDigit) {
            sum += currentDigit;
        }
    }

    return sum;
}

// Test cases
console.log(captchaSolution2("1212"));      // Output: 6
console.log(captchaSolution2("1221"));      // Output: 0
console.log(captchaSolution2("123425"));    // Output: 4
console.log(captchaSolution2("123123"));    // Output: 12
console.log(captchaSolution2("12131415"));  // Output: 4

//part2
fs.readFile('input.txt', 'utf8', (err, data) => {
    if (err) {
      console.error(err);
      return;
    }
    console.log(captchaSolution2(data)); // Output: 1420
  });