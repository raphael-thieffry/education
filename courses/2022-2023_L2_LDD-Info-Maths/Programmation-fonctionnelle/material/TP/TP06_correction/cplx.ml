let time f a =
  Gc.compact ();
  let t0 = Unix.gettimeofday () in
  let r = f a in
  let t1 = Unix.gettimeofday () in
  (r, (t1 -. t0) *. 1000.)
;;

let gen_list f n =
  let rec loop i acc =
    if i < 0 then acc
    else loop (i-1) ((f i)::acc)
  in loop (n-1) []


let rand_list n = gen_list (fun _ -> Random.int n) n
let int_list n = gen_list (fun i -> i) n


let insert_sort comp l =
  let rec ins  l x =
    match l with
    [] -> [ x ]
    | y :: ll ->
    if comp x y <= 0 then x :: y :: ll
    else
      y :: ins ll x
  in
  List.fold_left ins [] l
;;

let quick_sort comp l =
  let rec split l e acc_s acc_b =  
    match l with
    [] -> acc_s, acc_b
    | x :: ll -> 
      let c = comp x e in
      if c < 0 then
       split ll e (x :: acc_s) acc_b
      else 
       split ll e acc_s (x::acc_b)
  in
  let rec loop l =
    match l with
    [] -> l
    | e :: ll -> 
      let ls, lb = split ll e [] [] in
    (loop ls) @  [e] @  (loop lb)
  in
  loop l
;;

let test_sort f n sizes =
  Random.init 42;
  Printf.printf "%s\n" n;
  List.iter (fun s ->
    let l = int_list s in
    let res, t = time f l in
    Printf.printf "%d (trié) \t%f\n%!" s t;
    let l = rand_list s in
    let res, t = time f l in
    Printf.printf "%d (random) \t%f\n%!" s t
    ) sizes;
  Printf.printf "\n\n"

  ;;

let () = test_sort (insert_sort compare) "insert_sort" [0;1;10;20;50;100;200;500;1000;10000] 
let () = test_sort (quick_sort compare) "quick_sort" [0;1;10;20;50;100;200;500;1000;20000] 
let () = test_sort (List.sort compare) "List.sort" [0;1;10;20;50;100;200;500;1000;20000] 


(* partie 2 *)
let pivot_random l =
  let n = List.length l in
  let i = Random.int n in
  let rec loop j l acc =
    match l with
    [] -> failwith "pivot_random"
    | e::ll ->
      if j = i then
        e, List.rev_append ll acc
      else
        loop (j+1) ll (e::acc)
  in loop 0 l []

  let quick_sort_opt comp l =
    let rec split l e acc_s acc_e acc_b =  
      match l with
      [] -> acc_s, acc_e, acc_b
      | x :: ll -> 
        let c = comp x e in
        if c < 0 then
         split ll e (x :: acc_s) acc_e acc_b
        else if c = 0 then 
          split ll e (acc_s) (x::acc_e) acc_b
      else
         split ll e acc_s acc_e (x::acc_b)
    in
    let rec loop l =
      match l with
      [] -> l
      | _ -> let e, ll = pivot_random l in
        let ls, le, lb = split ll e [] [] [] in
      (loop ls) @  le @  (loop lb)
    in
    loop l
  




let () = test_sort (quick_sort_opt compare) "quick_sort_opt" [0;1;10;20;50;100;200;500;1000;20000] ;;

