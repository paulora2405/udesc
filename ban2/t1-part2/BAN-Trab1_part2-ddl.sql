-- Table: endereco
-- DROP TABLE endereco;
CREATE TABLE endereco
(
	id_endereco integer not NULL,
	rua character varying(50),
	num character varying(50),
	cidade character varying(50),
	cep character varying(50),
	telefone character varying(50),
	constraint endereco_pkey primary key (id_endereco)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE endereco OWNER TO postgres;


-- Table: musico
-- DROP TABLE musico;
CREATE TABLE musico
(
	num_registro integer not NULL,
	nome character varying(50),
	id_endereco integer not NULL,
	constraint musico_pkey primary key (num_registro),
	constraint musico_id_endereco_fkey foreign key (id_endereco)
	references endereco (id_endereco) match simple
	on update cascade on delete set NULL
)
WITH (
  OIDS=FALSE
);
ALTER TABLE musico OWNER TO postgres;


-- Table: instrumento
-- DROP TABLE instrumento;
CREATE TABLE instrumento
(
	cod_instrumento integer not NULL,
	nome character varying(50),
	constraint instrumento_pkey primary key (cod_instrumento)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE instrumento OWNER TO postgres;


-- Table: musico_instrumento
-- DROP TABLE musico_instrumento;
CREATE TABLE musico_instrumento
(
	num_registro integer not NULL,
	cod_instrumento integer not NULL,
	constraint musico_instrumento_pkey primary key (num_registro, cod_instrumento),
	constraint musico_instrumento_num_registro_fkey foreign key (num_registro)
		references musico (num_registro) match simple
		on update cascade on delete set NULL,
	constraint musico_instrumento_cod_instrumento_fkey foreign key (cod_instrumento)
		references instrumento (cod_instrumento) match simple
		on update cascade on delete set NULL
)
WITH (
  OIDS=FALSE
);
ALTER TABLE musico_instrumento OWNER TO postgres;


-- Table: banda
-- DROP TABLE banda;
CREATE TABLE banda
(
	id_banda integer not NULL,
	nome character varying(50),
	constraint banda_pkey primary key (id_banda)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE banda OWNER TO postgres;


-- Table: musico_banda
-- DROP TABLE musico_banda;
CREATE TABLE musico_banda
(
	num_registro integer not NULL,
	id_banda integer not NULL,
	constraint musico_banda_pkey primary key (num_registro, id_banda),
	constraint musico_banda_num_registro_fkey foreign key (num_registro)
		references musico (num_registro) match simple
		on update cascade on delete set NULL,
	constraint musico_banda_id_banda_fkey foreign key (id_banda)
		references banda (id_banda) match simple
		on update cascade on delete set NULL
)
WITH (
  OIDS=FALSE
);
ALTER TABLE musico_banda OWNER TO postgres;


-- Table: produtor
-- DROP TABLE produtor;
CREATE TABLE produtor
(
	id_produtor integer not NULL,
	nome character varying(50),
	constraint produtor_pkey primary key (id_produtor)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE produtor OWNER TO postgres;


-- Table: disco
-- DROP TABLE disco;
CREATE TABLE disco
(
	id_disco integer not NULL,
	titulo character varying(50),
	formato character varying(50),
	data date,
	id_produtor integer not NULL,
	num_registro integer,
	id_banda integer,
	constraint disco_pkey primary key (id_disco),
	constraint disco_id_produtor_fkey foreign key (id_produtor)
		references produtor (id_produtor) match simple
		on update cascade on delete set NULL,
	constraint disco_id_banda_fkey foreign key (id_banda)
		references banda (id_banda) match simple
		on update cascade on delete set NULL,
	constraint disco_num_registro_fkey foreign key (num_registro)
		references musico (num_registro) match simple
		on update cascade on delete set NULL
)
WITH (
  OIDS=FALSE
);
ALTER TABLE disco OWNER TO postgres;


-- Table: musica
-- DROP TABLE musica;
CREATE TABLE musica
(
	id_musica integer not NULL,
	nome character varying(50),
	formato character varying(50),
	num_registro integer,
	id_banda integer,
	constraint musica_pkey primary key (id_musica),
	constraint musica_id_banda_fkey foreign key (id_banda)
		references banda (id_banda) match simple
		on update cascade on delete set NULL,
	constraint musica_num_registro_fkey foreign key (num_registro)
		references musico (num_registro) match simple
		on update cascade on delete set NULL
)
WITH (
  OIDS=FALSE
);
ALTER TABLE musica OWNER TO postgres;


-- Table: musica_disco
-- DROP TABLE musica_disco;
CREATE TABLE musica_disco
(
	id_musica integer not NULL,
	id_disco integer not NULL,
	constraint musica_disco_pkey primary key (id_musica, id_disco),
	constraint musica_disco_id_disco_fkey foreign key (id_disco)
		references disco (id_disco) match simple
		on update cascade on delete set NULL,
	constraint musica_disco_id_musica_fkey foreign key (id_musica)
		references musica (id_musica) match simple
		on update cascade on delete set NULL
)
WITH (
  OIDS=FALSE
);
ALTER TABLE musica_disco OWNER TO postgres;
