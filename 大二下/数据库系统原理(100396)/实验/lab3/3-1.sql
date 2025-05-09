-- 创建 Major 数据库
CREATE DATABASE Major;

-- 使用 Major 数据库
USE Major;

-- 创建 Players 表
CREATE TABLE Players (
    Sno VARCHAR(10) PRIMARY KEY,
    Sname VARCHAR(20) UNIQUE,
    Ssex VARCHAR(1),
    Sage SMALLINT,
    Steam VARCHAR(20)
);