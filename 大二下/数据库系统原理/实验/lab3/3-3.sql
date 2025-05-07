-- 创建用户Jay（使用@'%'表示可以从任何主机连接）
CREATE USER 'Jay'@'%' IDENTIFIED BY '2351295';

-- 授予Jay create table权限，并允许再授权
GRANT CREATE ON Major.* TO 'Jay'@'%' WITH GRANT OPTION;

-- 刷新权限
FLUSH PRIVILEGES;