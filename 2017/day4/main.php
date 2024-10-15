<?php
// Function to count the number of valid passphrases
function count_valid_passphrases($input) {
    $valid_count = 0;

    // Loop through each passphrase in the input
    foreach ($input as $passphrase) {
        // Split the passphrase into words
        $words = explode(' ', $passphrase);
        
        // Check if the number of unique words is equal to the number of words
        if (count($words) === count(array_unique($words))) {
            // If they are equal, the passphrase is valid
            $valid_count++;
        }
    }

    return $valid_count;
}

// Example input: you can replace this with your actual input
$input = file('input.txt', FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

// Count the number of valid passphrases
$valid_passphrases = count_valid_passphrases($input);

// Output the result
echo "part1" . PHP_EOL;

echo "Valid passphrases: " . $valid_passphrases . PHP_EOL;


function is_valid_passphrase2($passphrase) {
    // Split the passphrase into words
    $words = explode(' ', $passphrase);
    
    // Sort the characters in each word to detect anagrams
    $sorted_words = array_map(function($word) {
        $chars = str_split($word);
        sort($chars);
        return implode('', $chars);
    }, $words);

    // If the number of unique sorted words equals the number of words, it's valid
    return count($sorted_words) === count(array_unique($sorted_words));
}

// Function to count valid passphrases according to the new policy
function count_valid_passphrases2($input) {
    $valid_count = 0;

    // Loop through each passphrase in the input
    foreach ($input as $passphrase) {
        if (is_valid_passphrase2($passphrase)) {
            $valid_count++;
        }
    }

    return $valid_count;
}

// Count the number of valid passphrases (lines)
$valid_passphrases2 = count_valid_passphrases2($input);

echo "part2" . PHP_EOL;

echo "valid passphrases: " . $valid_passphrases2 . PHP_EOL;
?>