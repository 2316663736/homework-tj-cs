SELECT W.Viewer_no, V.Viewer_name, M.Movie_name, W.Watch_date
FROM Watch AS W
NATURAL JOIN Viewer AS V  
NATURAL JOIN Movie AS M 
WHERE M.End_date < '2024-04-15'
ORDER BY W.Watch_date DESC;