-- 1. 在Customers表中添加LastLoginDate字段并创建触发器
-- 首先添加新字段
ALTER TABLE Customers ADD COLUMN LastLoginDate DATETIME;

-- 创建更新LastLoginDate的触发器
-- 假设有一个客户登录的表或操作，我们可以在其中创建触发器
-- 由于没有实际的登录表，这里创建一个模拟登录的存储过程和相应的触发器

-- 创建一个存储过程来模拟客户登录
DELIMITER $$
CREATE PROCEDURE CustomerLogin(IN customer_id INT)
BEGIN
    UPDATE Customers
    SET LastLoginDate = CURRENT_TIMESTAMP
    WHERE CustomerID = customer_id;
END$$
DELIMITER ;

-- 2. 将Customers表中的name由VARCHAR改为CHAR(15)
ALTER TABLE Customers MODIFY COLUMN Name CHAR(15) NOT NULL;

-- 3. 修改Products表，添加IsFeatured字段并创建索引
-- 添加字段
ALTER TABLE Products ADD COLUMN IsFeatured BOOLEAN DEFAULT FALSE;

-- 创建索引
CREATE INDEX idx_featured_products ON Products(IsFeatured);

-- 4. 删除Categories表中没有关联商品的分类记录（创建存储过程）
DELIMITER $$
CREATE PROCEDURE DeleteUnusedCategories()
BEGIN
    -- 删除没有关联商品的分类
    DELETE FROM Categories
    WHERE CategoryID NOT IN (
        SELECT DISTINCT CategoryID FROM Products
    );
    
    -- 输出删除的记录数
    SELECT CONCAT('Deleted ', ROW_COUNT(), ' unused categories.') AS Result;
END$$
DELIMITER ;

-- 调用存储过程来执行删除操作
-- CALL DeleteUnusedCategories();