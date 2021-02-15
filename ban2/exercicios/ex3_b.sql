create table curso (
	sigla_curso char(10) not null,
	nome varchar(100) not null,
	titulacao varchar(100) not null,
	primary key (sigla_curso)
);

create table disciplina (
	sigla_disc char(10) not null,
	nome varchar(100) not null,
	carga_horaria integer not null,
	primary key (sigla_disc)
);

create table grade (
	sigla_curso varchar(10) not null,
	sigla_disc varchar(10) not null,
	primary key (sigla_curso, sigla_disc),
	foreign key (sigla_curso) references curso,
	foreign key (sigla_disc) references disciplina
);

create table requisito (
	sigla_disc_req char(10) not null,
	sigla_curso_req char(10) not null,
	sigla_disc char(10) not null,
	sigla_curso char(10) not null,
	primary key (sigla_disc_req, sigla_curso_req, sigla_disc, sigla_curso),
	foreign key (sigla_disc, sigla_curso) references grade,
	foreign key (sigla_disc_req, sigla_curso_req) references grade (sigla_disc, sigla_curso)
);

create table inscricao (
  matricula integer not null,
  sigla_curso char(10) not null,
  cpf char(11) not null,
	primary key (matricula)
);

create table matricula (
	ano date not null,
	matricula integer not null,
	sigla_disc char(10) not null,
	semestre integer not null,
	primary key (ano, matricula, sigla_disc, semestre),
	foreign key (matricula) references inscricao,
	foreign key (sigla_disc) references disciplina
);

create table aluno (
	cpf char(11) not null,
	nome varchar(100) not null,
	rua varchar(255) not null,
	numero integer not null,
	estado char(2) not null,
	cidade varchar(100),
	cep integer not null,
	primary key (cpf)
);

create table professor (
	reg_mec integer not null,
	nome varchar(100) not null,
	rua varchar(255) not null,
	numero integer,
	cidade varchar(100) not null,
	estado char(2) not null,
	cep integer not null,
	primary key (reg_mec)

);

create table area (
	cod_area integer not null,
	descricao varchar not null,
	primary key (cod_area)
);

create table responsavel (
	reg_mec integer not null,
	cod_area integer not null,
	ate date not null,
	primary key (reg_mec, cod_area),
	foreign key (reg_mec) references professor,
	foreign key (cod_area) references area
);

create table titulo (
	reg_mec integer not null,
	cod_area integer not null,
	data_da_titulacao date not null,
	primary key (reg_mec, cod_area),
	foreign key (reg_mec) references professor,
	foreign key (cod_area) references area
);

create table leciona (
	sigla_disc char(10) not null,
	reg_mec integer not null,
	ano date not null,
	semestre integer not null,
	primary key (sigla_disc, reg_mec, ano, semestre),
	foreign key (sigla_disc) references disciplina,
	foreign key (reg_mec) references professor
);

create table habilitacao (
	sigla_disc char(10) not null,
	reg_mec integer not null,
	primary key (sigla_disc, reg_mec),
	foreign key (sigla_disc) references disciplina,
	foreign key (reg_mec) references professor
);