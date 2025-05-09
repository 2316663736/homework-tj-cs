SELECT W.Viewer_no, M.Movie_name, W.Watch_date
FROM Watch AS W
NATURAL JOIN Movie AS M  ;