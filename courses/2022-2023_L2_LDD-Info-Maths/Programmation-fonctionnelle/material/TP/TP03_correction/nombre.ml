type frac = { num : int;
              denom : int }

let rec pgcd a b =
  if b = 0 then a
  else
    pgcd b (a mod b)


let neg_frac f = { num = -f.num; denom = f.denom }

let sign i = if i > 0 then 1 else if i = 0 then 0 else -1
let simp_frac f =
  let num, denom =
    if sign f.num * sign f.denom >=0 then
        abs f.num, abs f.denom
    else
      -(abs f.num), (abs f.denom)
  in
  let p = pgcd (abs num) denom in
  { num = num / p; denom = denom / p }


let frac a b = simp_frac { num = a; denom = b}

let add_frac f1 f2 =
    frac
    (f1.num * f2.denom + f2.num * f1.denom)
    (f1.denom * f2.denom)

let sub_frac f1 f2 = add_frac f1 (neg_frac f2)

let mul_frac f1 f2 =
  frac (f1.num * f2.num) (f1.denom * f2.denom)

let inv_frac f = frac f.denom f.num

let div_frac f1 f2 =
  mul_frac f1 (inv_frac f2)

let string_of_frac f = Printf.sprintf "%d/%d" f.num f.denom

let float_of_frac f = (float f.num) /. (float f.denom)


let test_frac () =
  Printf.printf "%s \n" (string_of_frac (frac 2 10));
  Printf.printf "%s \n" (string_of_frac (frac 5 10));
  Printf.printf "%s \n" (string_of_frac (frac 100 20));
  Printf.printf "%s \n" (string_of_frac (add_frac (frac 2 10) (frac 4 10)));
  Printf.printf "%s \n" (string_of_frac (frac (-2) 10));
  Printf.printf "%s \n" (string_of_frac (frac (-5) (-10)));
  Printf.printf "%s \n" (string_of_frac (frac 100 (-20)));
  Printf.printf "%s \n" (string_of_frac (mul_frac (frac (-2) 10) (frac (-4) 10)))


let () = test_frac ()

type num =
    Float of float
  | Int of int
  | Frac of frac

let string_of_num n =
  match n with
  Int i -> string_of_int i
  | Float fl -> string_of_float fl
  | Frac fr -> string_of_frac fr

let exec_op n1 n2 op_i op_fr op_fl =
  match n1, n2 with
    Float fl1, Float fl2 -> Float (op_fl fl1 fl2)
  | Float fl1, Frac fr2 -> Float (op_fl fl1 (float_of_frac fr2))
  | Float fl1, Int i2 -> Float (op_fl fl1 (float i2))
  | Frac fr1, Float fl2 -> Float (op_fl (float_of_frac fr1) fl2)
  | Frac fr1, Frac fr2 -> Frac(op_fr fr1 fr2)
  | Frac fr1, Int i2 -> Frac(op_fr fr1 (frac i2 1))
  | Int i1, Float fl2 -> Float(op_fl (float i1) fl2)
  | Int i1, Frac fr2 -> Frac(op_fr (frac i1 1) fr2)
  | Int i1, Int i2 -> Int (op_i i1 i2)

let add n1 n2 =
  exec_op n1 n2 (+) add_frac (+.)

let sub n1 n2 =
  exec_op n1 n2 (-) sub_frac (-.)
let neg n = sub (Int 0) n

let mul n1 n2 =
  exec_op n1 n2 ( * ) (mul_frac) ( *.)

let div n1 n2 =
  exec_op n1 n2 ( /) (div_frac) ( /.)

let inv n = div (Int 1) n

let pow n k =
  let rec loop k acc =
    if k = 0 then acc
    else
      loop (k-1) (mul n acc)
    in
  loop k (Int 1)

let test () =
  Printf.printf "%s\n"  (string_of_num (pow (Int 2) 10));
  Printf.printf "%s\n"  (string_of_num (pow (Frac (frac 2 5)) 10));
  Printf.printf "%s\n"  (string_of_num (pow (Float 2.5) 14))

let () = test ()
