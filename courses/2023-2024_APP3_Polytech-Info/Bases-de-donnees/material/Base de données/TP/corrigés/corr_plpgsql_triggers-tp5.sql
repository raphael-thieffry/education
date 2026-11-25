-------------------------------------------------------------------------------
-- corr_pl_triggers.sql
-- utilise les autres corrigés
-------------------------------------------------------------------------------
-- trigger archivage niveau ligne : 
-- pour simplifier on ignore les contraintes sur la table d'archivage

drop table archive_sejour; 
create table archive_sejour(
    ids int, 
    idc int, 
    idv int,
    jour int,
    avoir int
);

create or replace function fcn_traitement4()
returns trigger
as $$
declare
    a client.avoir%type;
begin
    select avoir into a
        from client where idc = OLD.idc;
    insert into archive_sejour
        values(OLD.ids, OLD.idc, OLD.idv, OLD.jour, a);
    raise notice 'archivage de (%, %, %, %, %)',
        OLD.IDS, OLD.IDC, OLD.IDV, OLD.JOUR, a;
    return OLD;
end;
$$ language plpgsql;

drop trigger if exists traitement4 on sejour;
create trigger traitement4
    before delete on sejour
    for each row
execute function fcn_traitement4();

-- direct
delete from archive_sejour; 
insert into sejour values(100, 2, 1, 45);
insert into sejour values(101, 3, 2, 365);
select * from archive_sejour;
select * from sejour;
select * from client;

delete from sejour where jour < 365;
select * from archive_sejour;
select * from sejour;

-- en utilisant une procedure
delete from archive_sejour; 
insert into sejour values(100, 2, 1, 45);
insert into sejour values(101, 3, 2, 365);
select * from archive_sejour;
select * from sejour;
do
$$
begin
    raise notice '%',traitement3(365);
end;
$$;

select * from archive_sejour;
select * from sejour;

-- 0 lignes
delete from sejour where jour <= 1;

-- HERE
-------------------------------------------------------------------------------
-- trigger niveau table :
-- Rappel : on ne gere que le cas de la mise a jour : insertion sejour

create or replace function fnc_depenses_table()
    returns trigger
as $$
declare
    c cursor for
    select client.idc, nom, avoir, sum(prix) as depenses
            from client, sejour, village
            where client.idc = sejour.idc
              and sejour.idv = village.idv
            group by client.idc, nom, avoir
              having avoir + sum(prix) > 2000;
    le_client record;
begin
    open c;
    raise notice 'trigger';
    fetch c into le_client;
    if found then
        raise exception 'violation contrainte depenses (avoir %, depenses %)',
            le_client.avoir, le_client.depenses;
    end if;
    return null; -- car trigger after
end;
$$ language plpgsql;

drop trigger if exists contrainte_depenses_ligne on sejour;

create trigger contrainte_depenses_table
    after insert on sejour
    execute function fnc_depenses_table();

select * from client;
select * from village;
select * from sejour;
delete from sejour;
insert into sejour values(110, 1, 2, 364);
insert into sejour values(111, 1, 2, 363);
insert into sejour values(112, 1, 2, 362);
insert into sejour values(113, 1, 2, 361);

-------------------------------------------------------------------------------
