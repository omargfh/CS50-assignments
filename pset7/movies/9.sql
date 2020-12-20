SELECT DISTINCT people.name FROM stars
JOIN people ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.year = 2004
ORDER by people.birth;