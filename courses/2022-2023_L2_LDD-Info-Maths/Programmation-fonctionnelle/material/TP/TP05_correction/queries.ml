type movie = {
    id : int;
    title : string;
    year : int;
    runtime : int;
    rank : int
}

type res = Movie of movie | Invalid | Eof

let input_movie in_c =
  try
    let s = input_line in_c in
    match String.split_on_char ';' s with
    [ s_id; title; s_year; s_runtime ; s_rank ] ->
       Movie {
        id = int_of_string s_id;
        title = title;
        year = int_of_string s_year;
        runtime = int_of_string s_runtime;
        rank = int_of_string s_rank;
      }
    | _ -> Invalid

  with
   End_of_file -> Eof
  | _ -> Invalid


let load_movies f =
  let in_c = open_in f in
  let rec loop in_c acc =
    match input_movie in_c with
    | Eof -> acc
    | Invalid -> loop in_c acc
    | Movie m -> loop in_c (m :: acc)
  in
    let res = loop in_c [] in
    close_in in_c;
    res

let movies = load_movies "movies.csv"


let pr_movie m = Printf.printf
  "{ id=%d, title=\"%s\", year=%d, runtime=%d, rank=%d }"
  m.id  m.title m.year m.runtime m.rank


let pr_movies l =
  List.iter (fun m -> pr_movie m; Printf.printf "\n") l





let moviesTop10 l =
  List.filter (fun m -> m.rank <= 10) l

let () =
    Printf.printf "moviesTop10:\n";
    pr_movies (moviesTop10 movies);
    Printf.printf "--------------\n"

let movies1980 l =
  List.filter (fun m -> m.year < 1990 && m.year >= 1980) l


let () =
    Printf.printf "movies1980:\n";
    pr_movies (movies1980 movies);
    Printf.printf "--------------\n"


let movie_titles l =
    List.map (fun m -> m.title) l

let () =
    Printf.printf "movie titles:\n";
    List.iter (fun t -> Printf.printf "%s" t) (movie_titles movies);
    Printf.printf "--------------\n"


let max_id l =
  List.fold_left (fun acc m -> if m.id > acc then m.id else acc) 0 l


let () = Printf.printf "max_id: %d\n" (max_id movies)

let average_runtime l =
  let total, count =
  List.fold_left (fun (acc_r, acc_c) m ->
    (acc_r +. float m.runtime, acc_c +. 1.0)
    ) (0.0, 0.0) l
  in
  total /. count


let () = Printf.printf "average_runtime: %f\n" (average_runtime movies)



let average_by_year l =
  let ls = List.sort (fun m1 m2 -> compare m1.year m2.year) l in
  let rec loop l acc =
    match l,acc with
      [],_ -> acc
    | m :: lm, [] -> loop lm [(m.year, [m])]
    | m :: lm, (y, ly)::lacc ->
      if m.year = y then loop lm ((y, m::ly) :: lacc)
      else loop lm ((m.year, [m])::acc)
  in
  List.map (fun (y, ly) -> (y, average_runtime ly))
  (loop ls [])

let () = Printf.printf "Average by year:\n";
    List.iter (fun (y, a) ->
    Printf.printf "%d : %f\n" y a
    ) (average_by_year movies)

let () = Printf.printf "--------------\n"



let group_by f l =
  let ls = List.sort (fun m1 m2 -> compare (f m1) (f m2)) l in
  List.fold_left (fun acc m ->
       match acc with
             [] -> [(f m, [m])]
         | (y, ly)::lacc ->
            let fm = f m in
            if fm = y then (y, m::ly)::lacc
            else
               (fm, [m])::acc) [] ls


let average_by_decade l =
  List.map (fun (y, ly) -> (y, average_runtime ly))
      (group_by (fun m -> (m.year - m.year mod 10)) l)


let () =
    Printf.printf "Average by decade:\n";
    List.iter (fun (y, a) ->
    Printf.printf "%d : %f\n" y a
    ) (average_by_decade movies);
    Printf.printf "--------------\n"
