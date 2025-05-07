SELECT V.Viewer_no, V.Viewer_name, V.Age 
FROM Viewer AS V 
NATURAL JOIN Watch AS W 
NATURAL JOIN Movie AS M 
WHERE M.Movie_name = '泰坦尼克号'
ORDER BY V.Viewer_no ASC;