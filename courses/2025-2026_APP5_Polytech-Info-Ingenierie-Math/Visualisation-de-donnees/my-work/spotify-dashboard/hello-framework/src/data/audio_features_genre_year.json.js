import { query } from "./_db.js";

// All genres × year with audio features (no genre limit — filtering is done client-side)
// TABLESAMPLE SYSTEM(15) for speed — averages are statistically stable at this scale
const rows = await query(`
  SELECT
    TRIM(g) AS genre,
    release_year,
    COUNT(*) AS track_count,
    ROUND(AVG(danceability)::numeric, 4)      AS danceability,
    ROUND(AVG(energy)::numeric, 4)            AS energy,
    ROUND(AVG(valence)::numeric, 4)           AS valence,
    ROUND(AVG(tempo)::numeric, 2)             AS tempo,
    ROUND(AVG(acousticness)::numeric, 4)      AS acousticness,
    ROUND(AVG(loudness)::numeric, 3)          AS loudness,
    ROUND(AVG(duration_ms)::numeric, 0) / 60000.0 AS avg_duration_min
  FROM track_details TABLESAMPLE SYSTEM(15),
       LATERAL unnest(string_to_array(genres, ' | ')) AS g
  WHERE genres IS NOT NULL
    AND release_year BETWEEN 1970 AND 2025
  GROUP BY TRIM(g), release_year
  HAVING COUNT(*) > 3
  ORDER BY genre, release_year
`);

process.stdout.write(JSON.stringify(rows));
