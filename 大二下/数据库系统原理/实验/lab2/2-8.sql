-- 8. 向borrow_records表中插入一条记录
INSERT INTO borrow_records (No, B_no, R_no, Borrow_date, Return_date)
VALUES (6, 5, 5, '2025-03-24', NULL);

-- 验证插入结果
SELECT * FROM borrow_records WHERE No = 6;