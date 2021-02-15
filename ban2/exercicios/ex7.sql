--1)Função para inserção de um mecânico.
create or replace function funcao_1(codm int) RETURNS void as
$$
begin
	insert into mecanico values (codm);
	return;
end;
$$ language plpgsql

--2)Função para exclusão de um mecânico. 
create or replace function funcao_2(_codm int) RETURNS void as
$$
begin
	delete from mecanico where codm = _codm;
	return;
end;
$$ language plpgsql

--3)Função única para inserção, atualizar e exclusão de um cliente.
create or replace function 
funcao_3(op text, _codc int, _cpf text, _nome text, _idade int, _endereco text, _cidade text) 
RETURNS void as
$$
begin
	if op = 'insert' then
		insert into cliente values (_codc, _cpf, _nome, _idade, _endereco, _cidade);
	elsif op = 'update' then
		update cliente set codc=_codc, cpf=_cpf, nome=_nome, idade=_idade, endereco=_endereco, cidade=_cidade
		where codc = _codc;
	else
		delete from cliente where codc = _codc;
	end if;
	return;
end;
$$ language plpgsql

--4)Função que limite o cadastro de 
--  no máximo 10 setores na oficina mecânica.
create or replace function 
funcao_4(_cods int, _nome varchar(50))
returns void as
$$
declare
	vlinhas int default 0;
begin
	if(select count(cods) from setor) < 10 then
		insert into setor values (_cods, _nome);
		get diagnostics vlinhas = row_count;
	else
		raise exception 'Nao foi possivel incluis o setor, pois o numero maximo foi atingido';
	end if;
end;
$$
language plpgsql

--5)Função que limita o cadastro de um conserto 
--  apenas se o mecânico não tiver mais de 3 consertos 
--  agendados para o mesmo dia.
create or replace function 
funcao_5(_codm int, _codv int, _data date, _hora time)
returns void as
$$
declare
	qnt int;
begin
	qnt = (select count(*) from conserto where codm = _codm and data = _data);
	
	if qnt < 4 then
		insert into conserto values (_codm, _codv, _data, _hora);
	end if;
end;
$$
language plpgsql

--6)Função para calcular a média geral de idade dos Mecânicos e Clientes.
create or replace function 
funcao_6()
RETURNS int as
$$
declare
	soma int default 0;
	qnt int default 0;
begin
	soma = (select sum(idade) from mecanico) + (select sum(idade) from cliente);
	
	qnt = (select count(*) from mecanico where idade is not null) + (select count(*) from cliente where idade is not null);
	
	return soma / qnt;
end;
$$ language plpgsql

--7)Função única que permita fazer a exclusão de 
--  um Setor, Mecânico, Cliente ou Veículo.
create or replace function 
funcao_7(op text, _id int) 
RETURNS void as
$$
begin
	if op = 's' then
		delete from setor where cods = _id;
	elsif op = 'm' then
		delete from mecanico where codm = _id;
	elsif op = 'c' then
		delete from cliente where codc = _id;
	elseif op = 'v' then
		delete from veiculo where codv = _id;
	else
		raise notice 'Codigo nao existente.';
	end if;
	return;
end;
$$ language plpgsql

--8)Considerando que na tabela Cliente apenas codc é a chave primária, 
--  faça uma função que remova clientes com CPF repetido, 
--  deixando apenas um cadastro para cada CPF. 
--  Escolha o critério que preferir para definir qual cadastro será mantido: 
--  aquele com a menor idade, que possuir mais consertos agendados, etc. 
--  Para testar a função, não se esqueça de inserir na tabela 
--  alguns clientes com este problema.
create or replace function 
funcao_8(_cpf text)
RETURNS void as
$$
declare
	codc_min int;
begin
	codc_min = (select codc from cliente where cpf = _cpf and idade = (select min(idade) from cliente where cpf = _cpf));
	
	delete from cliente where codc != codc_min and cpf = _cpf;
	
	return;
end;
$$ language plpgsql


--9)Função para calcular se o CPF é válido*.

--10)Função que calcula a quantidade de horas extras de um 
--  mecânico em um mês de trabalho. 
--  O número de horas extras é calculado a partir 
--  das horas que excedam as 160 horas de trabalho mensais. 
--  O número de horas mensais trabalhadas é calculada a 
--  partir dos consertos realizados. Cada conserto tem a duração de 1 hora.
create or replace function funcao_10(pcodm int, pmes int, pano int)
returns int as
$$
declare
    vHorasTrabalho int default 0;
begin
select count(*) from conserto where codm = pcodm and date_part('month',data) = pmes and date_part('year', data) = pano into vHorasTrabalho;
    RAISE NOTICE 'Quantidade de horas trabalhadas: %', vHorasTrabalho;
    if vHorasTrabalho > 160 then
        return vHorasTrabalho -160;
    else
        RETURN 0;
    end if;
end;
$$
language plpgsql;
