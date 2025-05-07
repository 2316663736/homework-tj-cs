-- 删除已存在的存储过程
DROP PROCEDURE IF EXISTS update_rstate;

-- 创建新的存储过程
DELIMITER $$
CREATE PROCEDURE update_rstate()
BEGIN
    -- 逐个记录更新Repeat_state字段
    UPDATE Watch W1 
    SET Repeat_state = EXISTS(
        SELECT 1 
        FROM Watch W2 
        WHERE W2.Viewer_no = W1.Viewer_no 
        AND W2.Movie_no = W1.Movie_no 
        AND W2.S_no != W1.S_no
    );
END$$
DELIMITER ;

CALL update_rstate();


SELECT * FROM Watch;