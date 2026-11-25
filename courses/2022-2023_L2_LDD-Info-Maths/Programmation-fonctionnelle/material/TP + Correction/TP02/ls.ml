let rec affiche_tab_rec i a =
  if i < Array.length a then begin
    Printf.printf "    %s\n" a.(i);
    affiche_tab_rec (i+1) a
  end
;;

let rec affiche_tab a =
  affiche_tab_rec 0 a
;;


(* q2*)
(*
affiche_tab Sys.argv ;;
*)

let rec affiche_dir d =
  if Sys.is_directory d then begin
    Printf.printf "%s:\n%!" d;
    let t = Sys.readdir d in
    affiche_tab t;
    Sys.chdir d;
    affiche_dir_iter 0 t;
    Sys.chdir ".."
  end
and affiche_dir_iter i t =
    if i < Array.length t then begin
      affiche_dir t.(i);
      affiche_dir_iter (i+1) t
    end
;;

affiche_dir "."
;;
