Popular base de dados:
INSERT INTO empregado (num_matricula, num_membro_sindicato)
VALUES (1,1),(2,2),(3,3)

insert into tecnico (num_matricula,endereco,telefone,salario)
values (1,'azul',78976087,2000), (2,'verde',78976047,2500)

insert into modelo (codigo,capacidade,peso)
values (1,100,30000),(2, 38, 8000 )

insert into aviao (num_reg, modelo)
values (1,1),(2,1),(3,2)

insert into teste (num_teste,nome,ptc_max)
values(1,'teste1',95),(2,'teste2',95),(3,'teste3',95),(4,'teste4',95),(5,'teste5',95),(6,'teste6',95)

insert into info_teste (num_teste, num_reg, num_matricula, data, num_horas, pontuacao)
values (1,1,1,'12-09-2020',5,95),(2,1,1,'12-09-2020',5,95),(3,1,1,'12-09-2020',5,95),(4,1,1,'12-09-2020',5,95),(5,1,1,'12-09-2020',5,95)


--1) Gatilho para impedir que um teste seja inserido na tabela info_teste se o tecnico já realizou mais de 5 testes no dia.
--função
 create or replace function contaTestesNoDia(t_num_matricula int, t_dia int, t_mes int, t_ano int) returns int as
 $$
 declare
 	t_testes int default 0;
begin
	select count(num_matricula) from Info_teste where num_matricula = t_num_matricula 
    and date_part('day', data) = t_dia	
    and date_part('month', data) = t_mes 
	and date_part('year', data) = t_ano into t_testes;
	return t_testes;
end;
$$
language plpgsql;

--trigger
create or replace function contaTestesNoDia() returns trigger as
$$
declare
    v_dia int;
	v_mes int;
	v_ano int;
begin
    v_dia := date_part('day', new.data);
	v_mes := date_part('month', new.data);
	v_ano := date_part('year', new.data);
	if contaTestesNoDia(new.num_matricula, v_dia, v_mes, v_ano) > 4 then
		raise exception 'O funcionário excedeu a quantidade de testes no dia';
	end if;
	return new;
end;
$$
language plpgsql;

create trigger contaTestesNoDia before insert or update on info_teste
	for each row execute procedure contaTestesNoDia();
	
insert into info_teste (num_teste, num_reg, num_matricula, data, num_horas, pontuacao)

--teste
--values (6,1,1,'12-09-2020',5,95)

--2) Gatilho para impedir a inserção ou atualização de Empregados com o mesmo num_membro_sindicato.

create or replace function verificaNumeroMembro() returns trigger as
$$
begin
	if (select count(num_membro_sindicato) from Empregado where num_membro_sindicato = new.num_membro_sindicato) > 0 then
		raise exception 'Um funcionario já possui esse numero de membro';
	end if;
	return new;
end;
$$
language plpgsql;

create trigger verificaNumeroMembro before insert or update on Empregado for each row execute procedure verificaNumeroMembro();

--teste
-- INSERT INTO empregado (num_matricula, num_membro_sindicato) VALUES (4,1)


--3) Gatilho para impedir a inserção ou atualização da capacidade de um modelo para menos de 1 passageiro

create or replace function verificaCapacidadeModelo() returns trigger as
$$
begin
	if new.capacidade < 1 then
		raise exception 'O modelo deve ter capacidade para no minimo um passageiro';
	end if;
	return new;
end;
$$
language plpgsql;

create trigger verificaCapacidadeModelo before insert or update on modelo for each row execute procedure verificaCapacidadeModelo();

--teste
--INSERT INTO modelo (codigo, capacidade, peso) VALUES (3,0, 1000)
					

--4) Gatilho para impedir que um teste obtenha pontuação maior que 100 ou menor que 0;

create or replace function verificaPontuacao() returns trigger as
$$
begin
	if (new.pontuacao < 0 or new.pontuacao > 100) then
		raise exception 'A pontuação deve ser um valor entre 0 e 100';
	end if;
	return new;
end;
$$
language plpgsql;

create trigger verificaPontuacao before insert or update on info_teste for each row execute procedure verificaPontuacao();

--teste
--insert into info_teste (num_teste, num_reg, num_matricula, data, num_horas, pontuacao) values (7,1,2,'12-09-2020',5,101)

