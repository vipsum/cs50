SELECT  m.title, r.rating
FROM movies AS m
INNER JOIN ratings AS r
ON r.movie_id = m.id
WHERE year=2010
ORDER BY 2 DESC, 1;


