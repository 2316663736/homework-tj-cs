-- 10. 查询借阅过编号为1或者编号为2图书的读者No
SELECT DISTINCT R_no AS 读者编号
FROM borrow_records
WHERE B_no = 1 OR B_no = 2;