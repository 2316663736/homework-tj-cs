-- 7. 查询借阅时长超过15天的借阅记录
SELECT r.Name AS 读者姓名, b.Title AS 图书标题
FROM borrow_records br
JOIN readers r ON br.R_no = r.No
JOIN books b ON br.B_no = b.No
WHERE br.Return_date IS NOT NULL 
  AND DATEDIFF(br.Return_date, br.Borrow_date) > 15;