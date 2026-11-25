
let rec somme_entiers n =
  if n <= 0 then 0 else
    n + somme_entiers (n-1)
  ;;

Printf.printf "somme_entiers 0 = %d\n" (somme_entiers 0);;
Printf.printf "somme_entiers 5 = %d\n" (somme_entiers 5);;
Printf.printf "somme_entiers 10 = %d\n" (somme_entiers 10);;


let rec somme_carres n =
  if n <= 0 then 0 else
    n*n + somme_carres (n-1)
  ;;

Printf.printf "somme_carres 5 = %d\n"  (somme_carres 5);;
Printf.printf "somme_carres 10 = %d\n" (somme_carres 10);;
Printf.printf "somme_carres 0 = %d\n"  (somme_carres 0);;

let rec leibniz n =
  (* attention, on calcule sur des flottants *)
  if n = 0 then 1.0 else
    let s = if n mod 2 == 0 then 1.0 else -1.0 in
    s *. (1.0 /. float (2*n+1)) +. leibniz (n-1)
  ;;

Printf.printf "4. *. leibniz 10 = %f\n"  (4. *. leibniz 10);;
Printf.printf "4. *. leibniz 50 = %f\n"  (4. *. leibniz 50);;
Printf.printf "4. *. leibniz 100 = %f\n"  (4. *. leibniz 100);;
Printf.printf "4. *. leibniz 500 = %f\n"  (4. *. leibniz 500);;
    