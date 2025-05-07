 

-- 创建category表
CREATE TABLE category (
    No INTEGER PRIMARY KEY NOT NULL,
    Name VARCHAR(100) NOT NULL
);

-- 创建books表
CREATE TABLE books (
    No INTEGER PRIMARY KEY NOT NULL,
    Title VARCHAR(100) NOT NULL,
    Author VARCHAR(100) NOT NULL,
    publication_year INTEGER NOT NULL,
    C_no INTEGER NOT NULL,
    FOREIGN KEY (C_no) REFERENCES category(No)
);

-- 创建readers表
CREATE TABLE readers (
    No INTEGER PRIMARY KEY NOT NULL,
    Name VARCHAR(100) NOT NULL,
    Gender VARCHAR(10) NOT NULL CHECK (Gender IN ('Female', 'Male')),
    Tel VARCHAR(20) NOT NULL
);

-- 创建borrow_records表
CREATE TABLE borrow_records (
    No INTEGER PRIMARY KEY NOT NULL,
    B_no INTEGER NOT NULL,
    R_no INTEGER NOT NULL,
    Borrow_date DATE NOT NULL,
    Return_date DATE,
    FOREIGN KEY (B_no) REFERENCES books(No),
    FOREIGN KEY (R_no) REFERENCES readers(No)
);