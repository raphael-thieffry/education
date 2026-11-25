-------------------------------------------------------------------------------
-- bibli_actions.sql
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
-- ordres tapes par le programmeur :
-- action 0.

drop table livre;
drop table exemplaire;
drop table client;
drop table nbEmpruntsPlusResas;
drop table emprunt;
drop table reservation;

create table livre(
  idl int,
  titre varchar(25),
  auteur varchar(10),
  unique (titre, auteur)
);

-- rem : varchar pas plus 10 caracteres, sinon affichage select illisible

create table exemplaire(
  ide int,
  idl int,
  etat varchar(5) default 'neuf'
);

create table client(
  idc int,
  nom varchar(10)
);

create table nbEmpruntsPlusResas(
  nbmax int
);

create table emprunt(
  ide int,
  idc int
);

create table reservation(
  idl int,
  idc int,
  jour int
);

-------------------------------------------------------------------------------
-- employes :
-------------------------------------------------------------------------------
--  action 1.
select * from livre;

-------------------------------------------------------------------------------
-- 2.
insert into livre values(1, 'Pays de neige', 'Kawabata');
insert into livre values(2, 'Les planches courbes', 'Bonnefoy');
insert into livre values(3, 'La terre nous est etroite', 'Darwich');

-------------------------------------------------------------------------------
-- 3. 
select * from exemplaire;

-------------------------------------------------------------------------------
-- 4. 
insert into exemplaire(ide, idl) values(10, 1);
insert into exemplaire values(11, 1, 'bon');
insert into exemplaire values(12, 1, 'vieux');
insert into exemplaire(ide, idl) values(13, 2);
insert into exemplaire values(14, 3, 'vieux');

-------------------------------------------------------------------------------
-- 5. 
select titre, nom 
  from emprunt, exemplaire, livre, client
  where emprunt.ide = exemplaire.ide
    and exemplaire.idl = livre.idl
    and emprunt.idc = client.idc;

-------------------------------------------------------------------------------
-- clients :
-------------------------------------------------------------------------------
-- 6. 
-- traitement 1 : 

-- exemple sur Rita :
-- choix d'un identifiant, disons 100
-- rem : identifiant pas parametre, donc choisi dans traitement
insert into client values(100, 'Rita');
select count(*)
  from client
  where nom = 'Rita';
-- renvoie : 1

-- exemple sur une autre Rita :
-- choix d'un identifiant, disons 101
-- rem : identifiant pas parametre, donc choisi dans traitement
insert into client values(101, 'Rita');
select count(*)
  from client
  where nom = 'Rita';
-- renvoie : 2

-- exemple sur Riton :
-- choix d'un identifiant, disons 102
insert into client values(102, 'Riton');
select count(*)
  from client
  where nom = 'Riton';
-- renvoie : 1

-- modele d'ordre :
-- traitement1 (n) = 
--   choix d'un nouvel identifiant unique, disons i
--   insert into client values(i, n);
--   select count(*)
--     from client
--     where nom = n;
--     renvoie : k
--   return k;

-------------------------------------------------------------------------------
-- 7. 
-- traitement 2 : 

-- exemple sur Rita, idc 100, jour 45, veut oeuvre 3, il y a exemplaire libre :
select ide
  from exemplaire 
  where idl = 3
    and ide not in (select ide
                      from emprunt);
-- renvoie : 14
insert into emprunt values (14, 100);

-- exemple sur Riton, idc 102, jour 46, veut oeuvre 3, pas d'exemplaire libre :
select ide
  from exemplaire 
  where idl = 3
    and ide not in (select ide
                      from emprunt);
-- renvoie : vide
insert into reservation values(3,102,45);

-- exemple sur Rita, idc 100, jour 47, veut oeuvre 1, il y a exemplaire libre :
select ide
  from exemplaire 
  where idl = 1
    and ide not in (select ide
                      from emprunt);
-- renvoie : 10
insert into emprunt values (10, 100);

-- modele d'ordre :
-- traitement 2 (i,il,j) =
--   select ide
--     from exemplaire 
--     where idl = il
--       and ide not in (select ide
--                       from emprunt);
--   renvoie : ie ou vide
--   si ie alors
--     insert into emprunt values(ie,i);
--     return ie;
--   sinon -- vide
--     insert into reservation values(il,i,j);
--     return -1;

-------------------------------------------------------------------------------
-- rem : executer action 10 maintenant pour voir resa Riton avant détruite

-------------------------------------------------------------------------------
-- 8. 
-- traitement 3 : 

-- exemple sur Rita, idc 100, rapporte exemplaire 10, pas de reservation :
delete from emprunt 
  where ide = 10;
select exemplaire.idl, idc, jour
  from exemplaire, reservation
  where exemplaire.ide = 10
    and exemplaire.idl = reservation.idl
  order by jour asc;
-- renvoie : vide

-- exemple sur Rita, idc 100, rapporte exemplaire 14, il y a reservation :
delete from emprunt 
  where ide = 14;
select exemplaire.idl, idc, jour
  from exemplaire, reservation
  where exemplaire.ide = 10
    and exemplaire.idl = reservation.idl
  order by jour asc;
-- renvoie : idl 3, idc 102, jour 46
delete from reservation 
  where idl = 3
    and idc = 102;
insert into emprunt values(14, 102); 

-- modele d'ordre :
-- traitement3 (ie) =
--   delete emprunt 
--     where ide = ie;
--   select idl, idc, jour
--     from exemplaire, reservation
--     where exemplaire.ide = ie
--       and exemplaire.idl = reservation.idl
--     order by jour cresc;
--   renvoie : il, ic, j ou vide
--   si il, ic alors
--     delete reservation 
--       where idl = il
--         and idc = ic;
--     insert into empruntvalues(il, ic); 
--     return ic, j;
--   sinon -- vide
--     return -1;

-------------------------------------------------------------------------------
-- 9. 
select * from livre;

-------------------------------------------------------------------------------
-- 10. 

-- exemple sur Riton, idc 102 :
select titre 
  from reservation, livre 
  where idc = 102
    and reservation.idl = livre.idl;

-- modele d'ordre :
-- consulterReservations(i) = 
-- select titre 
--   from reservation, livre 
--   where idc = i
--     and reservation.idl = livre.idl;

-------------------------------------------------------------------------------
