let bissextile a =
  a mod 4 = 0 && (a mod 100 <> 1 || a mod 400 = 0)

let jour_mois m a =
  if m = 2 then
    if bissextile a then 29 else 28
  else
    let m = if m >= 8 then m - 7 else m in
    30 + (m mod 2)
  ;;
let rec jour_date j m a =
  if m == 1 then j else
    (jour_mois (m-1) a) + jour_date j (m-1) a


let () = Printf.printf "jour_date 31 12 2020 = %d\n" (jour_date 31 12 2020)
let () = Printf.printf "jour_date 31 12 2020 = %d\n" (jour_date 31 12 2019)