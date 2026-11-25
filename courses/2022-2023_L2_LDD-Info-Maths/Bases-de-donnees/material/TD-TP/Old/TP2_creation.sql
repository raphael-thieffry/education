drop table IF EXISTS participe;
drop table IF EXISTS evenement;
drop table IF EXISTS terrain;
drop table IF EXISTS lieu;
drop table IF EXISTS sport;
drop table IF EXISTS client;

create table client(id integer not null,
nom varchar(20),
prenom varchar(10),
sexe char, check (sexe = 'M' or sexe = 'F'),
ddn date,
pcode varchar(5),
score integer, check (score >= 0 and score <= 10),
primary key (id));

create table sport(id integer not null,
nom varchar(20),
nbmin integer,
nbmax integer,
primary key (id));

create table lieu(id integer not null,
intitule varchar(20),
pcode varchar(5),
capacite integer,
sport integer not null,
primary key (id),
CONSTRAINT fk_lieuSport FOREIGN KEY (sport)
REFERENCES sport(id));

create table evenement(id integer not null,
niveau varchar(20), check (niveau = 'debutant' or niveau = 'confirme' or niveau = 'professionnel'),
dat date,
organisateur integer not null,
lieu integer not null,
primary key (id),
CONSTRAINT fk_evLieu FOREIGN KEY (lieu)
REFERENCES lieu(id),
CONSTRAINT fk_evClient FOREIGN KEY (organisateur)
REFERENCES client(id));

create table terrain(id integer not null,
lieu integer not null,
surface integer,
type varchar(10), check (type = 'interieur' or type = 'exterieur'), 
primary key (id, lieu),
CONSTRAINT fk_terLieu FOREIGN KEY (lieu)
REFERENCES lieu(id));

create table participe(client integer not null,
evenement integer not null,
primary key (client, evenement),
CONSTRAINT fk_partClient FOREIGN KEY (client)
REFERENCES client(id),
CONSTRAINT fk_partEven FOREIGN KEY (evenement)
REFERENCES evenement(id));

INSERT INTO client values(1, 'BIDOIT', 'Nicole', 'F', '1980-01-04', 75014, 8);
INSERT INTO client values(2, 'TZOMPANAKI', 'Katerina', 'F', '1984-04-10', 92340, 7);
INSERT INTO client values(3, 'DECELLE', 'Aurelien', 'M', '1983-08-07', 75014, 4);
INSERT INTO client values(4, 'BENSEDDIQ', 'Hajer', 'F', '1993-05-10', 75013, 5);
INSERT INTO client values(5, 'BISHOP', 'Florian', 'M', '1995-12-04', 75013, 6);
INSERT INTO client values(6, 'JUPITER', 'Andrien', 'M', '1998-11-09', 75003, 2);
INSERT INTO client values(7, 'LAURENCIN', 'Naomi', 'F', '1990-05-12', 75010, 8);
INSERT INTO client values(8, 'NABILI', 'Samia', 'F', '1996-04-10', 92340, 7);
INSERT INTO client values(9, 'SEYE', 'Adiouma', 'M', '1988-01-04', 75014, 3);
INSERT INTO client values(10, 'LACOMBLEZ', 'Robin', 'M', '1995-10-10', 75009, 6);
INSERT INTO client values(11, 'FRANIATTE', 'Isaline', 'F', '1993-09-04', 75014, 6);
INSERT INTO client values(12, 'KICHENARADJOU', 'Siva', 'M', '1989-03-12', 92340, 1);
INSERT INTO client values(13, 'DOE', 'John', 'M', '1979-01-15', 69007, 5);

INSERT INTO sport values(1, 'tennis', 2, 4);
INSERT INTO sport values(2, 'football', 4, 10);
INSERT INTO sport values(3, 'volleyball', 2, 6);
INSERT INTO sport values(4, 'running', 2, 100);
INSERT INTO sport values(5, 'basketball', 2, 10);

INSERT INTO lieu values(1, 'lieu1',92340,100,1);
INSERT INTO lieu values(2, 'lieu2',92340,30,2);
INSERT INTO lieu values(3, 'lieu3', 75014,24,2);
INSERT INTO lieu values(4, 'lieu4', 75013,53,5);
INSERT INTO lieu values(5, 'lieu5', 75009,33,4);
INSERT INTO lieu values(6, 'lieu6', 75010,40,3);
INSERT INTO lieu values(7, 'lieu7', 75012,12,1);



INSERT INTO evenement values(1, 'debutant', '2015-01-04', 1, 1);
INSERT INTO evenement values(2, 'professionnel', '2015-11-04', 2, 1);
INSERT INTO evenement values(3, 'confirme', '2015-01-03', 1, 2);
INSERT INTO evenement values(4, 'professionnel', '2013-01-04', 3, 2);
INSERT INTO evenement values(5, 'debutant', '2015-01-03', 11, 7);
INSERT INTO evenement values(6, 'debutant', '2015-01-12', 10, 6);
INSERT INTO evenement values(7, 'professionnel', '2015-01-12', 2, 1);
INSERT INTO evenement values(8, 'confirme', '2014-10-12', 8, 5);

INSERT INTO terrain values(1,1,30, 'interieur');
INSERT INTO terrain values(2,1,23, 'exterieur');
INSERT INTO terrain values(3,1,10, 'interieur');
INSERT INTO terrain values(1,2,11, 'interieur');
INSERT INTO terrain values(2,2,20, 'interieur');
INSERT INTO terrain values(3,2,20, 'exterieur');
INSERT INTO terrain values(1,3,10, 'exterieur');
INSERT INTO terrain values(2,3,10, 'exterieur');
INSERT INTO terrain values(1,4,50, 'interieur');
INSERT INTO terrain values(1,5,30, 'interieur');
INSERT INTO terrain values(2,5,20, 'interieur');
INSERT INTO terrain values(1, 7,5, 'exterieur');
INSERT INTO terrain values(2, 7, 7, 'exterieur');

INSERT INTO participe values(1,1);
INSERT INTO participe values(2,1);
INSERT INTO participe values(4,1);
INSERT INTO participe values(12,1);
INSERT INTO participe values(8,2);
INSERT INTO participe values(2,2);
INSERT INTO participe values(3,2);
INSERT INTO participe values(2,3);
INSERT INTO participe values(11,3);
INSERT INTO participe values(6,3);
INSERT INTO participe values(5,4);
INSERT INTO participe values(6,4);
INSERT INTO participe values(7,4);
INSERT INTO participe values(1,5);
INSERT INTO participe values(7,5);
INSERT INTO participe values(12,6);
INSERT INTO participe values(10,6);
INSERT INTO participe values(11, 7);
INSERT INTO participe values(3, 7);
INSERT INTO participe values(1,8);
INSERT INTO participe values(2,8);
INSERT INTO participe values(3,8);
INSERT INTO participe values(4,8);
INSERT INTO participe values(5,8);
INSERT INTO participe values(6,8);
INSERT INTO participe values(7,8);
INSERT INTO participe values(8,8);
INSERT INTO participe values(9,8);
INSERT INTO participe values(10,8);
INSERT INTO participe values(11,8);
INSERT INTO participe values(12,8);





