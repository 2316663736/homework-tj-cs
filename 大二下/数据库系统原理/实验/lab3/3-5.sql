-- 退出Jay用户，并以root用户重新登录
EXIT;
obclient -uroot@sys -h127.1 -P2881
-- 授予用户Jay对Players表的查询、插入、修改等权限，并允许再授权
GRANT SELECT, INSERT, UPDATE, DELETE ON Major.Players TO 'Jay'@'%' WITH GRANT OPTION;