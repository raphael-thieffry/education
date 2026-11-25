---------------------------
--- exemples contraintes
--------------------------

drop table t;

create table t(
    a integer constraint pk_t primary key,
    b integer not null,
    c integer,
    constraint unique_t unique (b,c),
    --unique (b,c),
    constraint check_t check (a+b>4)
    --check (a+b>4)
);

insert into t values(1,2,9);
insert into t values(1,4,9);
insert into t values(1,7,9);
insert into t values(2,4,9);
select * from t;

drop table s;

create table s(
    a integer,
    b integer,
    foreign key (a) references t
    --foreign key (a) references t(a)
);

insert into s values(3,4);
insert into s values(1,4);

drop sequence td;
create sequence td;
insert into t values(nextval('td'),9,1);
insert into s values(currval('td'),99);

----------------------------------
--- contraintes SQL bibliotheque 
----------------------------------

drop table livre;
drop table exemplaire;
drop table client;
drop table nbEmpruntsPlusResas;
drop table emprunt;
drop table reservation;

create table livre(
    idl serial primary key,
    titre varchar(24) not null,
    auteur varchar(13) not null,
    unique (titre,auteur)
);

create table exemplaire(
    ide serial primary key,
    idl integer, foreign key (idl) references livre,
    etat varchar(5),
    constraint check_etat check (etat='neuf' or etat='bon' or etat='vieux')
);

create table client(
    idc serial primary key,
    nom varchar(10) not null
);

create table nbEmpruntsPlusResas(
    nbmax integer not null,
    constraint check_nbmax check (0<=nbmax and nbmax<=20)
);

create table emprunt(
    ide integer unique, foreign key (ide) references exemplaire,
    idc integer, foreign key (idc) references client
);

create table reservation(
    idl integer, foreign key (idl) references livre,
    idc integer, foreign key (idc) references client,
    jour integer not null,
    constraint check_jour check (1<=jour and jour<=365),
    unique (idl,idc)
);