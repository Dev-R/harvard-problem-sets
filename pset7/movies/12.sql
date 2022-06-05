/*
                                          ** PSEUDO CODE  ** 
movies(title): (movies(id) -> stars(movie_id) WHERE stars(person_id) IN -> people(id) people(name)) )

*/
SELECT title FROM movies
WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Johnny Depp"))
AND id IN(SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Helena Bonham Carter"));



