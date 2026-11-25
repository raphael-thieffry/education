-------------------------------------------------------------------------------
-- corr_pl_curseurs.sql 
-------------------------------------------------------------------------------
-- authentification :

create or replace procedure authentification(
    l_idc client.idc%type,
    le_nom client.nom%type)
as $$
declare
    c cursor for
        select * from client
	     where idc = l_idc and nom = le_nom;
    le_client record;
    message varchar(50);
begin
    open c;
    fetch c into le_client;
    if found then
        message := 'bienvenue '||le_client.nom||', '||le_client.age
	           ||' ans, avoir '||le_client.avoir;
    else
        message := 'desole, erreur identifiant/nom';
    end if;
    close c;
    raise notice '%',message;
end;
$$ language plpgsql;

select * from client;
call authentification(2, 'Rita');
call authentification(1, 'Rita');

-------------------------------------------------------------------------------
-- consulter informations client :

-- forme curseurs generale :

create or replace procedure consulter_sejours1(
    l_idc client.idc%type)
as $$
declare
    c cursor for
        select ids, idv, jour from sejour
         where sejour.idc = l_idc;
    l_ids sejour.ids%type;
    l_idv sejour.idv%type;
    le_jour sejour.jour%type;
begin
    open c;
    loop 
        fetch c into l_ids, l_idv, le_jour;
        exit when not found;
        raise notice 'sejour %, %, %',l_ids,l_idv,le_jour;
    end loop;
    close c;
    raise notice 'fin';
end;
$$ language plpgsql;

select * from sejour;
select * from village;
call consulter_sejours1(1);
call consulter_sejours1(5);

-- forme curseur for :

create or replace procedure consulter_sejours2(
    l_idc client.idc%type)
as $$
declare
    x record;
begin
    for x in 
        select ids, idv, jour
            from sejour
            where sejour.idc = l_idc
    loop
        raise notice 'sejour %, %, %',x.ids,x.idv,x.jour;
    end loop;
    raise notice 'fin';

end;
$$ language plpgsql;

select * from sejour;
select * from village;
call consulter_sejours2(1);
call consulter_sejours2(5);

-- forme curseur avec variable record curseur (rowtype sejour pas adapte) :

create or replace procedure consulter_sejours3(
    l_idc client.idc%type)
as $$
declare
    c cursor for
        select ids, idv, jour from sejour
         where sejour.idc = l_idc;
    le_sejour record;
begin
    open c;
    fetch c into le_sejour;
    while found loop
        raise notice 'sejour %, %, %',le_sejour.ids,le_sejour.idv,le_sejour.jour;
        fetch c into le_sejour;
    end loop;
    close c;
     raise notice 'fin';
end;
$$ language plpgsql;

select * from sejour;
select * from village;
call consulter_sejours3(1);
call consulter_sejours3(5);

-- rem : consulter_informations avec for-x-in ; autres formes ci-dessus

create or replace procedure consulter_informations(
    l_idc client.idc%type)
as $$
declare
    x record;
begin
    for x in select ids, idv, jour
        from sejour where sejour.idc = l_idc
    loop
        raise notice 'sejour %, %, %',x.ids,x.idv,x.jour;
    end loop;
    raise notice 'fin sejours';
    for x in select distinct village.idv, ville, activite, prix, capacite
        from village, sejour where sejour.idc = l_idc and village.idv = sejour.idv
    loop
        raise notice 'village % à %, %, % eur, % lits',x.idv,x.ville,x.activite,x.prix,x.capacite;
    end loop;
    raise notice 'fin villages';
end;
$$ language plpgsql;

select * from sejour;
select * from village;
call consulter_informations(1);
call consulter_informations(5);

-------------------------------------------------------------------------------
-- traitement 2 :

create or replace procedure traitement2(
    l_idc client.idc%type,
    la_ville village.ville%type,
    le_jour sejour.jour%type,
    l_idv inout village.idv%type,
    l_ids inout sejour.ids%type,
    l_activite inout village.activite%type)   
as $$
declare
    c cursor for select idv, prix, activite from village 
        where ville = la_ville order by prix desc;
    le_prix village.prix%type;
begin
    open c;
    fetch c into l_idv, le_prix, l_activite;
    if found then
        l_ids := nextval('sejour_ids_seq');
        insert into sejour 
            values(l_ids, l_idc, l_idv, le_jour);
        update client 
            set avoir = avoir - le_prix
            where idc = l_idc;
    else
        l_idv := -1;
	    l_ids := -1;
	    l_activite := 'neant';
    end if;
    close c;
end;
$$ language plpgsql;

select * from client;
select * from village;
select * from sejour;

do $$
declare
    iv village.idv%type;
    l_ids sejour.ids%type;
    a village.activite%type;
begin
    call traitement2(1, 'Chatelaillon', 361, iv, l_ids, a);
    raise notice 'idv %, ids %, activite %',iv,l_ids,a;
    call traitement2(1, 'Chatelaillon', 360, iv, l_ids, a);
    raise notice 'idv %, ids %, activite %',iv,l_ids,a;
end;
$$;

select * from sejour;

-------------------------------------------------------------------------------
