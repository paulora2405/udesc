--1) Gatilho para impedir a inserção ou atualização de Clientes com o mesmo CPF.

--2) Gatilho para impedir a inserção ou atualização de Mecânicos com idade menor que 20 anos.
--onde? mecanico
--quando? before
--quais operações? insert, update
--nivel? row level

create or replace function verificaIdade() returns trigger as
$$
begin
	if new.idade < 20 then
		raise exception 'Mecanico não pode ter idade menor que 20 anos.';
	end if;
	return new;
end;
$$
language plpgsql;

create trigger verificaIdade before insert or update on mecanico for each row execute procedure verificaIdade();

insert into mecanico (codm, cpf, nome, idade) values (12,4343, 'teste1', 18)

--3) Gatilho para atribuir um cods (sequencial) para um novo setor inserido.

--4) Gatilho para impedir a inserção de um mecânico ou cliente com CPF inválido.

--5) Gatilho para impedir que um mecânico seja removido caso não exista outro mecânico com a mesma função.

--6) Gatilho que ao inserir, atualizar ou remover um mecânico, reflita as mesmas modificações na tabela de Cliente. Em caso de atualização, se o mecânico ainda não existir na tabela de Cliente, deve ser inserido.
--onde? mecanico
--quando? after
--quem? insert, update and delete
--nivel? row level
--Criação da sequencia que fará o gerenciamento da PK do cliente
create sequence cliente_codc_seq start 8;

create or replace function atualizaCliente() returns trigger as 
$$
begin
	if TG_OP = 'INSERT' then
		insert into cliente values(nextval('cliete_codc_seq'), new.cpf, new.nome, new,idade, new.endereco, new.cidade);
	
	elseif TP_OP = 'UPDATE' then
		if(select 1 from cliente where cpf = new.cpf) then
			update cliente set nome=new.nome, idade = new.idade, endereco = new.endereco, cidade=new.cidade
			where cpf = new.cpf;
		else
			insert into cliente values(nextval('cliete_codc_seq'), new.cpf, new.nome, new,idade, new.endereco, new.cidade);
		end if;
	elseif TG_OP = 'DELETE' then
		delete from cliente where cpf = old.cpf;
	end if;
	return null;
end;
$$
language plpgsql;

create trigger atualizaCliente after insert or update or delete on mecanico
	for each row execute procedure atualizaCliente();

--7) Gatilho para impedir que um conserto seja inserido na tabela Conserto se o mecânico já realizou mais de 20 horas extras no mês.
--onde? conserto
--quando? before
--quem? insert or update
--nivel? each row (row level)
create or replace function calculaHorasExtras(p_codm int, p_mes int, p_ano int) returns int as
$$
declare
 	v_horas_trab int default 0;
begin
	select count(codm) from conserto where codm = p_codm 
	and date_part('month', data) = p_mes 
	and date_part('year', data) = p_ano into v_horas_trab;
	if v_horas_trab > 160 then
		return v_horas_trab -160;
	else
		return 0;
	end if;
end;
$$
language plpgsql;


create or replace function verificaHorasExtras() returns trigger as
$$
declare
	v_mes int;
	v_ano int;
begin
	v_mes := date_part('month', new.data);
	v_ano := date_part('year', new.data);
	if calculaHorasExtras(codm, mes, ano) > 20 then
		raise exception 'O funcionário excedeu a quantidade de horas extras do mês';
	end if;
	return new;
end;
$$
language plpgsql;

create trigger verificaHorasExtras before insert or update on conserto
	for each row execute procedure verificaHorasExtras();

--8) Gatilho para impedir que mais de 1 conserto seja agendado no mesmo setor na mesma hora. 
