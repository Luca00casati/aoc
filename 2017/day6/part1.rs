use std::collections::HashMap;

fn reallocation_cycles_and_loop_size(mut banks: Vec<u32>) -> (u32, u32) {
    let mut seen_configs = HashMap::new();
    let mut cycles = 0;

    while !seen_configs.contains_key(&banks) {
        seen_configs.insert(banks.clone(), cycles);

        let (mut max_index, &max_blocks) = banks
            .iter()
            .enumerate()
            .max_by_key(|&(i, &blocks)| (blocks, -(i as i32)))
            .unwrap();
        
        banks[max_index] = 0;
        for _ in 0..max_blocks {
            max_index = (max_index + 1) % banks.len();
            banks[max_index] += 1;
        }

        cycles += 1;
    }

    let first_seen_cycle = seen_configs[&banks];
    let loop_size = cycles - first_seen_cycle;

    (cycles, loop_size)
}

fn main() {
    let input = vec![10,3,	15,	10,	5,	15,	5,	15,	9,	2,	5,	8,	5,	2,	3,	6];
    let (cycles, loop_size) = reallocation_cycles_and_loop_size(input);
    println!("Cycles before repetition: {}", cycles);
    println!("Size of the loop: {}", loop_size);
}
