-- 5. 查询所有男性读者的借阅记录，按借阅日期升序排列
SELECT r.Name AS 读者姓名, b.Title AS 借阅图书, br.Borrow_date AS 借阅日期, br.Return_date AS 归还日期
FROM readers r
JOIN borrow_records br ON r.No = br.R_no
JOIN books b ON br.B_no = b.No
WHERE r.Gender = 'Male'
ORDER BY br.Borrow_date ASC;