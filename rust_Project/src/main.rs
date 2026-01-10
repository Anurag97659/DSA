use std::io;
use rand::Rng;
// use std::cmp::Ordering;
fn gussing_game(){
    // ================================================Guessing Game================================================
    println!("Guess the number!");
    let secret_number = rand::thread_rng().gen_range(1..=100);
    println!("The secret number is: {secret_number}");

    loop{
        println!("Please input your guess.");
        let mut guess = String::new();
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        let guess: u32 = guess.trim().parse().expect("Please type a number!");
        println!("You guessed: {guess}");
        // match guess.cmp(&secret_number) {
        //     Ordering::Less => println!("Too small!"),
        //     Ordering::Greater => println!("Too big!"),
        //     Ordering::Equal =>{ 
        //         println!("You win!");
        //         break;}
        // } 
        if secret_number > guess{
            println!("The secret number {secret_number} is greater than your guess {guess}");
        } 
        else if secret_number < guess {
            println!("The secret number {secret_number} is less than your guess {guess}");
        } 
        else{
            println!("The secret number {secret_number} is equal to your guess {guess}");
            break;
        }
    }
}

fn basic_calulator(x:i64, y:i64)-> i64{
    println!("chossen operation: +, -, *, /");
    let mut operation = String::new();
    io::stdin()
        .read_line(&mut operation)
        .expect("Failed to read line");
    let operation = operation.trim();
    let sum = x + y;
    let diff = x - y;
    let product = x * y;
    let quotient = x / y;
    if operation == "+" {
        return sum;
    } 
    else if operation == "-" {
        return diff;
    } 
    else if operation == "*" {
        return product;
    } 
    else if operation == "/" {
        return quotient;
    } 
    else {
        println!("Invalid operation!");
        return 0;
    }

}

fn main() {
    // gussing_game();
    let result = basic_calulator(10, 5);
    println!("The result is: {result}");

    // ================================================Data Types and Mathematical Operations================================================
    // u8,u16,u32,u64,u128,usize == unsigned integer -- can be only positive for example 0,1,2 
    // i8,i16,i32,i64,i128,isize == signed integer -- can be negative and can be positive for example -1,0,1 
    // f32,f64 == floating point number -- for example 3.14,2.0,-0.1
    // char == character -- for example 'a','b','1','$'
    // bool == boolean -- for example true,false
    // println!("some mathematical operations:");
    // let diff : i32 = 5-10; 
    // let difference : f32 = 4.3 - 95.5 ; 
    // let product = 4 * 30;
    // let quotient = 56.7 / 32.2;
    // let remainder = 43 % 5;
    // println!("diff: {diff}, Difference: {difference}, Product: {product}, Quotient: {quotient}, Remainder: {remainder}");

    // -----tuples-----
    // let tup: (i32, f64, u8) = (500, 6.4, 1);
    // let (_x, _y, _z) = tup;
    // println!("The value of y is: {_y}");
    // // accessing the values of tuple using index:
    // println!("The value of z is: {}", tup.2);
    // println!("The value of x is: {}", tup.0);
    
    
    
}