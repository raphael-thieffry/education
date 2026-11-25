open Heap
open Bs
open Affichage

let try_read_bytes ic =
  try Some (input_byte ic) with End_of_file -> None

let try_read_bit ic =
  try Some (read_bit ic) with Bs.End_of_stream -> None

let char_freq file = 
  let rec aux t =
    match try_read_bytes file with
    | Some o -> t.(o) <- t.(o) + 1;
                aux t
    | None -> t
in aux (Array.make 256 0)

let write_col_in_file c oc =
  let rec aux c oc s =
    match c with
    | []        -> s^"\n" (*end signal*)
    | (i, c)::r -> 
      match c with
        | Leaf c -> aux r oc (s^(string_of_int i)^","^(string_of_int (Char.code c))^";")
        | _      -> failwith "tuple list to string does not work on real trees"
  in Printf.fprintf oc "%s" (aux c oc "") 
  
let rec encode_text tc ic oc =
  match try_read_bytes ic with
  | Some o ->
      String.iter (
        fun c -> (write_bit oc (int_of_char c - 48))
      ) tc.(o);
      encode_text tc ic oc
  | None -> finalize oc
      
let getDebut ic =
  let rec aux ic s = 
    match try_read_bytes ic with
    | Some o -> (
        match (Char.chr o) with
        | '\n' -> s
        | c    -> aux ic (s^(Char.escaped c)))
    | None -> failwith "no end signal"
in aux ic ""

let ic_to_col ic = 
  let s = getDebut ic in
  let s = String.sub s 0 (String.length s - 1) in
  List.map (
  fun s -> 
    let t = String.split_on_char ',' s in
    (int_of_string (List.nth t 0), Leaf(Char.chr (int_of_string (List.nth t 1))))
  ) (String.split_on_char ';' s)