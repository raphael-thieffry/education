-------------------------------------------------------------------------------
-- corr_pl_bases.sql 
-------------------------------------------------------------------------------
-- traitement 3.
-- on adapte le modele d'ordre a la syntaxe PL/pgSQL :

create or replace function traitement3(
    le_jour sejour.jour%type)
    returns integer
as $$
declare
    le_nombre integer;
begin
  select count(*) into le_nombre
	  from sejour where jour < le_jour;
  delete from sejour
      where jour < le_jour;
  return le_nombre;
end;
$$ language plpgsql;

-- visualiser la base
select * from client;
select * from village;
select * from sejour;
do $$
begin
  raise notice 'Nombre de sejours detruits : %',traitement3(364);
end;
$$;
select * from sejour;
do $$
begin
  raise notice 'Nombre de sejours detruits : %',traitement3(365);
end;
$$;
select * from sejour;

-------------------------------------------------------------------------------
-- traitement 3 par procedure avec variables out : 
-- on adapte la version ci-dessus par fonction :

create or replace procedure traitement3_out(
    le_jour sejour.jour%type,
    le_nombre inout integer)
as $$
begin
  select count(*) into le_nombre
	  from sejour where jour < le_jour;
  delete from sejour
    where jour < le_jour;
end;
$$ language plpgsql;

select * from sejour;

do $$
declare
    n int;
begin
    call traitement3_out(150, n);
    raise notice 'Nombre de sejours detruits : %',n;
end;
$$;

select * from sejour;
do $$
declare
    n int;
begin
    call traitement3_out(365, n);
    raise notice 'Nombre de sejours detruits : %',n;
end;
$$;
select * from sejour;

-------------------------------------------------------------------------------
-- traitement 1 :

--version avec séquence
create or replace function traitement1(
    le_nom client.nom%type,
    l_age client.age%type)
    returns client.idc%type
as $$
declare
    l_idc client.idc%type;
begin
    l_idc := nextval('seq_client');
    insert into client(idc, nom, age) 
        values(l_idc, le_nom, l_age);
    return l_idc;
end;
$$ language plpgsql;

--version avec serial

create or replace function traitement1(
    le_nom client.nom%type,
    l_age client.age%type)
    returns client.idc%type
as $$
declare
    l_idc client.idc%type;
begin
    insert into client(idc, nom, age) 
        values(DEFAULT, le_nom, l_age);
    select idc into l_idc from client
        where nom=le_nom and age=l_age;
    -- ou trouver le nom de la séquence et appeler
    -- currval('client_idc_seq')
    -- l_idc := currval('client_idc_seq');
    return l_idc;
end;
$$ language plpgsql;


select * from client;
do $$
begin
  raise notice 'Nouvel identifiant : %', traitement1('Jeanne', 23);
end;
$$;
select * from client;
do $$
begin
  raise notice 'Nouvel identifiant : %', traitement1('Jules', 23);
end;
$$;
select * from client;

-------------------------------------------------------------------------------
-- vue villages sans sejour
-------------------------------------------------------------------------------

create view villages_sans_sejour as
    select idv, ville, activite, prix 
    from village 
    where idv not in (select idv 
                      from sejour);

select * from villages_sans_sejour;
