-------------------------------------------------------------------------------
/* Contraintes SQL et non SQL. 

Contraintes SQL (bonus en partiel/examen si presentation comme suit) :

client :
    idc pk
    nom not null
    age not null check 16<=age<=120
    avoir not null check 0<=avoir<=2000

village :
    idv pk
    ville not null
    activite -- null possible
    prix not null check 0<prix<=2000
    capacite not null check 1<=capacite<=1000

sejour :
    ids pk
    idc fk client not null -- rappel : fk n'implique pas not null
    idv fk village not null
    jour not null check 1<=jour<=365
    (idc, jour) unique 

creer sequences pour client, village, sejour

Contraintes non SQL : 

1. le nombre de sejours pour un centre pour un jour ne peut pas
depasser sa capacite :

  pour tout idv i de capacite n dans village,
  il y a au plus n lignes avec idv i pour chaque jour j dans sejour

2. l'avoir d'un client plus la somme des prix de ses sejours ne peut
exceder 2000 :

  pour tout idc i dans client : avoir + S <= 2000
  en effet, un client part de 2000 et achete des sejours, donc :
  avoir + somme des prix de ses sejours presents + somme des prix de
  ses sejours detruits = 2000 ;
  donc avoir + somme des prix de ses sejours presents <= 2000 ;
  comment obtient-on S : considerons toutes les lignes d'idc i dans
  sejour, et pour chacune, a partir de sa colonne idv dans sejour, son
  prix dans village identifie par idv ; on note S la somme de tous ces
  prix 
*/
  
-------------------------------------------------------------------------------
/* Rappel : 
Null : 
Peuvent etre "null" les valeurs intuitivement non
indispensable au fonctionnement de l'application. De plus, par
convention dans le module les colonnes utilisees en parametres ou a
l'interieur d'un traitement ne peuvent etre "null", mais il n'est pas
impose que celles en sortie d'un traitement ne le soient pas. 
Rappel : fk et check n'impliquent pas not null. 

Contraintes non SQL :
en general, il s'agit de compter un ensemble de lignes d'une table, ou de
comparer des valeurs dans deux tables, ou des variantes de ces situations
(ex : somme d'un ensemble de lignes). */

-------------------------------------------------------------------------------
-- Ordres SQL et modeles d'ordre : completer avec nouveaux outils TD precedent
-------------------------------------------------------------------------------

-- a/ option avec serial

drop table if exists sejour cascade;
drop table if exists client cascade;
drop table if exists village cascade;

create table client(
    idc serial primary key,
    nom varchar(10) not null, 
    age int not null, 
    constraint check_client_age check (0<=age and age<120),
    avoir int default 2000 not null, 
    constraint check_client_avoir check (0<=avoir and avoir<=2000)
);

create table village(
    idv serial primary key,
    ville varchar(12) not null,
    activite varchar(10),
    prix int not null, 
    constraint check_village_prix check (0<prix and prix<=2000),
    capacite int not null, 
    constraint check_village_capacite check (1<=capacite and capacite<=1000)
);

create table sejour(
    ids serial primary key,
    idc int not null, foreign key (idc) references client,
    idv int not null, foreign key (idv) references village,
    jour int not null, 
    constraint check_sejour_jour check (1<=jour and jour<=365), 
    unique (idc, jour)
);
--    exemples insertions

  insert into village values(DEFAULT, 'NY', 'resto', 50, 200);
  insert into village values(DEFAULT, 'NY', 'MOMA', 60, 300);
  insert into village values(DEFAULT, 'Chatelaillon', 'kitesurf', 100, 20);

  insert into client(idc, nom, age) values(DEFAULT, 'Rita', 22);
  insert into client(idc, nom, age) values(DEFAULT, 'Riton', 23);

  insert into sejour values(DEFAULT, 1, 1, 45);

-- b/ option avec séquence

drop table if exists sejour cascade;
drop table if exists client cascade;
drop table if exists village cascade;

create table client(
    idc int primary key,
    nom varchar(10) not null, 
    age int not null, 
    constraint check_client_age check (0<=age and age<120),
    avoir int default 2000 not null, 
    constraint check_client_avoir check (0<=avoir and avoir<=2000)
);

create table village(
    idv int primary key,
    ville varchar(12) not null,
    activite varchar(10),
    prix int not null, 
    constraint check_village_prix check (0<prix and prix<=2000),
    capacite int not null, 
    constraint check_village_capacite check (1<=capacite and capacite<=1000)
);

create table sejour(
    ids int primary key,
    idc int not null, foreign key (idc) references client,
    idv int not null, foreign key (idv) references village,
    jour int not null, 
    constraint check_sejour_jour check (1<=jour and jour<=365), 
    unique (idc, jour)
);

drop sequence if exists seq_client;
drop sequence if exists seq_village;
drop sequence if exists seq_sejour;

create sequence seq_client start with 1;
create sequence seq_village start with 10;
create sequence seq_sejour start with 100;

--    exemples insertions

  insert into village values(nextval('seq_village'), 'NY', 'resto', 50, 200);
  insert into village values(nextval('seq_village'), 'NY', 'MOMA', 60, 300);
  insert into village values(nextval('seq_village'), 'Chatelaillon', 'kitesurf', 100, 20);

  insert into client(idc, nom, age) values(nextval('seq_client'), 'Rita', 22);
  insert into client(idc, nom, age) values(nextval('seq_client'), 'Riton', 23);

  insert into sejour values(nextval('seq_sejour'), 1, 11, 45);