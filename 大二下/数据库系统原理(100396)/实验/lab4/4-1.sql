CREATE TABLE Movie (
    Movie_no VARCHAR(10) PRIMARY KEY,
    Movie_name VARCHAR(50),
    Director VARCHAR(30),
    Rating FLOAT,
    End_date DATETIME
);

CREATE TABLE Viewer (
    Viewer_no VARCHAR(10) PRIMARY KEY,
    Viewer_name VARCHAR(30),
    Age INT
);

CREATE TABLE Watch (
    S_no VARCHAR(10),
    Viewer_no VARCHAR(10),
    Movie_no VARCHAR(10),
    Watch_date DATETIME,
    PRIMARY KEY(S_no, Viewer_no, Movie_no),
    FOREIGN KEY(Viewer_no) REFERENCES Viewer(Viewer_no) ON DELETE CASCADE,
    FOREIGN KEY(Movie_no) REFERENCES Movie(Movie_no) ON DELETE CASCADE
);