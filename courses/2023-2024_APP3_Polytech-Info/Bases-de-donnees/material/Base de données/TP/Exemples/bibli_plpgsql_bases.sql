---------------------------
--- exemples PL/pgSQL
--------------------------

 create table personne(
    nom varchar(10),
    age int,
    activite varchar(15)
 );

 insert into personne values('Riton', 22, 'informatique');
 insert into personne values('Rita', 21, 'danse');
 insert into personne values('Jeanne', 23, 'lecture');
 insert into personne values('Lulu', 23, 'randonnée');
 insert into personne values('Pierre', 50, 'musique');

 select * from personne;

 -- anniversaire: augumenter age par 1, toute personne ayant le meme age -> meme activité

create or replace procedure anniversaire(le_nom personne.nom%type)
as $$
declare
    l_age personne.age%type;
    l_activite personne.activite%type;
begin
    update personne 
        set age = age+1 where nom = le_nom;
    select age, activite
        into l_age, l_activite from personne where nom=le_nom;
    update personne
        set activite = l_activite where age = l_age;
end;
$$ language plpgsql;

call anniversaire('Rita');
select * from personne;

-- fonction: age d'une personne a partir d'un nom

create or replace function age(le_nom personne.nom%type)
    returns personne.age%type
as $$
declare
    l_age personne.age%type;
begin
    select age into l_age
        from personne where nom = le_nom;
    return l_age;
end;
$$ language plpgsql;

do $$
begin
    raise notice 'Rita a % ans',age('Rita');
end;
$$;

select * from personne;

-- exemple bloc anonyme
do $$
declare
    x varchar(10);
begin
    x := 'Hello!';
    raise notice '%',x;
end;
$$;

--exemple procedure parametre OUT

create or replace procedure incremente(n integer, resultat inout integer)
as $$
begin
    resultat := n + 1;
end;
$$ language plpgsql;

do $$
declare
    k integer;
begin
    call incremente(4, k);
    raise notice 'le succeseur de 4 est %',k;
end;
$$;

-- procedure: age d'une personne a partir d'un nom

create or replace procedure age_out(le_nom personne.nom%type, l_age inout personne.age%type)
as $$
begin
    select age into l_age
        from personne where nom = le_nom;
end;
$$ language plpgsql;

do $$
declare
    a personne.age%type;
begin
    call age_out('Rita', a);
    raise notice 'Rita a % ans',a;
end;
$$;

-- fonction sans parametre

create or replace function age_max()
    returns personne.age%type
as $$
declare
    l_age personne.age%type;
begin
    select max(age) into l_age
        from personne;
    return l_age;
end;
$$ language plpgsql;

do $$
begin
    raise notice '%',age_max();
end;
$$;

select * from personne;

-- drop procedure/function

drop procedure anniversaire;
drop function age;

---------------------------
--- vues
--------------------------

create view vue_age_25 as
    select * from personne where age<=25;

select * from vue_age_25;

update personne set age=26 where nom = 'Lulu';

select * from vue_age_25;