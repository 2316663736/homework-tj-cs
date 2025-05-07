-- 4. 查询作者姓名中包含"张"字的图书信息
SELECT *
FROM books
WHERE Author LIKE '%张%';