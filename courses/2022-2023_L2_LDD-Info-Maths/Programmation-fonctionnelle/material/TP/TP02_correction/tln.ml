(* Question 1 
let rec guess n =
  Printf.printf "Saisir un nombre entier < 100:\n";
  let i = read_int () in
  if i = n then Printf.printf "Trouvé !\n"
  else
    begin
      Printf.printf "Trop %s!\n" (if i < n then "petit" else "grand");
      guess n
    end
*)

(* Le code ci-dessous correspond à la question 3, avec le paramètre supplémentaire *)
let rec guess n e =
  Printf.printf "Saisir un nombre entier < 100:\n";
  let i = read_int () in
  if i = n then Printf.printf "Trouvé en %d étape(s)!\n" e
  else
    begin
      Printf.printf "Trop %s!\n" (if i < n then "petit" else "grand");
      guess n (e + 1)
    end



let () =
    let () = Random.self_init () in
    let n = Random.int 101 in
    guess n 1