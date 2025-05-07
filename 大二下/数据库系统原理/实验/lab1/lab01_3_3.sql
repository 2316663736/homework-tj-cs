-- 查询Customers表的约束
SELECT table_name, constraint_name, constraint_type
FROM information_schema.TABLE_CONSTRAINTS
WHERE table_name='Customers';

-- 查询Products表的约束
SELECT table_name, constraint_name, constraint_type
FROM information_schema.TABLE_CONSTRAINTS
WHERE table_name='Products';

-- 查询Categories表的约束
SELECT table_name, constraint_name, constraint_type
FROM information_schema.TABLE_CONSTRAINTS
WHERE table_name='Categories';

-- 查询Orders表的约束
SELECT table_name, constraint_name, constraint_type
FROM information_schema.TABLE_CONSTRAINTS
WHERE table_name='Orders';

-- 查询OrderItems表的约束
SELECT table_name, constraint_name, constraint_type
FROM information_schema.TABLE_CONSTRAINTS
WHERE table_name='OrderItems';