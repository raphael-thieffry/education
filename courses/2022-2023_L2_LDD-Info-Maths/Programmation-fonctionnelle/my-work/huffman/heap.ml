type tree =
| Leaf of  (char)
| Node of tree * tree

type t = (int * tree)

type col = t list


let empty = []

let char_freq_to_tuple_list a =
  let l = Array.length a in
  let rec aux a la res =
    if la >= l then res
    else if a.(la) != 0 then
      aux a (la+1) ((a.(la), Leaf(Char.chr la))::res)
    else
      aux a (la+1) res
    in
      List.sort (fun a b -> compare (fst a) (fst b) ) (aux a 0 [])

let is_singleton l = match l with a::[]  -> true | _ -> false

let is_empty l = (l = [])

let rec add e h = 
    match h with
    | [] -> [e]
    | (i, t)::r when i >= (fst e) -> e::h
    | (i, t)::r when i <  (fst e) -> (i, t)::(add e r)
    | _  -> assert false

let sorted_remove_min col =
  match col with
  | []   -> failwith "can't remove nothing"
  | e::r -> (e, r)

let fusion_tree t1 t2 = Node(t1,t2)

let rec construct_huff_helper (col:(t list)) =
  if is_empty col || is_singleton col then 
    col 
  else
    let etape1 = sorted_remove_min col in
    let etape2 = sorted_remove_min (snd etape1) in
    let r = (snd etape2) in
    let tm1 = (fst (fst etape1), snd (fst etape1)) in
    let tm2 = (fst (fst etape2), snd (fst etape2)) in
    let tr = (fusion_tree (snd tm1) (snd tm2)) in
    construct_huff_helper  (add ((fst tm1)+(fst tm2), tr) r)

let construct_huff_tree col =
  let h = construct_huff_helper col in
  match h with
  | []    -> Leaf('0')
  | s::[] -> snd s
  | _     -> failwith "h not singleton"

let sag t =
  match t with
  | Leaf a       -> failwith "no child because leaf"
  | Node(sg, sd) -> sg

let sad t =
  match t with
  | Leaf a       -> failwith "no child because leaf"
  | Node(sg, sd) -> sd

let codage_each ht =
  let rec aux t ht c =
    match ht with
    | Leaf a -> t.(Char.code a) <- c;
                t
    | _ ->
      let arraygauche = (aux t (sag ht) (c^"0")) in
      let arraydroite = (aux t (sad ht) (c^"1")) in
      Array.map2 (
        fun a b -> 
          if compare a "" <> 0 then a 
          else if compare b "" <> 0 then b 
          else ""
      ) arraygauche arraydroite
  in aux (Array.make 256 "") ht ""