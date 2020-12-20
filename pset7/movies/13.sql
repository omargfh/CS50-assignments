SELECT DISTINCT name FROM people
WHERE people.id IN (
	SELECT person_id FROM stars
	JOIN movies ON movies.id = stars.movie_id
	WHERE movie_id IN (
		SELECT movies.id FROM movies
		JOIN stars ON stars.movie_id = movies.id
		JOIN people ON people.id = stars.person_id
		WHERE people.name = "Kevin Bacon" AND people.birth = "1958"
		)
	)
AND NOT name = "Kevin Bacon"
;