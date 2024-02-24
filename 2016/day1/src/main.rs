use std::collections::HashSet;

fn main() {
    let directions: [&str; 162] = [
        "L1", "L5", "R1", "R3", "L4", "L5", "R5", "R1", "L2", "L2", "L3", "R4", "L2", "R3", "R1",
        "L2", "R5", "R3", "L4", "R4", "L3", "R3", "R3", "L2", "R1", "L3", "R2", "L1", "R4", "L2",
        "R4", "L4", "R5", "L3", "R1", "R1", "L1", "L3", "L2", "R1", "R3", "R2", "L1", "R4", "L4",
        "R2", "L189", "L4", "R5", "R3", "L1", "R47", "R4", "R1", "R3", "L3", "L3", "L2", "R70",
        "L1", "R4", "R185", "R5", "L4", "L5", "R4", "L1", "L4", "R5", "L3", "R2", "R3", "L5", "L3",
        "R5", "L1", "R5", "L4", "R1", "R2", "L2", "L5", "L2", "R4", "L3", "R5", "R1", "L5", "L4",
        "L3", "R4", "L3", "L4", "L1", "L5", "L5", "R5", "L5", "L2", "L1", "L2", "L4", "L1", "L2",
        "R3", "R1", "R1", "L2", "L5", "R2", "L3", "L5", "L4", "L2", "L1", "L2", "R3", "L1", "L4",
        "R3", "R3", "L2", "R5", "L1", "L3", "L3", "L3", "L5", "R5", "R1", "R2", "L3", "L2", "R4",
        "R1", "R1", "R3", "R4", "R3", "L3", "R3", "L5", "R2", "L2", "R4", "R5", "L4", "L3", "L1",
        "L5", "L1", "R1", "R2", "L1", "R3", "R4", "R5", "R2", "R3", "L2", "L1", "L5",
    ];

    // let test1 = ["R2", "L3"];

    // let test2 = ["R2", "R2", "R2"];

    // let test3 = ["R5", "L5", "R5", "R3"];

    // let test4 = ["R8", "R4", "R4", "R8"];

    let mut look = "up";
    let mut pos = (0, 0);
    let mut store: Vec<(i32, i32)> = Vec::new();
    store.push((0, 0));

    for i in &directions {
        look = update_look(look.to_string(), i);
        pos = update_pos(pos, look, i);
        store.push(pos);
        println!("{}", look);
        println!("{:?}", pos);
    }
    println!("-----------");
    println!("{:?}", pos);
    let result = pos.0.abs() + pos.1.abs();
    println!("result = {}", result);

    println!("-----------");
    let step_store = add_step(&store);
    println!("{:?}", step_store);
    println!("-----------");

    if let Some(duplicate) = find_first_duplicate(&step_store) {
        println!("First duplicate found: {:?}", duplicate);
        let result = duplicate.0.abs() + duplicate.1.abs();
        println!("result = {}", result);
    } else {
        println!("No duplicates found");
    }
}

fn add_step(vec: &Vec<(i32, i32)>) -> Vec<(i32, i32)> {
    let mut step_store: Vec<(i32, i32)> = Vec::new();
    for i in 0..(vec.iter().len() - 1) {
        let x1 = vec[i].0;
        let y1 = vec[i].1;
        let x2 = vec[i + 1].0;
        let y2 = vec[i + 1].1;
        step_store.push((x1, y1));
        if x1 > x2{
            for ii in (x2 + 1 ..x1).rev(){
                step_store.push((ii, y1));
            }
        }
        if x2 > x1{
            for ii in x1 + 1 ..x2{
                step_store.push((ii, y1));
            }
        }
        if y1 > y2{
            for ii in (y2 + 1 ..y1).rev(){
                step_store.push((x1, ii));
            }
        }
        if y2 > y1{
            for ii in y1 + 1 ..y2{
                step_store.push((x1, ii));
            }
        }
    }
    step_store.push((vec[vec.len() - 1].0, vec[vec.len() - 1].1));
    step_store
}

fn find_first_duplicate(vec: &Vec<(i32, i32)>) -> Option<(i32, i32)> {
    let mut set = HashSet::new();
    for &item in vec {
        if !set.insert(item) {
            return Some(item);
        }
    }
    None
}

fn update_pos(val_pos: (i32, i32), val_dir: &str, value_c: &str) -> (i32, i32) {
    let mut x = val_pos.0;
    let mut y = val_pos.1;
    let value_int: i32 = value_c[1..].parse().unwrap();
    match val_dir {
        "up" => y += value_int,
        "down" => y -= value_int,
        "right" => x += value_int,
        "left" => x -= value_int,
        _ => println!("error"),
    }
    (x, y)
}

fn update_look(look_val: String, data: &str) -> &str {
    let rl_val: u8 = data.as_bytes()[0];
    let rl = rl_val as char;
    if look_val == "up" {
        return match rl {
            'R' => "right",
            'L' => "left",
            _ => "error",
        };
    };
    if look_val == "down" {
        return match rl {
            'L' => "right",
            'R' => "left",
            _ => "error",
        };
    };
    if look_val == "left" {
        return match rl {
            'L' => "down",
            'R' => "up",
            _ => "error",
        };
    };
    if look_val == "right" {
        return match rl {
            'R' => "down",
            'L' => "up",
            _ => "error",
        };
    };
    data
}
