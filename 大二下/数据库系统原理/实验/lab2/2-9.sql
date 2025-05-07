-- 9. 计算每本图书的平均借阅时长，输出平均借阅时长超过15天的图书的No
SELECT 
    B_no AS 图书编号,
    AVG(DATEDIFF(Return_date, Borrow_date)) AS 平均借阅时长
FROM 
    borrow_records
WHERE 
    Return_date IS NOT NULL
GROUP BY 
    B_no
HAVING 
    AVG(DATEDIFF(Return_date, Borrow_date)) > 15;