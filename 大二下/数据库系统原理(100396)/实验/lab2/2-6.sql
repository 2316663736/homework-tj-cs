-- 6. 查询女性读者的总人数
SELECT COUNT(*) AS 女性读者总人数
FROM readers
WHERE Gender = 'Female';