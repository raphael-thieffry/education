(* Compiler avec ocamlc -o fichier fichier.ml *)
let () = 
  if Array.length Sys.argv < 2 then
    Printf.printf "Pas assez d'arguments\n"
  else
    let f = Sys.argv.(1) in
    if not (Sys.file_exists f) then
      Printf.printf "Le fichier '%s' n'existe pas\n" f
    else
      if Sys.is_directory f then
        Printf.printf "Le répertoire '%s' existe\n" f
      else
        Printf.printf "Le fichier '%s' existe\n" f