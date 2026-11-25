open Heap

let pr_int_array t = Array.iter (fun x -> Printf.printf "%d " x) t;
  Printf.printf "\n"

let pr_string_array t = Array.iteri (fun i x -> if x <> "" then Printf.printf "(%c, %s); " (Char.chr i) x) t;
  Printf.printf "\n"

let pr_list_tuple lt = 
  List.iter 
  (fun (a, b) ->
    let c = 
      match b with
      | Leaf ch -> ch
      | _ -> assert false
    in
    Printf.printf "(%d, %c) " a c
  ) 
  lt;
  Printf.printf "\n"

let pr_tree t =
  let rec loop t =
    match t with
    | Leaf(a) -> Char.escaped a
    | Node(t1,t2) -> ("("^(loop t1)^","^(loop t2)^")")
  in
  Printf.printf "%s \n" (loop t)
  