EXIT;
-- Jay登录
obclient -uJay -p1234567 -h127.1 -P2881
-- 尝试查询Players表，会报错
SELECT * FROM Major.Players;