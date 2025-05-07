-- 12. 建立包含图书名字、作者、出版年份和图书类别的视图
CREATE VIEW book_information AS
SELECT 
    b.Title AS stitle,
    b.Author AS sauthor,
    b.publication_year AS spublicationyear,
    c.Name AS categoryname
FROM 
    books b
JOIN 
    category c ON b.C_no = c.No;

-- 验证视图创建结果
SELECT * FROM book_information;