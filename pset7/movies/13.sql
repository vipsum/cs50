SELECT name FROM people
WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN
(SELECT movie_id FROM stars
INNER JOIN people ON stars.person_id = people.id
WHERE name ="Kevin Bacon" AND birth=1958)) AND name != "Kevin Bacon";