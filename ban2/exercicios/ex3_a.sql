create table setor (
	cods serial not null,
	nome varchar(15) not null,
	primary key (cods)
);

create table mecanico (
	codm serial not null,
	cpf bigint not null,
	nome varchar(15) not null, 
	idade smallint not null, 
	endereco varchar(30) , 
	cidade varchar(15) not null, 
	funcao varchar(20) not null, 
	cods serial not null,
	primary key (codm),
	foreign key (cods) references setor(cods)
);

create table veiculo (
	codv serial not null,
	renavam integer not null, 
	modelo varchar(15) not null, 
	marca varchar(15) not null, 
	ano smallint not null, 
	quilometragem integer not null, 
	codc serial not null,
	primary key (codv),
	foreign key (codc) references cliente (codc)
);

create table cliente (
	codc serial not null, 
	cpf bigint not null, 
	nome varchar(15) not null, 
	idade smallint not null, 
	endereco varchar(30) not null, 
	cidade varchar(15) not null,
	primary key (codc)
);

create table conserto (
	codm serial not null, 
	codv serial not null, 
	datac date not null, 
	hora time not null,
	primary key (datac),
	foreign key (codm) references mecanico (codm),
	foreign key (codv) references veiculo (codv)
);