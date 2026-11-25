type tree =
| Leaf of  (char)
| Node of tree * tree
type t = (int * tree)
type col = t list
(** The type of heaps. Elements are ordered using generic comparison.
*)

val char_freq_to_tuple_list : int array -> col

val empty : col
(** [empty] is the empty heap. *)

val add : t -> col -> col
(** [add e h] add element [e] to [h]. *)

val sorted_remove_min : 'a list -> 'a * 'a list

val is_singleton : col -> bool
(** [is_singleton h] returns [true] if [h] contains one element *)

val is_empty : col -> bool
(** [is_empty h] returns [true] if [h] contains zero element *)

val fusion_tree : tree -> tree -> tree

val construct_huff_helper : t list -> t list

val construct_huff_tree : t list -> tree

val sag : tree -> tree

val sad : tree -> tree

val codage_each : tree -> string array
