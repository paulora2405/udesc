--1
create or replace view view_mecanico_nome_funcao as
select nome, funcao
from mecanico
with check option

--2
create or replace view view_cliente_modelo_marca (nome_cliente, veiculo_modelo, veiculo_marca) as
select nome,modelo,marca
from cliente join veiculo using (codc)

--3
create or replace view view_cliente_mecanico_veiculo_data_hora (nome_mecanico,nome_cliente, veiculo_modelo, data_conserto, hora_conserto) as
select mecanico.nome,cliente.nome,modelo,data,hora 
from mecanico join conserto using (codm)
join veiculo using (codv)
join cliente using (codc)

--4
create or replace view view_ano_media (ano, media_km) as
select ano, avg(quilometragem) 
from veiculo 
group by (ano)

--5
create or replace view view_mec_total_consertos as
select nome, data, count(*) 
from conserto join mecanico using (codm)
group by nome,data

--6
create or replace view view_setor_total_consertos as
select setor.nome, data, count(*)
from conserto join mecanico using (codm)
join setor using (cods)
group by setor.nome,data

--7
create or replace view view_funcoes_qnt_mecanico as
select funcao, count(funcao) as quant
from mecanico
group by funcao

--8
create or replace view view_mecanicos_funcao_setor (nome_mec, funcao, nome_set,num_set) as
select mecanico.nome, funcao, setor.nome, setor.cods
from mecanico left join setor using (cods)

--9
create or replace view view_funcoes_qnt_consertos as
select funcao, count(*)
from mecanico join conserto using (codm)
group by funcao