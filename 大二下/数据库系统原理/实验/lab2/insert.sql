-- 插入category表数据
INSERT INTO category (No, Name) VALUES
(1, '计算机'),
(2, '文学'),
(3, '历史'),
(4, '科学');


-- 插入books表数据
INSERT INTO books (No, Title, Author, publication_year, C_no) VALUES
(1, 'Python编程实战', '张三', 2021, 1),
(2, '百年孤独', '加西亚·马尔克斯', 1967, 2),
(3, '明朝那些事儿', '当年明月', 2006, 3),
(4, '时间简史', '霍金', 1988, 4),
(5, 'Java核心技术', '凯S.霍斯特曼', 2019, 1);



-- 插入readers表数据
INSERT INTO readers (No, Name, Gender, Tel) VALUES
(1, '小明', 'Male', '13800138000'),
(2, '小红', 'Female', '13900139000'),
(3, '小刚', 'Male', '13600136000'),
(4, '小芸', 'Female', '13700137000'),
(5, '小强', 'Male', '13300133000');

-- 插入borrow_records表数据
INSERT INTO borrow_records (No, B_no, R_no, Borrow_date, Return_date) VALUES
(1, 1, 1, '2024-10-01', '2024-10-20'),
(2, 2, 2, '2024-10-05', '2024-10-25'),
(3, 1, 3, '2024-10-10', '2024-10-30'),
(4, 3, 4, '2024-10-15', '2024-11-01'),
(5, 2, 5, '2024-10-20', NULL);