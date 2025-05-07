-- 查询借阅过编号为3的图书的读者的Name和Tel
SELECT r.Name, r.Tel
FROM readers r
JOIN borrow_records br ON r.No = br.R_no
WHERE br.B_no = 3;