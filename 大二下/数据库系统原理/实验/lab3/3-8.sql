EXIT;
obclient -uroot@sys -h127.1 -P2881
DROP USER 'Jay'@'%';


--验证jay用户是否真的删除了
obclient -uJay -p1234567 -h127.1 -P2881