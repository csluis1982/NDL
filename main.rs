use std::env;
use std::fs::File;
use std::io::{self, BufRead, BufReader};
use std::io;
use std::process;

#[derive(Debug, Clone, PartialEq)]
pub enum TokenType {
    // Single-character tokens & symbols
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    Comma,
    Dot,
    Colon,
    Arrow, // "->"

    // Literals with data
    Identifier(String),
    StringLiteral(String),
    Number(f64),

    // Keywords
    Node,
    Func,
    Net,
    Return,

    // End-of-file & Errors
    Eof,
    Invalid(char),
}

#[derive(Debug, Clone, PartialEq)]
pub struct Span {
    pub line: usize,
    pub column: usize,
    pub start: usize,
    pub end: usize,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Token {
    pub token_type: TokenType,
    pub span: Span,
    pub lexeme: String,
}

impl Token {
    pub fn new(token_type: TokenType, span: Span, lexeme: impl Into<String>) -> Self {
        Self {
            token_type,
            span,
            lexeme: lexeme.into(),
        }
    }
}

fn main() -> io::Result<()> {
    // You can also grab the argument using an iterator directly:
    let filename = match env::args().nth(1) {
        Some(path) => path,
        None => {
            eprintln!("Error: Missing filename argument.");
            eprintln!("Usage: cargo run -- <filename>");
            process::exit(1);
        }
    };

    // Open file
    let file = File::open(&filename)?;
    let reader = BufReader::new(file);

    // Read line-by-line
    for (index, line) in reader.lines().enumerate() {
        let line = line?;
        println!("{}: {}", index + 1, line);
        parse(&line);
    }

    Ok(())
}

fn parse(&mut stream : String){
    let mut tokens = Token::new();
    tokens = lexer(&line);
    
    return;
}

 
fn lexer( &mut line : String) -> Token  {
    
}


