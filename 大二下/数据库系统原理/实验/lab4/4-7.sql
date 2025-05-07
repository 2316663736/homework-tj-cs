SELECT DISTINCT V.Viewer_no
FROM Viewer AS V
NATURAL JOIN Watch AS W  
NATURAL JOIN Movie AS M  
WHERE M.Movie_name = '星际穿越'
AND V.Viewer_no NOT IN (
    SELECT W.Viewer_no
    FROM Watch W
    JOIN Movie M ON W.Movie_no = M.Movie_no
    WHERE M.Movie_name = '盗梦空间'
)
ORDER BY V.Viewer_no ASC;