-- 11. 查询既借阅过编号为1又借阅过编号为3图书的读者No
SELECT R_no AS 读者编号
FROM borrow_records
WHERE B_no = 1
AND R_no IN (
    SELECT R_no
    FROM borrow_records
    WHERE B_no = 3
);