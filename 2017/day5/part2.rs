use std::fs::File;
use std::io::{self, BufRead};

fn main() -> io::Result<()> {
    let path = "input.txt";

    let part = 1;
    let file = File::open(&path)?;
    let reader = io::BufReader::new(file);

    // Read each line, parse it to a number, and collect into an array
    let mut arr: Vec<i64> = reader
        .lines()
        .filter_map(|line| line.ok()?.parse::<i64>().ok())
        .collect();

    let mut i: isize = 0;
    let mut step: usize = 0;

    while i >= 0 && i < arr.len() as isize {
        let temp = i;
        i += arr[temp as usize] as isize;
        if part == 2 {
            if arr[temp as usize] >= 3 {
                arr[temp as usize] -= 1;
            } else {
                arr[temp as usize] += 1;
            }
        }
        if part == 1 {
            arr[temp as usize] += 1;
        } else {
            println!("part error");
        }
        step += 1;
    }

    println!("step {}", step);
    Ok(())
}
