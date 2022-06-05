/*
                                          ** PSEUDO CODE  ** 
movies(title): (movies(id)- > ratings(movie_id)  -> stars(movie_id) WHERE stars(person_id) -> people(name)) ORDER BY ratings DESC LIMIT 5
*/
/*
                                          ** PSEUDO CODE  ** 
movies(title): (movies(id)- > ratings(movie_id)  -> stars(movie_id) WHERE stars(person_id) -> people(name)) ORDER BY ratings DESC LIMIT 5
*/
SELECT title 
FROM movies 
JOIN ratings ON movies.id = ratings.movie_id 
JOIN stars ON stars.movie_id = ratings.movie_id 
WHERE stars.person_id = (SELECT id FROM people WHERE name = 'Chadwick Boseman')
ORDER BY rating DESC LIMIT 5;
