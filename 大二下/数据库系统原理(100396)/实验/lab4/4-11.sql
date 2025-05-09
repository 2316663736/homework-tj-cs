SELECT DISTINCT V.Viewer_name, V.Viewer_no
FROM Viewer AS V
WHERE V.Viewer_no NOT IN (
    SELECT DISTINCT W.Viewer_no
    FROM Watch AS W
    WHERE W.Repeat_state = TRUE
);