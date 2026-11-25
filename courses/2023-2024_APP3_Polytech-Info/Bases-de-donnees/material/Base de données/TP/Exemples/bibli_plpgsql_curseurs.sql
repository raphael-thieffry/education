--------------------------------------
--- exemples PL/pgSQL (curseurs)
--- à partir du bibli_pgsql_bases.sql
--------------------------------------


-- version avec LOOP / FETCH / EXIT
create or replace procedure affiche1(age_max personne.age%type)
as $$
declare
    c cursor for 
        select nom, age from personne
        where age <= age_max;
    le_nom personne.nom%type;
    l_age personne.age%type;
begin
    open c;
    loop
        fetch c into le_nom, l_age;
        exit when not found;
        raise notice '% a % ans',le_nom,l_age;
    end loop;
    close c;
    raise notice 'fin';
end;
$$ language plpgsql;

call affiche1(30);
select * from personne;
call affiche1(20);
call affiche1(19);

-- version avec FOR

create or replace procedure affiche2(age_max personne.age%type)
as $$
declare
    c cursor for 
        select nom, age from personne
        where age <= age_max;
    la_personne record;
begin
    for la_personne in c
    loop
        raise notice '% a % ans',la_personne.nom,la_personne.age;
    end loop;
    raise notice 'fin';
end;
$$ language plpgsql;

call affiche2(30);
select * from personne;
call affiche2(20);
call affiche2(19);

-- exemple avec ROWTYPE

create or replace procedure affiche3(age_max personne.age%type)
as $$
declare
    c cursor for 
        select nom, age from personne
        where age <= age_max;
    la_personne personne%rowtype;    
begin
    open c;
    loop
        fetch c into la_personne;
        exit when not found;
        raise notice '% a % ans',la_personne.nom,la_personne.age;
    end loop;
    close c;
    raise notice 'fin';
end;
$$ language plpgsql;

call affiche3(30);
select * from personne;
call affiche3(20);
call affiche3(19);

-- for implicite

create or replace procedure affiche4(age_max personne.age%type)
as $$
declare
    la_personne record;
begin
    for la_personne in select nom, age from personne where age <= age_max
    loop
        raise notice '% a % ans',la_personne.nom,la_personne.age;
    end loop;
    raise notice 'fin';
end;
$$ language plpgsql;

call affiche4(30);
select * from personne;
call affiche4(20);
call affiche4(19);

-- forcer un seul résultat

create or replace procedure affiche5(age_max personne.age%type)
as $$
declare
    c cursor for 
        select nom, age from personne
        where age <= age_max order by nom;
    le_nom personne.nom%type;
    l_age personne.age%type;
begin
    open c;
    fetch c into le_nom, l_age;
    if found then
        raise notice '% a % ans',le_nom,l_age;
    else
        raise notice 'aucune personne';
    end if;
    close c;
    raise notice 'fin';
end;
$$ language plpgsql;

call affiche5(30);
select * from personne;
call affiche5(20);
call affiche5(19);