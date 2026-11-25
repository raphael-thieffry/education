val char_freq : in_channel -> int array

val write_col_in_file : Heap.col -> out_channel -> unit

val encode_text : string array -> in_channel -> Bs.ostream -> unit

val getDebut : in_channel -> string

val ic_to_col : in_channel -> Heap.col

val try_read_bit : Bs.istream -> int option

val try_read_bytes : in_channel -> int option