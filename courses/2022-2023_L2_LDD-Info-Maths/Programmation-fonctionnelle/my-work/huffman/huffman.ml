  open Huff
  open Heap
  open Bs
  open Affichage

  let decompress inName outName = 
    let ic1 = open_in (inName) in
    let c  = (ic_to_col ic1) in
    let ht = construct_huff_tree c in
    let oc = open_out (outName) in
    let ic = of_in_channel ic1 in
    let rec aux ic t =
      match t with 
        | Leaf(c)    -> output_char oc c; aux ic ht 
        | Node(l, r) -> (
          match (try_read_bit ic) with 
            | Some 0 -> aux ic l
            | Some _ -> aux ic r
            | None -> ())
    in aux ic ht;
    close_out oc;
    close_in ic1

  let compress inName outName =
    let oc = open_out outName in
    let ic = open_in inName in
    let c  = char_freq_to_tuple_list (char_freq ic) in
    close_in ic;
    let ic = open_in inName in
    let ht = construct_huff_tree c in
    let tc = codage_each ht in
    write_col_in_file c oc;
    encode_text tc ic (of_out_channel oc);
    close_in ic;
    close_out oc


let help argv = 
    Printf.printf "Usage: %s <filename> [options]\n" argv.(0);
    Printf.printf "Options:\n";
    Printf.printf "  -s, --stats              Display the stats of the compression\n";
    Printf.printf "  -h, --help               Display this help and exit\n";
    exit 0

let exec string = let _ = Sys.command string in ()
  
let stats name compressName time mode = 
      (match Sys.os_type with
      | "Unix" ->
      (
        exec ("uname > os_tmp.txt");
        let ic = open_in "os_tmp.txt" in
        let os = input_line ic in
        close_in ic;
        exec ("rm os_tmp.txt");
        match os with
        | "Darwin" ->
            exec ("stat -f %z "^name^" > size_tmp.txt");
            exec ("stat -f %z "^compressName^" >> size_tmp.txt")
        | "Linux" ->
          exec ("stat -c %s "^name^" > size_tmp.txt");
          exec ("stat -c %s "^compressName^" >> size_tmp.txt")
        | _ ->
            Printf.printf "\x1b[31mOS not supported, please dont use --stats!\x1b[0m";
            exit 2
      )
      | "Cigwin" ->
        exec ("stat -c %s "^name^" > size_tmp.txt");
        exec ("stat -c %s "^compressName^" >> size_tmp.txt")
      | "Win32" ->
        exec ("for %I in ("^name^") do @echo %~zI > size_tmp.txt");
        exec ("for %I in ("^compressName^") do @echo %~zI >> size_tmp.txt")
      | _ -> 
        Printf.printf "\x1b[31mOS not supported, please dont use --stats!\x1b[0m"
      );
      let ic = open_in "size_tmp.txt" in
      let size1 = int_of_string (input_line ic) in
      let size2 = int_of_string (input_line ic) in
      close_in ic;
      if Sys.unix || Sys.cygwin then
        exec ("rm size_tmp.txt")
      else
        exec ("del size_tmp.txt");
      Printf.printf "\x1b[34mSize of the original file:\x1b[0m %d bytes\n" size1;
      Printf.printf "\x1b[34mSize of the compressed file:\x1b[0m %d bytes\n" size2;
      Printf.printf "\x1b[34mCompression ratio:\x1b[0m %f%c\n" (100. -. float_of_int size2 /. float_of_int size1 *. 100.) '%';
      if mode = "compress" then
        Printf.printf "\x1b[34mCompression time:\x1b[0m %f seconds\n" time
      else
        Printf.printf "\x1b[34mDecompression time:\x1b[0m %f seconds\n" time

let scan_args argv argc = 
  let rec aux argv argc i = 
    if i >= argc then false else
      match argv.(i) with
      | "-h" | "--help"  -> help argv
      | "-s" | "--stats" -> true
      | s when i > 1 -> 
        Printf.printf "\x1b[31mInvalid option:\x1b[0m %s\n" s;
        Printf.printf "Usage: %s <filename> [options]\n" argv.(0);
        Printf.printf "type %s --help or -h for help\n" argv.(0);
        exit 2
      | _ -> aux argv argc (i+1)
  in aux argv argc 1


let () = 
  let argc = Array.length Sys.argv and argv = Sys.argv in
  if argc < 2 then 
    begin
      Printf.printf ("\x1b[31mNot enough arguments !\x1b[0m\n");
      Printf.printf "Usage: %s <filename> [options : -s, -h]\n" argv.(0);
      Printf.printf "type %s --help or -h for help\n" argv.(0);
      exit 2
    end
  else
    let stats_flag = scan_args argv argc in
    let filename = argv.(1) in
    let time = Sys.time() in
    if  Sys.file_exists filename = false then
      begin
        Printf.printf "\x1b[31mFile `%s` not found !\x1b[0m\n" filename;
        exit 2
      end;
    if Filename.extension filename = ".hf" then
      begin
        Printf.printf "\x1b[33mDecompressing %s...\x1b[0m" filename;
        let output = Filename.chop_extension filename in
        decompress filename output;
        Printf.printf "\x1b[32m Done!\x1b[0m\n";
        Printf.printf "\x1b[34mOutput file:\x1b[0m %s\n" output;
        if stats_flag then
          stats output filename (Sys.time() -. time) "decompress"
      end
    else 
      begin
        let output = filename^".hf" in
        Printf.printf "\x1b[33mCompressing %s...\x1b[0m" filename;
        compress filename output;
        Printf.printf "\x1b[32m Done!\x1b[0m\n";
        Printf.printf "\x1b[34mOutput file:\x1b[0m %s\n" output;
        if stats_flag then
          stats filename output (Sys.time() -. time) "compress"
      end